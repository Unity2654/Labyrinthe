#include "Display.h"
#include <GL/glut.h>

gloop::Display::Display(Vector2f size, Vector2f position, std::string name) : size(size){
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(size.x, size.y);
    glutInitWindowPosition(position.x , position.y);
    glutCreateWindow(name.c_str());
}

void gloop::Display::reshape(Vector2f size){
    this->size = size;
}
