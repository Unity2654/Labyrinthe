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

/***************/
/* TEST SCENES */
/***************/

class MovingCube : public gloop::Entity3D, public gloop::Collidable {
public :
    gloop::Vector3f speed{ 0,0,0 };
    gloop::Vector3f position{ 0,0,0 };
    std::vector<gloop::Rectangle> otherElements;

    MovingCube(gloop::Vector3f position, gloop::Vector3f speed) : position(position), speed(speed){}

    virtual void update() override {
        const gloop::collisionData data = gloop::Physics::collide(*this, otherElements);
        speed = speed + data.collision + data.correction;
        position = position + speed;
    }

    virtual void render() override {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glutSolidCube(0.2F);
        glPopMatrix();
    }

    virtual gloop::Rectangle getCollisionBox() const override {
        return gloop::Rectangle::fromCenter({ position.x, position.y }, 1.0, 1.0);
    }
};

class ForceMovingCube : public MovingCube {
public :
    using MovingCube::MovingCube;

    virtual void update() override {
        gloop::Vector3f spd = speed;
        const gloop::collisionData data = gloop::Physics::collide(*this, otherElements);
        spd = spd + data.collision + data.correction;
        position = position + spd;
    }
};

// A Cube is sliding towards another cube
class Collision_Simple : public gloop::Scene {
public :
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 } };
    MovingCube cube2{ { -0.9, 0.0, 0.0 }, { 0.0,0.0,0.0 } };

    Collision_Simple() {
        cube1.otherElements = { cube2.getCollisionBox()};
        addEntity(cube1);
        addObject(cube2);
    }
};

// A cube sliding towards 2 other cubes, colliding in the middle
class Collision_TwoCubes : public gloop::Scene {
public:
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 } };
    MovingCube cube2{ { -0.9, 0.0, 0.1 }, { 0.0,0.0,0.0 } };
    MovingCube cube3{ { -0.9, 0.0, -0.1 }, { 0.0,0.0,0.0 } };

    Collision_TwoCubes() {
        cube1.otherElements = { cube2.getCollisionBox(), cube3.getCollisionBox()};
        addEntity(cube1);
        addObject(cube2);
        addObject(cube3);
    }
};

// A cube sliding towards another cube, higher on the Y axis
class Collision_YAxis : public gloop::Scene {
public:
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 } };
    MovingCube cube2{ { -0.6, 0.5, 0.0 }, { 0.0,0.0,0.0 } };

    Collision_YAxis() {
        cube1.otherElements = { cube2.getCollisionBox()};
        addEntity(cube1);
        addObject(cube2);
    }
};

// A cube sliding towards another cube, without lowering its speed upon making contact
class Collision_Force : public gloop::Scene {
public:
    ForceMovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 } };
    MovingCube cube2{ { -0.9, 0.0, 0.0 }, { 0.0,0.0,0.0 } };

    Collision_Force() {
        cube1.otherElements = { cube2.getCollisionBox()};
        addEntity(cube1);
        addObject(cube2);
    }
};

/**********************/
/* END OF TEST SCENES */
/**********************/

struct SceneHandler {
    std::vector < std::shared_ptr<gloop::Scene>> Scenes;
    int currentScene = 0;
    std::shared_ptr < gloop:: Scene > sc1 = std::make_shared<gloop::Scene>(Collision_Simple());
    std::shared_ptr < gloop::Scene > sc2 = std::make_shared<gloop::Scene>(Collision_TwoCubes());
    std::shared_ptr < gloop::Scene > sc3 = std::make_shared<gloop::Scene>(Collision_YAxis());
    std::shared_ptr < gloop::Scene > sc4 = std::make_shared<gloop::Scene>(Collision_Force());

    SceneHandler(){
        Scenes.push_back(sc1);
        Scenes.push_back(sc2);
        Scenes.push_back(sc3);
        Scenes.push_back(sc4);
    }

    void next() {
        currentScene = (currentScene + 1) % Scenes.size();
    }

    void prev() {
        currentScene = (currentScene - 1) % Scenes.size();
    }

    void render() {
        Scenes[currentScene]->display();
    }

    void update() {
        Scenes[currentScene]->update();
    }
};

static int wTx = 480;
static int wTy = 480;
static int wPx = 50;
static int wPy = 50;
static int fps = 60;

static GLenum displays[3] = { GL_FILL, GL_LINE, GL_POINT };
static int displayCount = 3;
static int currentDisplay = 1;

static SceneHandler handler{};

static void init(void) {
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
}

static void clean(void) {
}

static void display(void) {
    glPolygonMode(GL_FRONT, displays[currentDisplay]);

    glPushMatrix();
    glRotatef(10, 1.0, 1.0, 0.0);

    handler.render();

    glPopMatrix();

    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %x\n", error);
}

static void timer(int value) {
    handler.update();
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, timer, 0);
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
        break;
    case 0xd : // enter
        handler.next();
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
    glutTimerFunc(1000/fps, timer, 0);
    glutDisplayFunc(display);
    // affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements
    glutMainLoop();
}