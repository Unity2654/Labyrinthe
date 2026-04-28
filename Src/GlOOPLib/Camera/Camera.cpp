#include "Camera.h"
#include <iostream>

namespace gloop {


    CameraPerspective::CameraPerspective(Vector3f pos, Vector3f ori, Vector3f vis, float foc, float ratio, float cmin, float cmax) : Camera(pos, ori, vis, cmin, cmax), foc(foc), ratio(ratio) {}

    void CameraPerspective::buildPerspectiveCamera() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(foc, ratio, cmin, cmax);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        gluLookAt(pos.x, pos.y, pos.z, ori.x, ori.y, ori.z, vis.x, vis.y, vis.z);
    }


    CameraOrtho::CameraOrtho(Vector3f pos, Vector3f ori, Vector3f vis, float g, float d, float b, float h, float cmin, float cmax) : Camera(pos, ori, vis, cmin, cmax), g(g), d(d), b(b), h(h) {}

    void CameraOrtho::buildOrthoCamera()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(g, d, b, h, cmin, cmax);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(pos.x, pos.y, pos.z, ori.x, ori.y, ori.z, vis.x, vis.y, vis.z
        );
    }

}