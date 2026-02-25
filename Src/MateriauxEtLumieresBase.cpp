/* Materiaux et lumieres                        */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Fevrier 2023                                 */

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ObjetsGeometriques.h"

/* Variables globales                           */

static float rx = 0.0F;            // Angle de rotation de la scene sur elle-meme autour de l'axe x
static float sens = 1.0F;          // Sens de rotation de la scene sur elle-meme autour de l'axe x
static float ry = 0.0F;            // Angle de rotation de la scene sur elle-meme autour de l'axe y
static float rz = 0.0F;            // Angle de rotation de la scene sur elle-meme autour de l'axe z
static int anim = 0;               // Flag d'activation/desactivation de l'animation
static int mouseActive = 0;        // Flag de d'indication que la souris est active (bouton presse) ou non 
static int mouseX = 0;             // Derniere position en x relevee pour la souris

static int wTx = 360;              // Resolution horizontale de la fenetre
static int wTy = 360;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre

static int polygonMode = 1;        // Flag de switch entre modes d'affichage wireframe et fill 
static int scn = 3;                // Flag de switch entre les 4 scenes
static int normalize = 1;          // Flag de switch avec et sans normalisation
static int n = 50;                 // Niveau de facettisation
static int fond = 1;               // Flag de switch entre couleurs de fond noir et gris clair
static int culling = 0;            // Flag de switch entre affichages avec et sans culling
static int lightsAndMaterials = 1; // Flag de switch entre affichage avec lumière et materiaux
static int lights[4] = { 0,0,0,0 };// Flags d'activation les lumières 1 à 4

// Paramètres des lumières
static float ambient[4] = { 0.5, 0.5, 0.5, 1.0 };
static float diffuse[4] = { 1.0, 0.0, 0.0, 1.0 };
static float diffuse_white[4] = { 1.0, 1.0, 1.0, 1.0 };
static float specular[4] = { 1.0, 1.0, 1.0, 1.0 };

static float light_1_pos[] = { 1.0, 0.0, 0.0, 0.0};
static float light_2_pos[] = { -1.0, 0.0, 0.0, 0.0};
static float light_3_pos[] = { 5.0, 5.0, 5.0, 1.0};
static float light_4_pos[] = { -5.0, -5.0, 10.0, 1.0 };
static float light_4_direction[] = { 1.0, 1.0, -2.0 };
static float light_4_cutoff = 2;

// Paramètres des materiaux
static float m_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
static float m_shininess[] = { 50.0 };

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse_white);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}

//////////////////////////////////////////////////

/* Scene dessinee                               */

static void scene0(void) {
  glPushMatrix();
  glColor3f(0.8F,0.8F,0.0F);
  glutSolidSphere(0.8,n,n);
  glTranslatef(0.4F,0.4F,0.4F);
  glColor3f(0.0F,0.8F,0.8F);
  glutSolidSphere(0.4,n,n);
  glPopMatrix();
}

static void scene1(void) {
  glPushMatrix();
  glColor3f(0.8F,0.0F,0.8F);
  mySolidCube(1.0,n);
  glTranslatef(0.4F,0.4F,0.4F);
  glColor3f(0.8F,0.8F,0.8F);
  mySolidCube(0.6,n);
  glPopMatrix();
}

static void scene2(void) {
  glPushMatrix();
  glColor3f(0.0F,0.8F,0.0F);
  mySolidCylindre(1.2,0.6,n*3,n,1);
  glTranslatef(0.6F,0.4F,0.4F);
  glColor3f(0.8F,0.0F,0.0F);
  mySolidCylindre(0.6,0.3,n*3,n,1);
  glPopMatrix();
}

static void element(void) {
  glPushMatrix();
  mySolidCylindre(0.9,0.2,n,n*2);
  glPushMatrix();
  glTranslatef(0.75F,-0.75F,0.0F);
  glRotatef(90.0F,0.0F,0.0F,1.0F);
  mySolidCylindre(0.9,0.2,n,n*2);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.75F,0.75F,0.0F);
  glRotatef(90.0F,0.0F,0.0F,1.0F);
  mySolidCylindre(0.9,0.2,n,n*2);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.0F,-0.75F,0.0F);
  mySolidCube(0.6,n);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.0F,0.75F,0.0F);
  mySolidCube(0.6,n);
  glPopMatrix();
  glPopMatrix();
}

static void scene3(void) {
  glPushMatrix();
  glColor3f(1.0F,1.0F,1.0F);
  glutSolidSphere(0.5,n,n);
  for ( int i = 0 ; i < 4 ; i++ ) {
    glPushMatrix();
    glRotatef(i*90.0F,0.0F,1.0F,0.0F);
    glTranslatef(-0.75F,0.0,0.75F);
    element();
    glPopMatrix(); }
  glPopMatrix();
}

//////////////////////////////////////////////////

