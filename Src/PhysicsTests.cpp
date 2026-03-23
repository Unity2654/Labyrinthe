#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "GlOOPLib/Scenes/Scenes.h"
#include "GlOOPLib/Objects/Entity3D.h"
#include "GlOOPLib/Objects/Object3D.h"
#include "GlOOPLib/Maths/Vector.h"
#include "GlOOPLib/Lights/Lights.h"
#include "GlOOPLib/Lights/Materials.h"
#include "GlOOPLib/Textures/Texture.h"
#include "GlOOPLib/Physics/Physics.h"


static int wTx = 480;
static int wTy = 480;
static int wPx = 50;
static int wPy = 50;

static GLenum displays[3] = { GL_LINE, GL_FILL, GL_POINT };
static int displayCount = 3;
static int currentDisplay = 1;

static gloop::Scene mainScene;

static void init(void) {
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
}

static void clean(void) {
}

static void display(void) {
    glPolygonMode(GL_FRONT, displays[currentDisplay]);

    mainScene.display();


    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %x\n", error);
}

static void timer(int value) {
    mainScene.update();
    glutPostRedisplay();
}

static void reshape(int wx, int wy) {
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %x %4d %4d\n", key, x, y);
    switch (key) {
    case 0x1B: // escape
        exit(0);
        break;
    case 0x20: // space
        currentDisplay = (currentDisplay + 1) % displayCount;
        glutPostRedisplay();
        break;
    }
    return;
}

int main(int argc, char** argv) {

    atexit(clean); // exécution d'une fonction (static void clean(void)) lorsque l'application est interrompue par exécution de la fonction standard void exit(int)

    glutInit(&argc, argv);
    // configuration et création de la fenêtre de visualisation
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Physique");
    // configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme
    init();
    // programmation de la gestion des événements
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(1/60, timer, 0);
    glutDisplayFunc(display);
    // affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements
    glutMainLoop();
}