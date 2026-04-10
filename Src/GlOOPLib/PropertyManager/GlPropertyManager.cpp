#include "GlPropertyManager.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void gloop::GlPropertyManager::init(int argc, char** argv, Rectangle windowDimensions, std::string windowName){
	window = Display(windowDimensions, windowName);
	glutInit(&argc, argv);
	window.createWindow();
}