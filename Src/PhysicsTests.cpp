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

#define TEST

#ifdef TEST

/***************/
/* TEST SCENES */
/***************/

class MovingCube : public gloop::Entity3D, public gloop::Collidable {
public :
    gloop::Vector3f speed{ 0,0,0 };
    gloop::Vector3f position{ 0,0,0 };
    std::vector<gloop::CollisionBox> otherElements;
    float scale;
    bool isColliding = false;
    //gloop::Material red{ gloop::Color{1.0,0.0,0.0,1.0}, gloop::Color{1.0,0.0,0.0,1.0} };

    MovingCube(gloop::Vector3f position, gloop::Vector3f speed, float scale) : position(position), speed(speed), scale(scale){}

    virtual void update() override {
        const gloop::collisionData data = gloop::Physics::collide(this->getCollisionBox(), otherElements);
        speed = speed + data.collision + data.correction;
        position = position + speed;
        isColliding = data.flags.find(gloop::CollisionFlag::TESTFLAG) != data.flags.end();
    }

    virtual void render() override {
        //gloop::Material old = gloop::Material::getCurrentMaterial(GL_FRONT);
        glPushMatrix();
        /*if (isColliding)
            red.apply(GL_FRONT);*/
        glTranslatef(position.x, position.y, position.z);
        glutSolidCube(scale);
        glPopMatrix();
        //old.apply(GL_FRONT);
    }

    virtual gloop::CollisionBox getCollisionBox() const override {
        return { gloop::Rectangle::fromCenter({ position.x, position.z }, scale, scale), true, {}, getSpeed() };
    }

    virtual gloop::Vector2f getSpeed() const {
        return { speed.x, speed.z };
    }
};

class NonSolidCube : public MovingCube {
public:
    using MovingCube::MovingCube;

    virtual gloop::CollisionBox getCollisionBox() const override {
        return { gloop::Rectangle::fromCenter({ position.x, position.z }, scale, scale), false, { gloop::CollisionFlag::TESTFLAG }, getSpeed() };
    }
};

class ForceMovingCube : public MovingCube {
public :
    using MovingCube::MovingCube;

    virtual void update() override {
        gloop::Vector3f spd = speed;
        const gloop::collisionData data = gloop::Physics::collide(this->getCollisionBox(), otherElements);
        std::cout << data.correction.x << " " << data.correction.y << std::endl;
        spd = { spd.x + data.collision.x + data.correction.x, spd.y ,spd.z + data.collision.y + data.correction.y };
        position = position + spd;
    }
};

// A Cube is sliding towards another cube
class Collision_Simple : public gloop::Scene {
public :
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 }, 0.5 };
    MovingCube cube2{ { -0.9, 0.0, 0.0 }, { 0.0,0.0,0.0 }, 0.5 };

    Collision_Simple() {
        cube1.otherElements.push_back(cube2.getCollisionBox());
        addEntity(cube1);
        addObject(cube2);
    }
};

// A Cube is sliding towards an non-solid cube, giving a flag turning the first cube red on collision
class Collision_Flag : public gloop::Scene {
public:
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 }, 0.5 };
    NonSolidCube cube2{ { -0.9, 0.0, 0.0 }, { 0.0,0.0,0.0 }, 0.5 };

    Collision_Flag() {
        cube1.otherElements.push_back(cube2.getCollisionBox());
        addEntity(cube1);
        addObject(cube2);
    }
};

// A cube sliding towards 2 other cubes, colliding in the middle
class Collision_TwoCubes : public gloop::Scene {
public:
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 }, 0.5 };
    MovingCube cube2{ { -0.9, 0.0, 0.1 }, { 0.0,0.0,0.0 }, 0.5 };
    MovingCube cube3{ { -0.9, 0.0, -0.1 }, { 0.0,0.0,0.0 }, 0.5 };

    Collision_TwoCubes() {
        cube1.otherElements.push_back(cube2.getCollisionBox()); 
        cube1.otherElements.push_back(cube3.getCollisionBox());
        addEntity(cube1);
        addObject(cube2);
        addObject(cube3);
    }
};

