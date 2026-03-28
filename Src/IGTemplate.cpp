#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#include "spng/spng.h"

#include "GlOOPLib/Scenes/Scenes.h"
#include "GlOOPLib/Objects/Entity3D.h"
#include "GlOOPLib/Objects/Object3D.h"
#include "GlOOPLib/Maths/Vector.h"
#include "GlOOPLib/Lights/Lights.h"
#include "GlOOPLib/Lights/Materials.h"

#include "Laby3D/Laby3D.h"
#include "Laby/generation.h"

#include "Laby/tab.h"

// --- constants ---
#define MOUSE_SENS 0.003f         // mouse sensitivity
#define MOVEMENT_SPEED 0.05f      // movement speed
#define SPRINT_SPEED 0.05f        // sprint speed, added to MOVEMENT_SPEED
#define GRAVITY 0.01f             // gravity (used for the jump)
#define JUMP_FORCE 0.2f           // force of the jump
#define CAM_SHAKE_AMPLITUDE 0.03f // used for the camera animation
#define CAM_SHAKE_SPEED 0.02f     // used for the camera animation

// --- window ---
static int wTx = 480; // size of the window, initially set to 480x480
static int wTy = 480;
static int wPx = 50; // initial position of the window (50x50)
static int wPy = 50;

// --- camera ---
static int old_x = 0; // used to detect mouse movement
static int old_y = 0;
static float rotate_x = 0.0f; // used to store the angle of rotation
static float rotate_y = 0.0f;
static gloop::Vector3f looking_at(0.0, 0.0, -1.0); // direction of the camera
static gloop::Vector3f pos(0.0, 1.75, 0.0);        // position of the camera
static int camera = 0;                             // 0 = 1st person, 1 = map open
static float cam_shake = 0.0f;                     // used for the camera animation

// --- display ---
static GLenum displays[3] = {GL_LINE, GL_FILL, GL_POINT};
static int displayCount = 3;
static int currentDisplay = 1;

// --- movement ---
static float jump = 0.0f;             // used to detect if the player is jumping
static char moving[4] = {0, 0, 0, 0}; // up, down, left, right
static bool isSprinting = 0;          // if the player is sprinting

static gloop::Scene mainScene; // main scene, contains the maze

/**
 * Returns the maximum of two floating point numbers.
 *
 * @param a The first number
 * @param b The second number
 * @return The maximum of a and b
 */

/*static float max(float a, float b)
{
    return a > b ? a : b;
}*/

/**
 * Returns the minimum of two floating point numbers.
 *
 * @param a The first number
 * @param b The second number
 * @return The minimum of a and b
 */
/*static float min(float a, float b)
{
    return a < b ? a : b;
}*/

/**
 * Normalize a 2D vector.
 *
 * The length of the vector is calculated and each component of the vector is divided by the length.
 *
 * @param v The 2D vector to normalize.
 */
static void normalizeVector2D(float v[2])
{
    float l = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[0] /= l;
    v[1] /= l;
}

/**
 * Scale a 2D vector.
 *
 * Each component of the vector is multiplied by the scaling factor s.
 *
 * @param v The 2D vector to scale.
 * @param s The scaling factor.
 */
static void scaleVector2D(float v[2], float s)
{
    v[0] *= s;
    v[1] *= s;
}

static void init(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    Tab t = tab_start(10, 10, 0);
    generate(t, 1, 1, 1);

    maze_show(t);

    Laby3D laby(t, 30.0f, 30.0f, 4.0f, 0.2f, 0.4f);
    laby.displayInScene(mainScene);

    float globalAmbient[4] = {0.15, 0.15, 0.15, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutSetCursor(GLUT_CURSOR_NONE);
}

static void drawMap(bool fullscreen)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    if (fullscreen)
    {
        float map_size = min(wTx, wTy);
        glViewport((wTx - map_size) / 2, 0, map_size, map_size);
    }
    else
    {
        float map_size = max(wTx * (0.1), wTy * (0.1));
        glViewport(0, wTy - map_size, map_size, map_size);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 30.0, 0.0, // position caméra
        0.0, 0.0, 0.0,  // point regardé
        0.0, 0.0, -1.0);
    float diffLight[4] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
    float posLight[4] = {0, 10, 0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, posLight);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);

    mainScene.display();
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
}
static void display(void)
{
    // first viewport
    glViewport(0, 0, wTx, wTy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)wTx / wTy, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, displays[currentDisplay]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (camera == 1)
    {
        drawMap(true);
        glutSwapBuffers();
        return;
    }

    gluLookAt(
        pos.x, pos.y + sin(cam_shake) * CAM_SHAKE_AMPLITUDE, pos.z,       // position caméra
        pos.x + looking_at.x, pos.y + looking_at.y, pos.z + looking_at.z, // point regardé
        0.0, 1.0, 0.0);

    cam_shake += CAM_SHAKE_SPEED;

    float ambLight[4] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight);

    float diffLight[4] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
    float posLight[4] = {pos.x, pos.y, pos.z, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, posLight);

    float direction[3] = {looking_at.x, looking_at.y, looking_at.z};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);

    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15.0);

    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);

    mainScene.display();

    drawMap(false);

    glutSwapBuffers();

    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %x\n", error);
}

static void reshape(int wx, int wy)
{
    wTx = wx;
    wTy = wy;
}

static void idle(void)
{
    mainScene.update();

    float vect[2] = {looking_at.x, looking_at.z};
    normalizeVector2D(vect);
    scaleVector2D(vect, MOVEMENT_SPEED + isSprinting * SPRINT_SPEED);

    if (moving[0])
    {
        pos.x += vect[0];
        pos.z += vect[1];
    }
    if (moving[1])
    {
        pos.x -= vect[0];
        pos.z -= vect[1];
    }
    if (moving[2])
    {
        pos.x += vect[1];
        pos.z -= vect[0];
    }
    if (moving[3])
    {
        pos.x -= vect[1];
        pos.z += vect[0];
    }

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

    glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;
    float vect[2] = {looking_at.x, looking_at.z};
    normalizeVector2D(vect);
    scaleVector2D(vect, MOVEMENT_SPEED);
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

    glutPostRedisplay();
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

    float vect[2] = {looking_at.x, looking_at.z};
    normalizeVector2D(vect);
    scaleVector2D(vect, MOVEMENT_SPEED);
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

static void mouse(int button, int state, int x, int y)
{
    (void)button;
    (void)state;
    old_x = x;
    old_y = y;
    // glfwDisable(GLFW_MOUSE_CURSOR);
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

    glutPostRedisplay();
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static int warp = 0;

static void passiveMouseMotion(int x, int y)
{
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

    glutPostRedisplay();
}

/* Fonction ex�cut�e automatiquement            */
/* lors de l'ex�cution de la fonction exit()    */

static void clean(void)
{
}

/* Fonction principale                          */

int main(int argc, char **argv)
{

    atexit(clean); // ex�cution d'une fonction (static void clean(void)) lorsque l'application est interrompue par ex�cution de la fonction standard void exit(int)

    glutInit(&argc, argv);
    // configuration et cr�ation de la fen�tre de visualisation
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Maze Project");
    // configuration des param�tres OpenGL obligatoires qui n'auront pas � �tre reconfigur�s au cours de la vie du programme
    init();
    // programmation de la gestion des �v�nements
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    // glutMouseFunc(mouse);
    // glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    // affichage de la fen�tre de visualisation et lancement de la boucle infinie de gestion des �v�nements
    glutMainLoop();
    return (0);
}
