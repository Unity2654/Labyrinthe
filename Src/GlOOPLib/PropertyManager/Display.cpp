#include "Display.h"
#include <GL/glut.h>

gloop::Display::Display(int wx, int wy, int px, int py, std::string name) : wx(wx), wy(wy){
    int i = 1;
    char* whatever[] = { "hello", "world" };
    glutInit(&i, whatever);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wx, wy);
    glutInitWindowPosition(wx, wy);
    glutCreateWindow(name.c_str());
}

void gloop::Display::reshape(int wx, int wy){
    this->wx = wx;
    this->wy = wy;
}

int gloop::Display::getSizeX() const{
    return wx;
}

int gloop::Display::getSizeY() const{
    return wy;
}

void gloop::Display::displayViewPort() const{
    glViewport(0, 0, wx, wy);
}