// A cube sliding towards another cube, higher on the Y axis
// A collision should occur
class Collision_YAxis : public gloop::Scene {
public:
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 }, 0.2 };
    MovingCube cube2{ { -0.6, 0.5, 0.0 }, { 0.0,0.0,0.0 }, 0.5 };

    Collision_YAxis() {
        cube1.otherElements.push_back(cube2.getCollisionBox());
        addEntity(cube1);
        addObject(cube2);
    }
};

// A cube sliding towards another cube, higher on the Z axis
// No collision should occur
class Collision_ZAxis : public gloop::Scene {
public:
    MovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 }, 0.2};
    MovingCube cube2{ { -0.6, 0.0, 0.7 }, { 0.0,0.0,0.0 }, 0.5};

    Collision_ZAxis() {
        cube1.otherElements.push_back(cube2.getCollisionBox());
        addEntity(cube1);
        addObject(cube2);
    }
};

// A Cube is sliding towards another cube in a diagonal direction
class Collision_Diagonal : public gloop::Scene {
public:
    MovingCube cube1{ { 0.9, 0.0, 0.9 }, {-0.01,0.0,-0.01 }, 0.2 };
    MovingCube cube2{ { -0.9, 0.0, 0.0 }, { 0.0,0.0,0.0 }, 0.5 };

    Collision_Diagonal() {
        cube1.otherElements.push_back(cube2.getCollisionBox());
        addEntity(cube1);
        addObject(cube2);
    }
};

// A Cube is sliding towards another cube in a diagonal direction, without lowering its speed upon making contact
class Collision_Force_Diagonal : public gloop::Scene {
public:
    ForceMovingCube cube1{ { 0.9, 0.0, 0.9 }, {-0.01,0.0,-0.01 }, 0.2 };
    MovingCube cube2{ { -0.9, 0.0, 0.0 }, { 0.0,0.0,0.0 }, 0.5 };

    Collision_Force_Diagonal() {
        cube1.otherElements.push_back(cube2.getCollisionBox());
        addEntity(cube1);
        addObject(cube2);
    }
};

// A cube sliding towards another cube, without lowering its speed upon making contact
class Collision_Force : public gloop::Scene {
public:
    ForceMovingCube cube1{ { 0.9, 0.0, 0.0 }, {-0.01,0.0,0.0 }, 0.2 };
    MovingCube cube2{ { -0.9, 0.0, 0.0 }, { 0.0,0.0,0.0 }, 0.5 };

    Collision_Force() {
        cube1.otherElements.push_back(cube2.getCollisionBox());
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
    std::shared_ptr < gloop::Scene > sc4 = std::make_shared<gloop::Scene>(Collision_ZAxis());
    std::shared_ptr < gloop::Scene > sc5 = std::make_shared<gloop::Scene>(Collision_Force());
    std::shared_ptr < gloop::Scene > sc6 = std::make_shared<gloop::Scene>(Collision_Diagonal());
    std::shared_ptr < gloop::Scene > sc7 = std::make_shared<gloop::Scene>(Collision_Force_Diagonal());
    std::shared_ptr < gloop::Scene > sc8 = std::make_shared<gloop::Scene>(Collision_Flag());

    SceneHandler(){
        Scenes.push_back(sc1);
        Scenes.push_back(sc2);
        Scenes.push_back(sc3);
        Scenes.push_back(sc4);
        Scenes.push_back(sc5);
        Scenes.push_back(sc6);
        Scenes.push_back(sc7);
        Scenes.push_back(sc8);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(30, 1.0, 1.0, 0.0);

    handler.render();

    glPopMatrix();
    glutSwapBuffers();
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
#endif // TEST