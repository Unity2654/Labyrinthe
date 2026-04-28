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
#include "Components/Character.h"

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
#define SPECIAL_KEY_OFFSET 256 

// --- camera ---
static int old_x = 0; // used to detect mouse movement
static int old_y = 0;
static float cam_shake = 0.0f;                     // used for the camera animation


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
    glEnable(GL_CULL_FACE); 
    glEnable(GL_TEXTURE_2D);

    float globalAmbient[4] = {0.15, 0.15, 0.15, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glClearColor(0.0, 0.0, 0.0, 1.0);
}

static void display(void)
{
    glPolygonMode(GL_FRONT, displays[currentDisplay]);
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
    (void)x; (void)y;
    prop::getKey().setKeyStateTrue(key);
}

static void keyboardUp(unsigned char key, int x, int y)
{
    (void)x; (void)y;
    prop::getKey().setKeyStateFalse(key);
}

static void special(int specialKey, int x, int y)
{
    (void)x; (void)y;
    prop::getKey().setKeyStateTrue(SPECIAL_KEY_OFFSET + specialKey);
    glutPostRedisplay();
}

static void specialUp(int specialKey, int x, int y)
{
    (void)x; (void)y;
    prop::getKey().setKeyStateFalse(SPECIAL_KEY_OFFSET + specialKey);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */
static void mouseMotion(int x, int y)
{
    prop::getMouse().update(gloop::Vector2f{ (float)x ,(float)y });

}

static int warp = 0;

static void passiveMouseMotion(int x, int y)
{
    prop::getMouse().update({ (float)x,(float)y });

    if (warp)
    {
        warp = 0;
        return;
    }

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
//#if defined(WIN32) || defined(WIN32)
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//    _crtBreakAlloc = 634;
//#endif
    //for test : malloc(10);
    prop::init(argc, argv, gloop::Rectangle({0,0},480, 480), "Labyrinthe");
    //prop::getSceneManager().pushScene(LabyrintheScene());
    MenuScene ms;
    prop::getSceneManager().pushScene(ms);

    atexit(clean);
    // configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme
    init();

    //Ajout des touches dans le KeybordManager
    prop::getKey().addKeys({
        'a', 'z', 'q', 's', 'd', 'c', ' ',
        SPECIAL_KEY_OFFSET + GLUT_KEY_LEFT,
        SPECIAL_KEY_OFFSET + GLUT_KEY_UP,
        SPECIAL_KEY_OFFSET + GLUT_KEY_DOWN,
        SPECIAL_KEY_OFFSET + GLUT_KEY_RIGHT
    });


    // programmation de la gestion des événements
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouseFunction);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
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
