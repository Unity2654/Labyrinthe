#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "GlOOPLib/Scenes/Scenes.h"
#include "GlOOPLib/Objects/Entity3D.h"
#include "GlOOPLib/Objects/Object3D.h"
#include "GlOOPLib/Maths/Vector.h"
#include "GlOOPLib/Lights/Lights.h"
#include "GlOOPLib/Lights/Materials.h"
#include "GlOOPLib/Textures/Texture.h"
#include "GlOOPLib/Physics/Physics.h"
#include "Components/LabyrintheScene.h"
#include "Laby/tab.h"

#define SHOW_HITBOX

// --- window ---
static int wTx = 480; // size of the window, initially set to 480x480
static int wTy = 480;
static int wPx = 50; // initial position of the window (50x50)
static int wPy = 50;

// --- display ---
static GLenum displays[3] = { GL_LINE, GL_FILL, GL_POINT };
static int displayCount = 3;
static int currentDisplay = 1;
static int constexpr fps = 60;


static LabyrintheScene mainScene;

static void init(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    float globalAmbient[4] = { 0.15, 0.15, 0.15, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutSetCursor(GLUT_CURSOR_NONE);
}

static void display(void) {
    glPolygonMode(GL_FRONT, displays[currentDisplay]);
    // TESTS //
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)wTx / wTy, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        7.0, 2.0, 5.0,
        6.0, 0.0, 0.0, 
        0.0, 1.0, 0.0);
    // END OF TESTS //
    glPushMatrix();

    mainScene.display();

    glPopMatrix();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %x\n", error);
}

static void timer(int value) {
    mainScene.update();
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, timer, 0);
}

static void reshape(int wx, int wy){
    mainScene.reshape(wx, wy);
}

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %x %4d %4d\n", key, x, y);
    switch (key) {
    case 0x1B: // escape
        exit(0);
        break;
    case 0x20: // space
        currentDisplay = (currentDisplay + 1) % displayCount;
        break;
    }
    return;
}

static void showDebugs() {
#ifdef SHOW_HITBOX
    std::cout << "debug : hitbox displayed" << std::endl;
#endif // SHOW_HITBOX

}

int main(int argc, char** argv) {
    // configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme
    init();
    // programmation de la gestion des événements
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000 / fps, timer, 0); // Using a timer instead of idle to sync with the computer clock
                                         // More work will have to be done using this, to incorporate a delta, for slow computers
    glutDisplayFunc(display);
    // affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements
    glutMainLoop();
    return 0;
}