#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "spng/spng.h"

#include "GlOOPLib/Scenes/Scenes.h"
#include "GlOOPLib/Objects/Entity3D.h"
#include "GlOOPLib/Objects/Object3D.h"
#include "GlOOPLib/Maths/Vector.h"
#include "GlOOPLib/Lights/Lights.h"
#include "GlOOPLib/Lights/Materials.h"
#include "GlOOPLib/Textures/Texture.h"

class StaticOrange : public gloop::Object3D {
public :
    const float size = 0.5f;
    const gloop::Texture tex;
    
    StaticOrange() = delete;
    StaticOrange(gloop::Texture tex) : tex(tex) {}

    virtual void render() override {
        glPushMatrix();
        float t = size/2;
        // Making the cube
        float points[8][3] = {
            {-t, -t, -t},
            {t, -t, -t},
            {t, -t ,t},
            {-t, -t, t},
            {-t, t, -t},
            {t, t, -t},
            {t, t ,t},
            {-t, t, t},
        };
        glBegin(GL_QUADS);
        {
            glNormal3f(0,-1,0);
            glTexCoord2f(0.0F, 0.0F);
            glVertex3fv(points[0]);
            glTexCoord2f(1.0F, 0.0F);
            glVertex3fv(points[1]);
            glTexCoord2f(1.0F, 1.0F);
            glVertex3fv(points[2]);
            glTexCoord2f(0.0F, 1.0F);
            glVertex3fv(points[3]);
            
            glNormal3f(1, 0, 0);
            glTexCoord2f(0.0F, 0.0F);
            glVertex3fv(points[1]);
            glTexCoord2f(1.0F, 0.0F);
            glVertex3fv(points[5]);
            glTexCoord2f(1.0F, 1.0F);
            glVertex3fv(points[6]);
            glTexCoord2f(0.0F, 1.0F);
            glVertex3fv(points[2]);
            
            glNormal3f(0, 0, -1);
            glTexCoord2f(0.0F, 0.0F);
            glVertex3fv(points[2]);
            glTexCoord2f(1.0F, 0.0F);
            glVertex3fv(points[6]);
            glTexCoord2f(1.0F, 1.0F);
            glVertex3fv(points[7]);
            glTexCoord2f(0.0F, 1.0F);
            glVertex3fv(points[3]);
            
            glNormal3f(-1, 0, 0);
            glTexCoord2f(0.0F, 0.0F);
            glVertex3fv(points[3]);
            glTexCoord2f(1.0F, 0.0F);
            glVertex3fv(points[7]);
            glTexCoord2f(1.0F, 1.0F);
            glVertex3fv(points[4]);
            glTexCoord2f(0.0F, 1.0F);
            glVertex3fv(points[0]);
            
            glNormal3f(0, 0, 1);
            glTexCoord2f(0.0F, 0.0F);
            glVertex3fv(points[0]);
            glTexCoord2f(1.0F, 0.0F);
            glVertex3fv(points[4]);
            glTexCoord2f(1.0F, 1.0F);
            glVertex3fv(points[5]);
            glTexCoord2f(0.0F, 1.0F);
            glVertex3fv(points[1]);
            
            glNormal3f(0, 1, 0);
            glTexCoord2f(0.0F, 0.0F);
            glVertex3fv(points[4]);
            glTexCoord2f(1.0F, 0.0F);
            glVertex3fv(points[7]);
            glTexCoord2f(1.0F, 1.0F);
            glVertex3fv(points[6]);
            glTexCoord2f(0.0F, 1.0F);
            glVertex3fv(points[5]);

        }
        glEnd();

        glPopMatrix();
    }
};

class RotatingSphere : public gloop::Entity3D {
public:
    const float distance = 0.75f;
    float angle = 0.0f;
    const float radius = 0.25f;
    const gloop::Material material;

    RotatingSphere() {};
    
    RotatingSphere(float angle, gloop::Material material): 
        angle(angle), material(material){ }

    virtual void render() override {
        const float a = angle;
        const float d = distance;
        const float r = radius;
        material.renderWithMaterial(GL_FRONT, [a,d,r]() {
            glPushMatrix();
            glRotatef(a, 0.0f, 0.0f, 1.0f);
            glTranslatef(d, 0.0f, 0.0f);
            glutSolidSphere(r, 180.0f, 70.0f);
            glPopMatrix();
        });
    }

    virtual void update() override {
        angle += 0.1f;
    }
};

class RotatingLight : public gloop::DirectionalLight {
    float angle;
    float distance;

public :
    RotatingLight(GLenum light, float angle, float distance) :
        DirectionalLight(light, { gloop::Color(), gloop::Color{0.0,1.0,1.0,1.0} }, { distance, 0.0f, distance }),
        angle(angle),
        distance(distance){ }


    void update() override {
        angle += 0.1;
    }

    void doRender() const override {
        glPushMatrix();
        glRotatef(angle, 0.0, 1.0, 0.0);
        gloop::DirectionalLight::doRender();
        glPopMatrix();
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
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    // Creating materials
    gloop::Material redSpecular;
    redSpecular.diffuseReflexion = { 1.0,0.0,0.0,1.0 };
    redSpecular.specularReflexion = { 1.0,1.0,1.0,1.0 };
    redSpecular.shininess = 90;
    gloop::Material blue{ gloop::Color{0.0,0.0,0.2,1.0}, gloop::Color{0.0,0.0,0.8,1.0}, gloop::Color{0.0,0.2,0.2,1.0} };
    blue.shininess = 90;

    // Loading textures
    gloop::Texture tex{ "C:/Users/kjeli/source/repos/Labyrinthe/Resources/Orange-Free-PNG-Image.png" };

    // Adding objects and entities
    mainScene.addObject(StaticOrange(tex));
    mainScene.addEntity(RotatingSphere(0, redSpecular));
    mainScene.addEntity(RotatingSphere(180, blue));

    // Adding lights
    gloop::DirectionalLight light0 = { GL_LIGHT0, { gloop::Color{0.2,0.2,0.2,1.0}, gloop::Color{1.0,1.0,1.0,1.0} , gloop::Color{1.0,1.0,1.0,1.0}}};
    mainScene.addStaticLight(light0); 
    RotatingLight light1 = { GL_LIGHT1, 0.0, 2.0 };
    //light1.enabled = false;
    mainScene.addDynamicLight(light1);
}


static void display(void) {
    glPolygonMode(GL_FRONT, displays[currentDisplay]);

    mainScene.display();

    
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %x\n", error);
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