static void checkLights() {
    if (lights[0])
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    if (lights[1])
        glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);
    if (lights[2])
        glEnable(GL_LIGHT3);
    else
        glDisable(GL_LIGHT3);
    if (lights[3])
        glEnable(GL_LIGHT4);
    else
        glDisable(GL_LIGHT4);
}  

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    if (culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,( polygonMode ) ? GL_FILL : GL_LINE);
    if (normalize)
        glEnable(GL_NORMALIZE);
    else
        glDisable(GL_NORMALIZE);
    if (fond) 
        glClearColor(0.0F,0.0F,0.0F,1.0F);
    else
        glClearColor(0.8F,0.8F,0.8F,1.0F);
    if (lightsAndMaterials)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);
    checkLights();

    glPolygonMode(GL_FRONT_AND_BACK,(polygonMode == 1) ? GL_FILL : GL_LINE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glLightfv(GL_LIGHT1, GL_POSITION, light_1_pos);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, light_4_cutoff);
    glLightfv(GL_LIGHT3, GL_POSITION, light_3_pos);
    glLightfv(GL_LIGHT2, GL_POSITION, light_2_pos);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light_4_direction);
    glLightfv(GL_LIGHT4, GL_POSITION, light_4_pos);

    glRotatef(rx,1.0F,0.0F,0.0F);
    glRotatef(ry,0.0F,1.0F,0.0F);
    glRotatef(rz,0.0F,0.0F,1.0F);

    glScalef(0.6F,0.6F,0.6F);

    switch (scn) {
        case 0 :
            scene0();
            break;
        case 1 :
            scene1();
            break;
        case 2 :
            scene2();
            break;
        case 3 :
            scene3();
            break; 
    }

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if ( error != GL_NO_ERROR )
    printf("Attention erreur %d\n",error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx,int wy) {
  wTx = wx; 
  wTy = wy; 
  glViewport(0,0,wx,wy); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double ratio =(double) wx/wy; 
  if ( wx > wy ) 
    glOrtho(-ratio,ratio,-1.0,1.0,-2.0,2.0);
    else
    glOrtho(-1.0,1.0,-1.0/ratio,1.0/ratio,-2.0,2.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
  rx += sens;
  ry += sens;
  rz += sens;
  glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key,int x,int y) {
    printf("K %x\n", key);
    switch (key) {
    case 'n' :
        n--;
        if ( n < 1 )
        n = 1;
        glutPostRedisplay();
        break;
    case 'N' :
        n++;
        glutPostRedisplay();
        break;
    case 's' :
    case 'S' :
        { scn = (scn+1)%4;
        glutPostRedisplay(); }
        break;
    case 'f' :
        fond = !fond;
        glutPostRedisplay();
        break;
    case 0x0D :
        { anim = !anim;
        glutIdleFunc(( anim ) ? idle : NULL); }
        break;
    case 'c' :
        culling = !culling;
        glutPostRedisplay();
        break;
    case 'm' :
        polygonMode = !polygonMode;
        glutPostRedisplay();
        break;
    case 0x20 :
        normalize = !normalize;
        glutPostRedisplay();
        break;
    case 0x1B :
        exit(0);
        break; }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey,int x,int y) {
    printf("S %x\n", specialKey);
    float incr = 1;
    switch(specialKey) {
    case GLUT_KEY_RIGHT :
        ry += 2.0F;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT :
        ry -= 2.0F;
        glutPostRedisplay();
        break; 
    case GLUT_KEY_F10 :
        lightsAndMaterials = 1 - lightsAndMaterials;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F1 :
        lights[0] = 1 - lights[0];
        glutPostRedisplay();
        break;
    case GLUT_KEY_F2:
        lights[1] = 1 - lights[1];
        glutPostRedisplay();
        break;
    case GLUT_KEY_F3:
        lights[2] = 1 - lights[2];
        glutPostRedisplay();
        break;
    case GLUT_KEY_F4:
        lights[3] = 1 - lights[3];
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        if (light_4_cutoff < 1)
            incr = 0.1;
        light_4_cutoff = min(light_4_cutoff+incr, 180);
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        if (light_4_cutoff <= 1)
            incr = 0.1;
        light_4_cutoff = max(light_4_cutoff - incr, 0.1);
        glutPostRedisplay();
        break;
    }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button,int state,int x,int y) {
    printf("M\n");
  if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) ) {
    mouseX = x;
    mouseActive = 1; }
  if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_UP ) ) {
    mouseActive = 0; }
  if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_UP ) )
    sens *= -1.0F;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x,int y) {
    printf("M\n");
  if ( mouseActive ) {
    rz += (mouseX - x);
    mouseX = x;
    glutPostRedisplay(); }
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x,int y) {
}

/* Fonction exécutée automatiquement            */
/* lors de l'exécution de la fonction exit()    */

static void clean(void) {
  printf("Bye\n");
}

/* Fonction principale                          */

int main(int argc,char **argv) {

  atexit(clean);

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(wTx,wTy);
  glutInitWindowPosition(wPx,wPy);
  glutCreateWindow("Materiaux et lumieres");
  init();
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
