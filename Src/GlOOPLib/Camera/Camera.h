#pragma once

#include "../Maths/Vector.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace gloop {

    class Camera {
        public:
            
            Vector3f pos;
            Vector3f ori;
            Vector3f vis;

            float cmin;
            float cmax;

        protected:
            Camera(Vector3f pos, Vector3f ori, Vector3f vis, float cmin, float cmax) : pos(pos), ori(ori), vis(vis), cmin(cmin), cmax(cmax) {}
    };

    class CameraPerspective : public Camera {
        public:
            CameraPerspective(Vector3f pos, Vector3f ori, Vector3f vis, float foc, float ratio, float cmin, float cmax);

            void buildPerspectiveCamera();

        private:
            float foc;
            float ratio;
    };

    class CameraOrtho : public Camera {
        public:
            CameraOrtho(Vector3f pos, Vector3f ori, Vector3f vis, float g, float d, float b, float h, float cmin, float cmax);

            void buildOrthoCamera();

        private:
            float g;
            float d;
            float b;
            float h;
    };

}