#pragma once
#include <GL/gl.h>
#include "Colors.h"
#include "../Maths/Vector.h"

namespace gloop{

    struct LightData {
        Color ambientColor;
        Color diffuseColor;
        Color specularColor;
    };

    class Light{
    public :
        const GLenum light;
        LightData data;
        bool enabled = true;

        Light() = delete;
        Light(GLenum light) : light(light) {}
        Light(GLenum light, LightData data) : light(light), data(data) {}

        // Methods
        virtual void update() {}

        void render() const{
            doRender();
            float colorA[4] = { data.ambientColor.r, data.ambientColor.g, data.ambientColor.b, data.ambientColor.alpha };
            glLightfv(light, GL_AMBIENT, colorA);
            float colorD[4] = { data.diffuseColor.r, data.diffuseColor.g, data.diffuseColor.b, data.diffuseColor.alpha };
            glLightfv(light, GL_DIFFUSE, colorD);
            float colorS[4] = { data.specularColor.r, data.specularColor.g, data.specularColor.b, data.specularColor.alpha };
            glLightfv(light, GL_SPECULAR, colorS);
            if(enabled)
                glEnable(light);
            else
                glDisable(light);
        }

        // Stores the light currently applied to the scene in an object
        static Light GetCurrentLight(GLenum targetLight) {
            float colorA[4];
            glGetLightfv(targetLight, GL_AMBIENT, colorA);
            float colorD[4];
            glGetLightfv(targetLight, GL_DIFFUSE, colorD);
            float colorS[4];
            glGetLightfv(targetLight, GL_SPECULAR, colorS);
            LightData resData = {
                {colorA[0], colorA[1], colorA[2], colorA[3]},
                {colorD[0], colorD[1], colorD[2], colorD[3]},
                {colorS[0], colorS[1], colorS[2], colorS[3]},
            };
            Light res = { targetLight, resData };
            res.enabled = glIsEnabled(targetLight);
            return res;
        }

    protected :
        virtual void doRender() const{}
    };

    class DirectionalLight : public Light {
    public :
        Vector3f direction{ 1.0,0.0,1.0 };

        // Constructors
        using Light::Light;
        DirectionalLight(GLenum light, Vector3f direction) : Light(light), direction(direction) {}
        DirectionalLight(GLenum light, LightData data, Vector3f direction) : Light(light, data), direction(direction) {}

        // Methods
        virtual void doRender() const override {
            float v[] = { direction.x, direction.y, direction.z, 0.0F };
            glLightfv(light, GL_POSITION, v);
        }

        // Stores the light currently applied to the scene in an object
        static DirectionalLight GetCurrentLight(GLenum targetLight) {
            Light* result = &(Light::GetCurrentLight(targetLight));
            DirectionalLight* res = dynamic_cast<DirectionalLight*>(result);
            float dir[3];
            glGetLightfv(targetLight, GL_POSITION, dir);
            res->direction = { dir[0], dir[1], dir[2] };
            return *res;
        }
    };

    class PonctualLight : public Light {
    public :
        Vector3f position{ 0.0F, 0.0F, 0.0F };

        // Constructors
        using Light::Light;
        PonctualLight(GLenum light, Vector3f position) : Light(light), position(position) {}
        PonctualLight(GLenum light, LightData data, Vector3f position) : Light(light, data), position(position) {}

        // Methods
        virtual void doRender() const override {
            float v[] = { position.x, position.y, position.z, 1.0F };
            glLightfv(light, GL_POSITION, v);
        }

        // Stores the light currently applied to the scene in an object
        static PonctualLight GetCurrentLight(GLenum targetLight) {
            Light* result = &(Light::GetCurrentLight(targetLight));
            PonctualLight* res = dynamic_cast<PonctualLight*>(result);
            float pos[3];
            glGetLightfv(targetLight, GL_POSITION, pos);
            res->position = { pos[0], pos[1], pos[2] };
            return *res;
        }
    };

    class SpotLight : public PonctualLight {
    public:
        Vector3f direction{ 0.0F, 0.0F, -1.0F };
        float cutoff = 90.0F;
        float exponent = 0.0F;

        // Constructors
        using PonctualLight::PonctualLight;
        SpotLight(GLenum light, Vector3f position, Vector3f direction, float cutoff, float exponent) :
            PonctualLight(light, position),
            direction(direction),
            cutoff(cutoff),
            exponent(exponent){}
        SpotLight(GLenum light, LightData data, Vector3f position, Vector3f direction, float cutoff, float exponent) :
            PonctualLight(light, data, position),
            direction(direction),
            cutoff(cutoff),
            exponent(exponent) {}

        // Methods 
        virtual void doRender() const override {
            PonctualLight::doRender();
            float dir[] = { direction.x, direction.y, direction.z };
            glLightfv(light, GL_SPOT_DIRECTION, dir);
            glLightf(light, GL_SPOT_CUTOFF, cutoff);
            glLightf(light, GL_SPOT_EXPONENT, exponent);
        }

        // Stores the light currently applied to the scene in an object
        static SpotLight GetCurrentLight(GLenum targetLight) {
            PonctualLight* result = &(PonctualLight::GetCurrentLight(targetLight));
            SpotLight* res = dynamic_cast<SpotLight*>(result);
            // direction
            float dir[3];
            glGetLightfv(targetLight, GL_SPOT_DIRECTION, dir);
            res->direction = { dir[0], dir[1], dir[2] };
            // Cutoff & exponent
            glGetLightfv(targetLight, GL_SPOT_CUTOFF, &(res->cutoff));
            glGetLightfv(targetLight, GL_SPOT_EXPONENT, &(res->exponent));
            return *res;
        }
    };
}
