#pragma once

#include "../Maths/Vector.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace gloop {

     // Class storing all the parameters of the camera
     // The Camera class only exists for Polymorphism purposes. 
     // Inherited classes CameraOrtho and CameraPerspective should be used for modelisation purposes
    class Camera {
        public:
            // Position of the camera in the scene
            Vector3f pos;
            // Orientation of the camera
            Vector3f ori;
            // Vertical of the camera
            Vector3f vis;

            // Minimum render distance 
            float cmin;
            // Maximum render distance
            float cmax;

        protected:
            Camera(Vector3f pos, Vector3f ori, Vector3f vis, float cmin, float cmax) : pos(pos), ori(ori), vis(vis), cmin(cmin), cmax(cmax) {}
    };

    // Class storing the parameters of a camera displaying the scene in perspective
    // It contains a method allowing to build it directly in the scene
    class CameraPerspective : public Camera {
        public:
            CameraPerspective(Vector3f pos, Vector3f ori, Vector3f vis, float foc, float ratio, float cmin, float cmax);

            // OpenGL calls to build the camera in the scene
            void buildPerspectiveCamera();

            // Updates the content of the camera
            void reshape(float foc, float ratio);
        private:
            // Horizontal field of view of the camera
            float foc;
            // Ratio between the horizontal and vertical fov of the camera
            float ratio;
    };

    // Class storing the parameters of a camera displaying the scene in orthogonal view
    // It contains a method allowing to build it directly in the scene
    class CameraOrtho : public Camera {
        public:
            CameraOrtho(Vector3f pos, Vector3f ori, Vector3f vis, float g, float d, float b, float h, float cmin, float cmax);

            // OpenGL calls to build the camera in the scene
            void buildOrthoCamera();

            // Updates the content of the camera
            void reshape(float g, float d, float b, float h);
        private:
            float g;
            float d;
            float b;
            float h;
    };

}