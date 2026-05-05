#include <stdio.h>
#include <stdlib.h>
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
#define SPECIAL_KEY_OFFSET 256 

//#define TEST

#ifndef TEST

/******************************/
/**** GLUT EVENT FUNCTIONS ****/
/******************************/

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

static void display(void){
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
    prop::getMouse().update();

    glutPostRedisplay();
    glutTimerFunc(1000 / prop::FPS, timer, 0);
}

static void reshape(int wx, int wy){
    prop::getDisplay().reshape(wx, wy);
}

static void keyboard(unsigned char key, int x, int y){
    (void)x; (void)y;
    prop::getKey().setKeyStateTrue(key);
}

static void keyboardUp(unsigned char key, int x, int y){
    (void)x; (void)y;
    prop::getKey().setKeyStateFalse(key);
}

static void special(int specialKey, int x, int y){
    (void)x; (void)y;
    prop::getKey().setKeyStateTrue(SPECIAL_KEY_OFFSET + specialKey);
    glutPostRedisplay();
}

static void specialUp(int specialKey, int x, int y){
    (void)x; (void)y;
    prop::getKey().setKeyStateFalse(SPECIAL_KEY_OFFSET + specialKey);
}

static void mouseMotion(int x, int y){
    prop::getMouse().moveTo(gloop::Vector2f{ (float)x ,(float)y });
}

static void passiveMouseMotion(int x, int y){
    prop::getMouse().moveTo({ (float)x,(float)y });
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

/*****************************/
/**** KEY EVENT FUNCTIONS ****/
/*****************************/

static void toggleDisplay(bool state) {
    if (state) {
        prop::getDisplayMode().next();
    }
}

static void toggleLights(bool state) {
    if (state)
        prop::getSceneProperties().toggleLights();
}

static void toggleTextures(bool state) {
    if (state)
        prop::getSceneProperties().toggleTexures();
}

static void quit(bool state) {
    if (state)
        prop::getSceneManager().popScene();
}

static void loadkeyboardCallbacks() {
    prop::getKey().registerCallback(SPECIAL_KEY_OFFSET + GLUT_KEY_F1, toggleDisplay);
    prop::getKey().registerCallback(0x1b, quit); // Escape key
    prop::getKey().registerCallback(SPECIAL_KEY_OFFSET + GLUT_KEY_F2, toggleLights);
    prop::getKey().registerCallback(SPECIAL_KEY_OFFSET + GLUT_KEY_F3, toggleTextures);
}

int main(int argc, char** argv) {
    prop::init(argc, argv, gloop::Rectangle({0,0},480, 480), "Labyrinthe");

    MenuScene ms;
    prop::getSceneManager().pushScene(ms);

    init();

    //Ajout des touches dans le KeybordManager
    prop::getKey().addKeys({
        'a', 'z', 'q', 's', 'd', 'c', ' ',
        SPECIAL_KEY_OFFSET + GLUT_KEY_LEFT,
        SPECIAL_KEY_OFFSET + GLUT_KEY_UP,
        SPECIAL_KEY_OFFSET + GLUT_KEY_DOWN,
        SPECIAL_KEY_OFFSET + GLUT_KEY_RIGHT
    });

    loadkeyboardCallbacks();


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
