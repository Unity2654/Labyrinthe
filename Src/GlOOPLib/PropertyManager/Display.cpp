#include "Display.h"
#include <GL/glut.h>

gloop::Display::Display(Rectangle dimensions, std::string name) : dimensions(dimensions), name(name)
{}

void gloop::Display::createWindow(){
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(dimensions.getWidth(), dimensions.getHeight());
    glutInitWindowPosition(dimensions.getPosition().x, dimensions.getPosition().y);
    glutCreateWindow(name.c_str());
}

void gloop::Display::reshape(int wx, int wy){
    dimensions = gloop::Rectangle( dimensions.getPosition(), wx, wy);
}

int gloop::Display::getSizeX() const{
    return dimensions.getWidth();
}

int gloop::Display::getSizeY() const{
    return dimensions.getHeight();
}

const gloop::Rectangle& gloop::Display::getDimensions() const{
    return dimensions;
}

const gloop::Vector2f& gloop::Display::getCenter() const{
    auto& center = dimensions.getCenter();
    return { (float)floor(center.x), (float)floor(center.y) };
}

void gloop::Display::displayViewPort() const{
    glViewport(0, 0, dimensions.getWidth(), dimensions.getHeight());
}
