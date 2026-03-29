#pragma once
#include <GL/gl.h>
#include "Colors.h"
#include "../Maths/Vector.h"
#include <functional>

namespace gloop {
    class Material {
    public :
        Color ambientReflexion{ 0.2,0.2,0.2,1.0 };
        Color diffuseReflexion{ 0.8,0.8,0.8,1.0 };
        Color specularReflexion{ 0.0,0.0,0.0,1.0 };
        Color emissionColor{ 0.0,0.0,0.0,1.0 };
        float shininess = 0.0;

        // Stores the current material applied to the scene in an object
        static Material getCurrentMaterial(GLenum face) {
            Material result;
            float colorA[4];
            glGetMaterialfv(face, GL_AMBIENT, colorA);
            result.ambientReflexion = { colorA[0], colorA[1], colorA[2], colorA[3] };
            float colorS[4];
            glGetMaterialfv(face, GL_SPECULAR, colorS);
            result.specularReflexion = { colorS[0], colorS[1], colorS[2], colorS[3] };
            float colorD[4];
            glGetMaterialfv(face, GL_DIFFUSE, colorD);
            result.diffuseReflexion = { colorD[0], colorD[1], colorD[2], colorD[3] };
            float colorE[4];
            glGetMaterialfv(face, GL_EMISSION, colorE);
            result.emissionColor = { colorE[0], colorE[1], colorE[2], colorE[3] };

            glGetMaterialfv(face, GL_SHININESS, &(result.shininess));
            return result;
        }

        // Applies the material to the scene
        void apply(GLenum face) const {
            float colorA[4] = {ambientReflexion.r, ambientReflexion.g, ambientReflexion.b, ambientReflexion.alpha};
            glMaterialfv(face, GL_AMBIENT, colorA);
            float colorD[4] = { specularReflexion.r, specularReflexion.g, specularReflexion.b, specularReflexion.alpha };
            glMaterialfv(face, GL_SPECULAR, colorD);
            float colorS[4] = {diffuseReflexion.r, diffuseReflexion.g, diffuseReflexion.b, diffuseReflexion.alpha};
            glMaterialfv(face, GL_DIFFUSE, colorS);
            float colorE[4] = {emissionColor.r, emissionColor.g, emissionColor.b, emissionColor.alpha};
            glMaterialfv(face, GL_EMISSION, colorE);
            glMaterialf(face, GL_SHININESS, shininess);
        }

        // Allows to run display commands with the current material
        // The material is changed back to the original one after the displays
        void renderWithMaterial(GLenum face, std::function<void()> commands) const {
            Material old = getCurrentMaterial(face);
            apply(face);
            commands();
            old.apply(face);
        }
    };
}