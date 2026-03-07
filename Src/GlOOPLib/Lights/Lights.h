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
    };
}
