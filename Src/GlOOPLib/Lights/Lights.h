#pragma once
#include <GL/gl.h>
#include "Colors.h"
#include "../Maths/Vector.h"

namespace gloop{

    struct Light{
        const GLenum light;
        Color ambiantColor;
        Color diffuseColor;
        Color specularColor;
        bool enabled = true;

        // Constructors
        Light() = delete;

        // Methods
        virtual void update() const {}

        void render() const{
            doRender();
            glLightfv(light, GL_AMBIENT, ambiantColor.asArray());
            glLightfv(light, GL_DIFFUSE, diffuseColor.asArray());
            glLightfv(light, GL_SPECULAR, specularColor.asArray());
            if(enabled)
                glEnable(light);
            else
                glDisable(light);
        }

    protected :
        virtual void doRender() const{}
    };

    struct DirectionalLight : public Light {
        Vector3f direction{ 1.0F, 0.0F, 1.0F };

        virtual void doRender() const override {
            float v[] = { direction.x, direction.y, direction.z, 0.0F };
            glLightfv(light, GL_POSITION, v);
        }
    };

    struct PonctualLight : public Light {
        Vector3f position{ 0.0F, 0.0F, 0.0F };

        virtual void doRender() const override {
            float v[] = { position.x, position.y, position.z, 1.0F };
            glLightfv(light, GL_POSITION, v);
        }
    };

    struct SpotLight : public PonctualLight {
        Vector3f direction{ 0.0F, 0.0F, -1.0F };
        float cutoff = 90.0F;
        float exponent = 0.0F;

        virtual void doRender() const override {
            PonctualLight::doRender();
            glLightfv(light, GL_SPOT_DIRECTION, direction.asArray());
            glLightf(light, GL_SPOT_CUTOFF, cutoff);
            glLightf(light, GL_SPOT_EXPONENT, exponent);
        }
    };
}
