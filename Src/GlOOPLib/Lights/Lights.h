#pragma once
#include <GL/gl.h>
#include "Colors.h"
#include "../Maths/Vector.h"

namespace gloop{
    // Data structure made to store the main properties of a light
    struct LightData {
        Color ambientColor;
        Color diffuseColor;
        Color specularColor;
    };

    // Class storing the main properties of a light
    class Light{
    public :
        // OpenGL light used by the object
        const GLenum light;
        // Data of the light
        LightData data;
        // If true, the light is displayed in the scene
        bool enabled = true;

        Light() = delete;
        Light(GLenum light) : light(light) {}
        Light(GLenum light, LightData data) : light(light), data(data) {}

        // Methods
        
        // Updates the light
        // This method should be overriden to create dynamic lights
        virtual void update() {}

        // Displays the light in the scene.
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
        // Method called when the render method is called
        // Should be overriden to customize the call
        virtual void doRender() const{}
    };

    // Specialization of the light class, modelizing a directionnal light
    class DirectionalLight : public Light {
    public :
        // Direction of the light
        Vector3f direction{ 1.0,0.0,1.0 };

        // Constructors
        using Light::Light;
        DirectionalLight(GLenum light, Vector3f direction) : Light(light), direction(direction) {}
        DirectionalLight(GLenum light, LightData data, Vector3f direction) : Light(light, data), direction(direction) {}
        DirectionalLight(Light light) : Light(light.light, light.data) {}

        // Methods
        virtual void doRender() const override {
            float v[] = { direction.x, direction.y, direction.z, 0.0F };
            glLightfv(light, GL_POSITION, v);
        }

        // Stores the light currently applied to the scene as a directionnal light
        static DirectionalLight GetCurrentLight(GLenum targetLight) {
            DirectionalLight res = DirectionalLight(Light::GetCurrentLight(targetLight));
            float dir[3];
            glGetLightfv(targetLight, GL_POSITION, dir);
            res.direction = { dir[0], dir[1], dir[2] };
            return res;
        }
    };

    // Specialization of the light class, modelizing a ponctual light
    class PonctualLight : public Light {
    public :
        // Position of the light in the scene
        Vector3f position{ 0.0F, 0.0F, 0.0F };
        // Attenuation of the light
        Vector3f attenuation{ 1.0f, 0.0f, 0.0f };


        // Constructors
        using Light::Light;
        PonctualLight(GLenum light, Vector3f position) : Light(light), position(position) {}
        PonctualLight(GLenum light, LightData data, Vector3f position) : Light(light, data), position(position) {}
        PonctualLight(Light light) : Light(light.light, light.data) {}
        PonctualLight(GLenum light, LightData data, Vector3f position, Vector3f attenuation) : Light(light, data), position(position), attenuation(attenuation) {}

        // Methods
        virtual void doRender() const override {
            float v[] = { position.x, position.y, position.z, 1.0F };
            glLightfv(light, GL_POSITION, v);
            glLightf(light, GL_CONSTANT_ATTENUATION, attenuation.x);
            glLightf(light, GL_LINEAR_ATTENUATION, attenuation.y);
            glLightf(light, GL_QUADRATIC_ATTENUATION, attenuation.z);
        }

        // Stores the light currently applied to the scene in an object
        static PonctualLight GetCurrentLight(GLenum targetLight) {
            PonctualLight res = PonctualLight(Light::GetCurrentLight(targetLight));
            float pos[3];
            glGetLightfv(targetLight, GL_POSITION, pos);
            res.position = { pos[0], pos[1], pos[2] };
            return res;
        }
    };

    // Specialization of the positionnal light class, modelizing a spot light
    class SpotLight : public PonctualLight {
    public:
        // Direction of the cone of light
        Vector3f direction{ 0.0F, 0.0F, -1.0F };
        // Cutoff of the cone of light
        float cutoff = 90.0F;
        // Exponent of the cone of light
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
        SpotLight(Light light) : PonctualLight(light) {}

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
            SpotLight res = SpotLight(PonctualLight::GetCurrentLight(targetLight));
            // direction
            float dir[3];
            glGetLightfv(targetLight, GL_SPOT_DIRECTION, dir);
            res.direction = { dir[0], dir[1], dir[2] };
            // Cutoff & exponent
            glGetLightfv(targetLight, GL_SPOT_CUTOFF, &(res.cutoff));
            glGetLightfv(targetLight, GL_SPOT_EXPONENT, &(res.exponent));
            return res;
        }
    };
}
