#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "GlOOPLib/Scenes/Scenes.h"
#include "GlOOPLib/Objects/Entity3D.h"
#include "GlOOPLib/Objects/Object3D.h"
#include "GlOOPLib/Maths/Vector.h"

class StaticCube : public gloop::Object3D {
public :
    const float size = 0.5f;

    virtual void render() override {
        glPushMatrix();
        glutSolidCube(size);
        glPopMatrix();
    }
};

class RotatingSphere : public gloop::Entity3D {
public:
    const float distance = 0.75f;
    float angle = 0.0f;
    const float radius = 0.25f;

    RotatingSphere() {};
    
    RotatingSphere(float angle): 
        angle(angle){ }

    virtual void render() override {
        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(distance, 0.0f, 0.0f);
        glutSolidSphere(radius, 180.0f, 70.0f);
        glPopMatrix();
    }

    virtual void update() override {
        angle += 0.1f;
    }
};

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
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    mainScene.addObject(StaticCube());
    mainScene.addEntity(RotatingSphere());
    mainScene.addEntity(RotatingSphere(180));
}

static void scene(void) {
    glPushMatrix();
    glPopMatrix();
}


static void display(void) {
    glPolygonMode(GL_FRONT, displays[currentDisplay]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mainScene.display();

    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
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

static void idle(void) {
    mainScene.update();
    glutPostRedisplay();
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


static void special(int specialKey, int x, int y) {
}


static void mouse(int button, int state, int x, int y) {
    printf("M");
    return;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x, int y) {
}

/* Fonction exécutée automatiquement            */
/* lors de l'exécution de la fonction exit()    */

static void clean(void) {
}

/* Fonction principale                          */

int main(int argc, char** argv) {

    atexit(clean); // exécution d'une fonction (static void clean(void)) lorsque l'application est interrompue par exécution de la fonction standard void exit(int)

    glutInit(&argc, argv);
    // configuration et création de la fenêtre de visualisation
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Gestion événementielle de GLUt");
    // configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme
    init();
    // programmation de la gestion des événements
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    // affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements
    glutMainLoop();
    return(0);
}
