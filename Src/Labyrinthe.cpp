//// Memory checking
//#if defined(WIN32) || defined(WIN64)
//#define _CRTDBG_MAP_ALLOC
//#if defined(_DEBUG)
//#define _AFXDLL
//#include <afx.h>
//#endif
//#endif
//#include <stdlib.h>
//#if defined(WIN32) || defined(WIN64)
//#include <crtdbg.h>
//#endif

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>

#include "GlOOPLib/Scenes/Scenes.h"
#include "GlOOPLib/Objects/Entity3D.h"
#include "GlOOPLib/Objects/Object3D.h"
#include "GlOOPLib/Maths/Vector.h"
#include "GlOOPLib/Lights/Lights.h"
#include "GlOOPLib/Lights/Materials.h"
#include "GlOOPLib/Textures/Texture.h"
#include "GlOOPLib/Physics/Physics.h"
#include "GlOOPLib/PropertyManager/GlPropertyManager.h"
#include "Components/LabyrintheScene.h"
#include "Components/MenuScene.h"
#include "Laby/tab.h"

#define SHOW_HITBOX
//#define TEST

#ifndef TEST

// --- window ---
static int wTx = 480; // size of the window, initially set to 480x480
static int wTy = 480;
static int wPx = 50; // initial position of the window (50x50)
static int wPy = 50;

// --- display ---
static GLenum displays[3] = {GL_LINE, GL_FILL, GL_POINT};
static int displayCount = 3;
static int currentDisplay = 1;

/********************************************************************/
/************* TEMPORARY CONTENT FOR FIRST DEPOSIT ******************/
/********************************************************************/
// --- constants ---
#define MOUSE_SENS 0.003f         // mouse sensitivity
#define MOVEMENT_SPEED 0.05f      // movement speed
#define SPRINT_SPEED 0.05f        // sprint speed, added to MOVEMENT_SPEED
#define GRAVITY 0.01f             // gravity (used for the jump)
#define JUMP_FORCE 0.2f           // force of the jump
#define CAM_SHAKE_AMPLITUDE 0.03f // used for the camera animation
#define CAM_SHAKE_SPEED 0.02f     // used for the camera animation

// --- camera ---
static int old_x = 0; // used to detect mouse movement
static int old_y = 0;
static float rotate_x = 0.0f; // used to store the angle of rotation
static float rotate_y = 0.0f;
static gloop::Vector3f looking_at(0.0, 0.0, -1.0); // direction of the camera
static gloop::Vector3f pos(1.0, 1.75, 1.0);        // position of the camera
static int camera = 0;                             // 0 = 1st person, 1 = map open
static float cam_shake = 0.0f;                     // used for the camera animation

// --- movement ---
static float jump = 0.0f;            // used to detect if the player is jumping
static int moving[4] = {0, 0, 0, 0}; // up, down, left, right
static bool isSprinting = 0;         // if the player is sprinting

/**********************************************************/
/************* END OF TEMPORARY CONTENT  ******************/
/**********************************************************/

static void init(void){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE); // TODO : change the way the text is drawn, then re-enable this

    float globalAmbient[4] = {0.15, 0.15, 0.15, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Loading a texture for test purposes
    //gloop::Texture tex = gloop::Texture("../Resources/orange.png");
}

static void display(void)
{
    glPolygonMode(GL_FRONT, displays[currentDisplay]);
    if (prop::isMainScene()) {
        // TESTS //
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, (float)wTx / wTy, 0.1, 100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(
            pos.x, pos.y + sin(cam_shake) * CAM_SHAKE_AMPLITUDE, pos.z,       // position caméra
            pos.x + looking_at.x, pos.y + looking_at.y, pos.z + looking_at.z, // point regardé
            0.0, 1.0, 0.0);

        cam_shake += CAM_SHAKE_SPEED;
        // END OF TESTS //
    }
    glPushMatrix();

    prop::getSceneManager().display();

    glPopMatrix();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %x\n", error);
}

