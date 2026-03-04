#pragma once
#include <GL/gl.h>
#include "Colors.h"

namespace gloop{

    struct Light{
        const GLenum Light;
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
}
