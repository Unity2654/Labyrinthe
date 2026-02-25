/* Objets geometriques modelises par facettes   */
/*  - Cube                                      */
/*  - Cylindre                                  */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Fevrier 2023                                 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef M_PI
#define M_PI 3.14159
#endif

static void face(float tx,float ty, int n,int m) {
  float dy = ty/m;
  float dx = tx/n;
  glPushMatrix();
  glNormal3f(0.0F,0.0F,1.0F);
  glTranslatef(-tx/2.0F,-ty/2.0F,0.0F);
  for ( int l = 0 ; l < m ; l++) {
    float yf = l * dy;
    float yi = yf + dy;
    float x = 0.0F;
    glBegin(GL_QUAD_STRIP);
    for ( int c = 0 ; c <= n ; c++ ) {
      glVertex2f(x,yi);
      glVertex2f(x,yf);
      x += dx; }
    glEnd(); }
  glPopMatrix();
}

void mySolidCube(double ct,int n) {
  glPushMatrix();
  glPushMatrix();
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(90.0F,0.0F,1.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(180.0F,0.0F,1.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(270.0F,0.0F,1.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(-90.0F,1.0F,0.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPopMatrix();
}

void mySolidCylindre(double hauteur,double rayon,int ns,int nl) {
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  for ( int j = 0 ; j < nl ; j++ ) {
    float hi =(float) (hauteur/2-j*hauteur/nl);
    float hf =(float) (hi-hauteur/nl);
    glBegin(GL_QUAD_STRIP);
    for( int i = 0 ; i <= ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      glNormal3f(cs,0.0F,sn);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,hi,z);
      glVertex3f(x,hf,z); }
    glEnd(); }
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

void mySolidCylindre(double hauteur,double rayon,int ns,int nl,int bases) {
  mySolidCylindre(hauteur,rayon,ns,nl);
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  if ( bases ) {
    glBegin(GL_POLYGON);
    glNormal3f(0.0F,1.0F,0.0F);
    for( int i = 0 ; i < ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,(float) (hauteur/2.0F),z); }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0.0F,-1.0F,0.0F);
    for( int i = 0 ; i < ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) sin(a);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,(float) (-hauteur/2.0F),z); }
    glEnd(); }
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}