static void timer(int value)
{
    prop::getSceneManager().update();

    if (prop::isMainScene()) {
        gloop::Vector2f vect{ looking_at.x, looking_at.z };

        gloop::Vector2f speed{ 0, 0 };
        if (moving[0])
        {
            speed.x += vect.x;
            speed.y += vect.y;
        }
        if (moving[1])
        {
            speed.x -= vect.x;
            speed.y -= vect.y;
        }
        if (moving[2])
        {
            speed.x += vect.y;
            speed.y -= vect.x;
        }
        if (moving[3])
        {
            speed.x -= vect.y;
            speed.y += vect.x;
        }
        speed = speed.normalize() * (MOVEMENT_SPEED + isSprinting * SPRINT_SPEED);
        pos = { pos.x + speed.x, pos.y, pos.z + speed.y };

        if (pos.y >= 1.75f)
        {
            pos.y += jump;
            jump -= GRAVITY;
        }
        else
        {
            jump = 0.0f;
            pos.y = 1.75f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / prop::FPS, timer, 0);
}

static void reshape(int wx, int wy)
{
    wTx = wx;
    wTy = wy;
    prop::getDisplay().reshape(wx, wy);
}

static void keyboard(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;

    switch (key)
    {
    case 'c':
        camera = (camera + 1) % 2;
        break;
    case 'z':
        moving[0] = 1;
        break;
    case 's':
        moving[1] = 1;
        break;
    case 'q':
        moving[2] = 1;
        break;
    case 'd':
        moving[3] = 1;
        break;
    case 'a':
        isSprinting = !isSprinting;
        break;
    case ' ':
        if (pos.y <= 1.75f)
            jump = JUMP_FORCE;
        break;
    case 'r':
        currentDisplay = (currentDisplay + 1) % displayCount;
        break;
    }
}

static void keyboardUp(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;
    switch (key)
    {
    case 'z':
        moving[0] = 0;
        break;
    case 's':
        moving[1] = 0;
        break;
    case 'q':
        moving[2] = 0;
        break;
    case 'd':
        moving[3] = 0;
        break;
    }
}

static void special(int specialKey, int x, int y)
{
    (void)x;
    (void)y;

    switch (specialKey)
    {
    case GLUT_KEY_UP:
        moving[0] = 1;
        break;
    case GLUT_KEY_DOWN:
        moving[1] = 1;
        break;
    case GLUT_KEY_LEFT:
        moving[2] = 1;
        break;
    case GLUT_KEY_RIGHT:
        moving[3] = 1;
        break;
    }

    glutPostRedisplay();
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */
static void mouseMotion(int x, int y)
{
    // rotate_x += x - old_x;
    // rotate_y += y - old_y;
    // old_x = x;
    // old_y = y;
    // glutPostRedisplay();
    prop::getMouse().update(gloop::Vector2f{ (float)x ,(float)y });

    if (!prop::isMainScene())
        return;

    float dx = (x - old_x) * MOUSE_SENS;
    float dy = (y - old_y) * MOUSE_SENS;

    old_x = x;
    old_y = y;

    rotate_x += dx;
    rotate_y += dy;

    // printf("rotate_x = %f, rotate_y = %f\n", rotate_x, rotate_y);

    looking_at.x = cos(rotate_y) * sin(rotate_x);
    looking_at.y = -sin(rotate_y);
    looking_at.z = -cos(rotate_y) * cos(rotate_x);
}

static int warp = 0;

static void passiveMouseMotion(int x, int y)
{
    prop::getMouse().update({ (float)x,(float)y });
    if (!prop::isMainScene())
        return;

    if (warp)
    {
        warp = 0;
        return;
    }

    float dx = (x - wTx / 2) * MOUSE_SENS;
    float dy = (y - wTy / 2) * MOUSE_SENS;

    rotate_x += dx;
    rotate_y += dy;

    looking_at.x = cos(rotate_y) * sin(rotate_x);
    looking_at.y = -sin(rotate_y);
    looking_at.z = -cos(rotate_y) * cos(rotate_x);

    warp = 1;
    glutWarpPointer(wTx / 2, wTy / 2);
}

static void mouseFunction(int button, int state, int x, int y) {
    auto& mouse = prop::getMouse();
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
            mouse.click();
        else
            mouse.releaseClick();
    else
        if (state == GLUT_DOWN)
            mouse.rightClick();
        else
            mouse.releaseRightClick();
}

static void clean(void)
{
}

static void showDebugs()
{
#ifdef SHOW_HITBOX
    std::cout << "debug : hitbox displayed" << std::endl;
#endif // SHOW_HITBOX
}

int main(int argc, char** argv) {
//#if defined(WIN32) || defined(WIN64)
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//    _crtBreakAlloc = 634;
//#endif
    //for test : malloc(10);
    prop::init(argc, argv, gloop::Rectangle({0,0},480, 480), "Labyrinthe");
    //prop::getSceneManager().pushScene(LabyrintheScene());
    prop::getSceneManager().pushScene(MenuScene());

    atexit(clean);
    // configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme
    init();
    // programmation de la gestion des événements
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouseFunction);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passiveMouseMotion);
    glutTimerFunc(1000 / prop::FPS, timer, 0); // Using a timer instead of idle to sync with the computer clock
                                         // More work will have to be done using this, to incorporate a delta, for slow computers
    glutDisplayFunc(display);
    // affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements
    glutMainLoop();
    return 0;
}

#endif TEST
