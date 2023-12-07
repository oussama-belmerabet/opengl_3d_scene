#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


// LES VARIABLES GLOBALES
int droite=1;
GLfloat   rouler=0.0 ;
GLfloat  i,j,k,n , pos,rouler1;
int x_lum=500;
GLUquadric *params;
GLUquadric *params2;
int rotation = 0;

float move_left_car =0.0f;
float move_left_car_1 =0.0f;

float treeX = 0.0f;
float treeY = 0.0f;



/*  Variables Globale de la gestion clavier souris-------------*/

static int l = 1;

static float px =-25.42;              //0.0F;
static float py =9.0;                    //4.5F;
static float pz =80.14;                         // -30.0F;
static float angle = 2.83;                           //0.0F;
static float ouv = 60.0F;
static int mouvement = 0 ;
static int button = 0 ;
static int mx;
static int my;
//static int pos;
//static int rouler1;
static int v =25;
//   Les variable de l'illumination
GLfloat posL0[]={1,10,0,0};
GLfloat diff[]={1,1,1},amb[]={0.5,0.5,0.5},spec[]={1,1,1};





/* +++++++++++++++++++++++++++++++++++++GESTION CLAVIER SOURIS+++++++++++++++++++*/

void keyboard(unsigned char key,int x,int y) {
  switch ( key ) {
    case 0x0D : l = !l ;
                glutPostRedisplay();
                break;

  case 'y' :

               /* py=py+1;
                glutPostRedisplay();
                break;*/
            if(py<39){
                py=py+1;
                glutPostRedisplay();
                break;
            }
  case 'u' :

                py=py-1;
                glutPostRedisplay();
                break;
             case '1' :

                pos= rouler;
                rouler1=0;
                glutPostRedisplay();
                break;
                  case '2' :

                pos= rouler;
                rouler1=1;
                glutPostRedisplay();
                break;

          if (py>1){
         py=py-1;
         glutPostRedisplay();
          break;

}
/*  case 'z' :

                rouler=rouler-1;
                glutPostRedisplay();
                break;
  case 'w' :

                rouler=rouler+1;
                glutPostRedisplay();
                break;*/
  case '+' :
      v=v-3;
      glutPostRedisplay();
      break;
  case '-' :
      v=v+3;
      glutPostRedisplay();
      break;

       case 'c':

        px=-1.44; py=9.0; pz=4; angle=2.93;
        gluLookAt(px,py,pz,px+sin(angle),py,pz+cos(angle),0.0,1.0,0.0);

      break;
       case 'g':

        px=-28.44; py=6.0; pz=-0.14; angle=2.93;
        gluLookAt(px,py,pz,px+sin(angle),py,pz+cos(angle),0.0,1.0,0.0);

      break;
    case 'n':

        px=19.44; py=5.8; pz=1.6; angle=1.93;
        gluLookAt(px,py,pz,px+sin(angle),py,pz+cos(angle),0.0,1.0,0.0);

      break;
        case 's':

        px=2.42; py=9.0; pz=-30.14; angle=2.33;
        gluLookAt(px,py,pz,px+sin(angle),py,pz+cos(angle),0.0,1.0,0.0);

      break;
       case 'm':

        px=-0.42; py=9.0; pz=52.14; angle=2.83;
        gluLookAt(px,py,pz,px+sin(angle),py,pz+cos(angle),0.0,1.0,0.0);

      break;
       case 't':

        px=-0.42; py=29.0; pz=-9; angle=2.83;
        gluLookAt(px,py,pz,px+sin(angle),py,pz+cos(angle),0.0,1.0,0.0);

      break;

   case 'p' :

        printf("%f\n %f\n %f\n %f\n",px,py,pz,angle);

                break;

    case 0x1B : exit(0); }
}

/* Fonction executee lors de l'appui            */
/* d'une touche de la souris                    */

void mouse(int bouton,int etat,int x,int y) {
  button = bouton;
  mx = x ;
  my = y ;
  if ( etat == GLUT_DOWN ) {
    mouvement = 1 ; }
  if ( etat == GLUT_UP ) {
    mouvement = 0 ; }
}

/* Fonction executee lors du deplacement        */
/* de la souris devant la fenetre               */
/* avec le bouton appuye                        */



void motion(int x,int y) {
  switch ( button ) {
    case GLUT_LEFT_BUTTON :
      if ( mouvement == 1 ) {
        px += 0.1F*sin(angle)*(my-y)/5.0F ;
        pz += 0.1F*cos(angle)*(my-y)/5.0F ;
        angle += (x-mx)/200.0F ;
        mx = x;
        my = y;
        glutPostRedisplay(); }
        break; }
}

/* Fonction executee lors de la frappe          */
/* d'une touche non alphanumerique du clavier   */

void special(int key,int x,int y) {
  switch ( key ) {
    case GLUT_KEY_UP      : px += 0.7F*sin(angle);
                            pz += 0.7F*cos(angle);
                            glutPostRedisplay();
                            break;
    case GLUT_KEY_DOWN    : px -= 0.7F*sin(angle);
                            pz -= 0.7F*cos(angle);
                            glutPostRedisplay();
                            break;
    case GLUT_KEY_RIGHT   : angle -= 0.13F;
                            glutPostRedisplay();
                            break;
    case GLUT_KEY_LEFT    : angle += 0.13F;
                            glutPostRedisplay();
                            break; }
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/




void monCadrage( int  width, int height)
{

glViewport( 0,0, width, height );              /* On ajuste la nouvelle taille du viewport. */
glMatrixMode( GL_MODELVIEW );

}

 void monInitscene()
{
glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* L’écran sera effacé aavec  la couleur noir.*/
glClearDepth( 1.0 );                /* Le tampon Z est effacé à 1. */
glEnable( GL_DEPTH_TEST );


}

// LA CAMERA

void maCamera(){
    glMatrixMode( GL_PROJECTION );          /* Mode matrice de projection.*/
    glLoadIdentity();                       /* La matrice de projection est la matrice identitée… */
    gluPerspective( ouv, (double)400 / 400, 1, 300.0 );

    gluLookAt(px,py,pz,px+sin(angle),py,pz+cos(angle),0.0,1.0,0.0);
    }


void timer(int theTimer){
    rotation++;
    if(droite==1){
        rouler ++ ;

        if(rouler>80){
            droite=0;
            }
        }

     else{
        rouler -- ;
        if(rouler<-80){
            droite=1;
            }
         }

    glutPostRedisplay() ;
    glutTimerFunc(v, timer, 0) ;
    }





//La route verticale
void route_1() {
    GLfloat ir;
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);

    // Ajuster la longueur de la route (changer les valeurs x)
    glVertex3f(-150, 0.2, 57);  // Point 1
    glVertex3f(150, 0.2, 57);   // Point 2
    glVertex3f(150, 0.2, 67);   // Point 3
    glVertex3f(-150, 0.2, 67);  // Point 4
    glEnd();

    // Dessiner des bandes blanches (lignes parallèles à la route)
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    // Ajuster la largeur et la longueur des bandes selon vos besoins
    GLfloat stripeWidth = 2.0;
    GLfloat stripeLength = 15.0;  // Ajustez la longueur des bandes ici
    GLfloat stripeSpacing = 20.0;

    // Dessiner des bandes blanches le long de la route
    for (GLfloat i = -150; i < 150; i += stripeSpacing + stripeLength) {
        glVertex3f(i, 0.21, 62);                // Point 1
        glVertex3f(i + stripeLength, 0.21, 62);  // Point 2
        glVertex3f(i + stripeLength, 0.21, 64);  // Point 3
        glVertex3f(i, 0.21, 64);                // Point 4
    }

    glEnd();
    }


void route_2() {
    GLfloat ir;
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);

    // Ajuster les coordonnées pour la deuxième route (orientation horizontale)
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-20, 0.2, -100);  // Point 1
    glVertex3f(-20, 0.2, 200);    // Point 2
    glVertex3f(-30, 0.2, 200);    // Point 3
    glVertex3f(-30, 0.2, -100);  // Point 4
    glEnd();

    // Dessiner des bandes blanches (lignes parallèles à la route)
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    // Ajuster la largeur et la longueur des bandes selon vos besoins
    GLfloat stripeWidth = 2.0;
    GLfloat stripeLength = 15.0;  // Ajustez la longueur des bandes ici
    GLfloat stripeSpacing = 20.0;

    // Dessiner des bandes blanches le long de la route
    for (GLfloat i = -100; i < 150; i += stripeSpacing + stripeLength) {
        glVertex3f(-25, 0.21, i);                // Point 1
        glVertex3f(-25, 0.21, i + stripeLength);  // Point 2
        glVertex3f(-27, 0.21, i + stripeLength);  // Point 3
        glVertex3f(-27, 0.21, i);                // Point 4
    }

    glEnd();
    }

GLfloat frameNumber = 0;
bool isKeyOn = true;

void drawWindmill(float scale) {
    int i;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.05f * scale, 0, 0);
    glVertex3f(0.05f * scale, 0, 0);
    glVertex3f(0.05f * scale, 3 * scale, 0);
    glVertex3f(-0.05f * scale, 3 * scale, 0);
    glEnd();

    glTranslatef(0, 3 * scale, 0);

    if (isKeyOn == true) {
        glRotated(rotation * (360.0 / 96), 0, 0, 1); // z-axis rotation speed
    }

    // Blade er pakha
    glColor3ub(0, 0, 0);

    for (i = 0; i < 3; i++) { // Blade er pakha no
        glRotated(120, 0, 0, 1); // Blader er pakha space
        glBegin(GL_POLYGON);
        glVertex3f(0, 0, 0);
        glVertex3f(0.5f * scale, 0.1f * scale, 0);
        glVertex3f(1.5f * scale, 0, 0);
        glVertex3f(0.5f * scale, -0.1f * scale, 0);
        glEnd();
    }
}

void tree(){



}

//Les arbres
void arbres(){
    params = gluNewQuadric();
    gluQuadricDrawStyle(params, GLU_FILL);
   	glLoadIdentity();
   	for(i=-70;i<80;i=i+19){
        // Positionne l'arbre
        glColor3ub(172,104,17);
        glTranslatef (i,3,70);
        glRotatef (90,1,0,0);
        glScalef(0.4,0.8,0.8);
        GLUquadricObj *p = gluNewQuadric();
        gluCylinder (p,1,1,3,30,30);
        glLoadIdentity ();

        glColor3ub(36,100,20);
        glTranslatef (i,3,70);
        glRotatef (270,1,0,0);
        glScalef(0.8,0.8,0.8);
        glutSolidCone(3, 3, 25, 25);
        glLoadIdentity ();

        glColor3ub(36,100,20);
        glTranslatef (i,4,70);
        glRotatef (270,1,0,0);
        glScalef(0.8,0.8,0.8);
        glutSolidCone(3, 3, 25, 25);
        glLoadIdentity ();

        glColor3ub(36,100,20);
        glTranslatef (i,5,70);
        glRotatef (270,1,0,0);
        glScalef(0.8,0.8,0.8);
        glutSolidCone(3, 3, 25, 25);
        glLoadIdentity ();
        }

        for(i=-70;i<80;i=i+19){
        glColor3ub(172,104,17);
        glTranslatef (i,3,50);
        glRotatef (90,1,0,0);
        glScalef(0.4,0.8,0.8);
        GLUquadricObj *p = gluNewQuadric();
        gluCylinder (p,1,1,3,30,30);
        glLoadIdentity ();


        glColor3ub(36,100,20);
        glTranslatef (i,3,50);
        glRotatef (270,1,0,0);
        glScalef(0.8,0.8,0.8);
        glutSolidCone(3, 3, 25, 25);
        glLoadIdentity ();


        glColor3ub(36,100,20);
        glTranslatef (i,4,50);
        glRotatef (270,1,0,0);
        glScalef(0.8,0.8,0.8);
        glutSolidCone(3, 3, 25, 25);
        glLoadIdentity ();

        glColor3ub(36,100,20);
        glTranslatef (i,5,50);
        glRotatef (270,1,0,0);
        glScalef(0.8,0.8,0.8);
        glutSolidCone(3, 3, 25, 25);
        glLoadIdentity ();
        }

    }








//Ciel
void ciel(){
    glColor3ub( 173,212,247);
	glutSolidSphere(200,20,20);
    }

//Soleil
 void sun(){
    glLoadIdentity();
    glColor3ub(255,255,120);
    glTranslatef(-35.2,33.5,-50);
    glutSolidSphere(2.6,70,70);
    }





//Clouds
void clouds(){
    glLoadIdentity();
    glColor3ub(255,255,255);
    glTranslatef(-10.2+rouler,40.5,-46);
    glutSolidSphere(2.6,70,70);

    glLoadIdentity();
    glColor3ub(255,255,255);
    glTranslatef(-14.2+rouler,39,-46);
    glutSolidSphere(2.6,70,70);

    glLoadIdentity();
    glColor3ub(255,255,255);
    glTranslatef(-10.2+rouler,39,-46);
    glutSolidSphere(2.6,70,70);

    glLoadIdentity();
    glColor3ub(255,255,255);
    glTranslatef(-7.2+rouler,39,-46);
    glutSolidSphere(2.6,70,70);
    }




   void drawHouse(float scale, float xPos, float yPos, float zPos) {


    // Apply translation to position the house
    glTranslatef(xPos, yPos, zPos);

    // Apply scaling to the house
    glScalef(scale, scale, scale);
    //sets front wall to blue color
    glColor3f( 0.4, 0.4, 0.9 );
    glFrontFace ( GL_CCW );
    glPolygonMode( GL_FRONT, GL_FILL );
    //glPolygonMode( GL_BACK, GL_LINE );

    glBegin( GL_POLYGON );
    glVertex3i( -1, 0, -2);
    glVertex3i( -1, 1, -2);
    glVertex3i( 1, 1, -2);
    glVertex3i( 1, 0, -2);
    glEnd();

    //sets wall color to light blue
    glColor3f( 0.4, 0.8, 1.0 );

    glFrontFace ( GL_CCW );

    //back wall
    glBegin( GL_POLYGON );
    glVertex3i( -1, 0, 1);
    glVertex3i( -1, 1, 1);
    glVertex3i( -1, 1, -2);
    glVertex3i( -1, 0, -2);
    glEnd();
    //blue

    glFrontFace ( GL_CW );
    glPolygonMode( GL_FRONT, GL_FILL );
    //sets color to light purple
    glColor3f( 0.5, 0.4, 0.9 );
    //left wall
    glBegin( GL_POLYGON );
    glVertex3i( -1, 0, 1);
    glVertex3i( -1, 1, 1);
    glVertex3i( 1, 1, 1);
    glVertex3i( 1, 0, 1);
    glEnd();

    //sets front wall color to light green
    glColor3f( 0.5, 0.9, 0.6 );
    //front wall
    glBegin( GL_POLYGON );
    glVertex3i( 1, 0, 1);
    glVertex3i( 1, 1, 1);
    glVertex3i( 1, 1, -2);
    glVertex3i( 1, 0, -2);
    glEnd();

    //deep saffron
    glColor3f(1.0, 0.6, 0.2 );
    glBegin( GL_TRIANGLES );
    //left roof
    glVertex3i(-1, 1, 1);
    glVertex3f( 0, 1.5, 0.5);
    glVertex3i( 1, 1, 1);


    //right roof
    glVertex3i( 1, 1, -2);
    glVertex3f( 0, 1.5, -1.5);
    glVertex3i( -1, 1, -2);
    glEnd();

    //sets part of roof color to dark brown
    glColor3f( 0.5,0.2,0.0 );
    //front roof
    glBegin( GL_POLYGON );
    glVertex3i( 1,1,1);
    glVertex3f( 0, 1.5, 0.5);
    glVertex3f( 0, 1.5, -1.5);
    glVertex3i( 1, 1, -2);
    glEnd();

    //sets back roof to color light brown
    glColor3f( 0.5,0.3,0.1 );
    //back roof
    glBegin( GL_POLYGON );
    glVertex3i( -1,1,1);
    glVertex3i( -1,1,-2);
    glVertex3f( 0, 1.5, -1.5);
    glVertex3f( 0,1.5,0.5);
    glEnd();

    //door
    //sets chocolate color to door
    glColor3f( 0.3,0.15,0 );
    glBegin( GL_POLYGON );
    glVertex3f( 1, 0, 0.8);
    glVertex3f( 1, 0.8, 0.8);
    glVertex3f( 1, 0.8, 0.4);
    glVertex3f( 1, 0, 0.4);
    glEnd();

    //front wall window
    //sets the color of door to light green
    glColor3f( 0.7,0.5,0.1 );
    glBegin( GL_POLYGON );
    glVertex3f( 1, 0.4, -0.8);
    glVertex3f( 1, 0.7, -0.8);
    glVertex3f( 1, 0.7, -1.5);
    glVertex3f( 1, 0.4, -1.5);
    glEnd();

    //left wall window
    //sets left wall window to color white
    glColor3f( 1.0,1.0,1.0 );
    glBegin( GL_POLYGON );
    glVertex3f( -0.8, 0.4, 1);
    glVertex3f( -0.8, 0.7, 1);
    glVertex3f( -0.3, 0.7, 1);
    glVertex3f( -0.3, 0.4, 1);

    glEnd();

    }

int drive = 5;
int theta3 = 2;
void drawCar()
{
    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
        glTranslatef(drive, 4.0f, -25);


        // Draw the main body of the car
        glPushMatrix();
        glColor3f(0.1, 0.0, 0.75);
        glScalef(10.0f, 3.0f, 6.0f);
        glutSolidCube(1.0);
        glPopMatrix();

        // Draw the vehicle tires
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);

        // Front left tire
        glPushMatrix();
        glTranslatef(5.0f, -2.0f, 3.5f);
        glRotatef(theta3, 0.0, 0.0, 1.0);
        glScalef(1.2f, 1.2f, 1.0f);
        glutSolidTorus(0.7, 0.7, 15.0, 55.0);
        glPopMatrix();

        // Front right tire
        glPushMatrix();
        glTranslatef(5.0f, -2.0f, -3.5f);
        glRotatef(theta3, 0.0, 0.0, 1.0);
        glScalef(1.2f, 1.2f, 1.0f);
        glutSolidTorus(0.7, 0.7, 15.0, 55.0);
        glPopMatrix();

        // Rear left tire
        glPushMatrix();
        glTranslatef(-5.0f, -2.0f, 3.5f);
        glRotatef(theta3, 0.0, 0.0, 1.0);
        glScalef(1.2f, 1.2f, 1.0f);
        glutSolidTorus(0.7, 0.7, 15.0, 55.0);
        glPopMatrix();

        // Rear right tire
        glPushMatrix();
        glTranslatef(-5.0f, -2.0f, -3.5f);
        glRotatef(theta3, 0.0, 0.0, 1.0);
        glScalef(1.2f, 1.2f, 1.0f);
        glutSolidTorus(0.7, 0.7, 15.0, 55.0);
        glPopMatrix();

        glPopMatrix();
    glPopMatrix();

    // Draw the road
    glPushMatrix();

    glPopMatrix();
}

void building(){
    ////BuildingsBackRow////

    ////1////
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.4,0.2, 0.0);
    glVertex3f(-0.66f, 0.0f, 0.0f);
    glVertex3f(-0.416f, 0.0f, 0.0f);
    glVertex3f(-0.416f, 0.25f, 0.0f);
    glVertex3f(-0.66f, 0.25f, 0.0f);
    glEnd();

    ////2////
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.8,1.0, 0.6);
    glVertex3f(-0.25f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.25f, 0.0f);
    glVertex3f(-0.25f, 0.25f, 0.0f);
    glEnd();

    ////3////
    glBegin(GL_POLYGON);
    glColor3f(0.6,0.0, 0.29);
    glVertex3f(0.33f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.25f, 0.0f);
    glVertex3f(0.33f, 0.25f, 0.0f);
    glEnd();

    ////4////
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.5);
    glVertex3f(0.833f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.25f, 0.0f);
    glVertex3f(0.833f, 0.25f, 0.0f);
    glEnd();

    /////BackRowBuildingWindow////

    ////1////
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.65f, 0.166f, 0.0f);
    glVertex3f(-0.566f, 0.166f, 0.0f);
    glVertex3f(-0.566f, 0.216f, 0.0f);
    glVertex3f(-0.65f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.65f, 0.15f, 0.0f);
    glVertex3f(-0.566f, 0.15f, 0.0f);
    glVertex3f(-0.566f, 0.1f, 0.0f);
    glVertex3f(-0.65f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.65f, 0.083f, 0.0f);
    glVertex3f(-0.566f, 0.083f, 0.0f);
    glVertex3f(-0.566f, 0.033f, 0.0f);
    glVertex3f(-0.65f, 0.033f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.55f, 0.166f, 0.0f);
    glVertex3f(-0.5f, 0.166f, 0.0f);
    glVertex3f(-0.5f, 0.216f, 0.0f);
    glVertex3f(-0.55f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.55f, 0.15f, 0.0f);
    glVertex3f(-0.5f, 0.15f, 0.0f);
    glVertex3f(-0.5f, 0.1f, 0.0f);
    glVertex3f(-0.55f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.55f, 0.083f, 0.0f);
    glVertex3f(-0.5f, 0.083f, 0.0f);
    glVertex3f(-0.5f, 0.033f, 0.0f);
    glVertex3f(-0.55f, 0.033f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.483f, 0.166f, 0.0f);
    glVertex3f(-0.433f, 0.166f, 0.0f);
    glVertex3f(-0.433f, 0.216f, 0.0f);
    glVertex3f(-0.483f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.483f, 0.15f, 0.0f);
    glVertex3f(-0.433f, 0.15f, 0.0f);
    glVertex3f(-0.433f, 0.1f, 0.0f);
    glVertex3f(-0.483f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.69, 0.4);
    glVertex3f(-0.483f, 0.083f, 0.0f);
    glVertex3f(-0.433f, 0.083f, 0.0f);
    glVertex3f(-0.433f, 0.033f, 0.0f);
    glVertex3f(-0.483f, 0.033f, 0.0f);
    glEnd();

    ////2////
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.233f, 0.166f, 0.0f);
    glVertex3f(-0.166f, 0.166f, 0.0f);
    glVertex3f(-0.166f, 0.216f, 0.0f);
    glVertex3f(-0.233f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.233f, 0.15f, 0.0f);
    glVertex3f(-0.166f, 0.15f, 0.0f);
    glVertex3f(-0.166f, 0.1f, 0.0f);
    glVertex3f(-0.233f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.233f, 0.083f, 0.0f);
    glVertex3f(-0.166f, 0.083f, 0.0f);
    glVertex3f(-0.166f, 0.033f, 0.0f);
    glVertex3f(-0.233f, 0.033f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.15f, 0.166f, 0.0f);
    glVertex3f(-0.066f, 0.166f, 0.0f);
    glVertex3f(-0.066f, 0.216f, 0.0f);
    glVertex3f(-0.15f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.15f, 0.15f, 0.0f);
    glVertex3f(-0.066f, 0.15f, 0.0f);
    glVertex3f(-0.066f, 0.1f, 0.0f);
    glVertex3f(-0.15f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.15f, 0.083f, 0.0f);
    glVertex3f(-0.066f, 0.083f, 0.0f);
    glVertex3f(-0.066f, 0.033f, 0.0f);
    glVertex3f(-0.15f, 0.033f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.05f, 0.166f, 0.0f);
    glVertex3f(0.0f, 0.166f, 0.0f);
    glVertex3f(0.0f, 0.216f, 0.0f);
    glVertex3f(-0.05f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.05f, 0.15f, 0.0f);
    glVertex3f(0.0f, 0.15f, 0.0f);
    glVertex3f(0.0f, 0.1f, 0.0f);
    glVertex3f(-0.05f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.4, 0.4);
    glVertex3f(-0.05f, 0.083f, 0.0f);
    glVertex3f(0.0f, 0.083f, 0.0f);
    glVertex3f(0.0f, 0.033f, 0.0f);
    glVertex3f(-0.05f, 0.033f, 0.0f);
    glEnd();

    ////3////
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.8, 1.0);
    glVertex3f(0.366f, 0.166f, 0.0f);
    glVertex3f(0.466f, 0.166f, 0.0f);
    glVertex3f(0.466f, 0.216f, 0.0f);
    glVertex3f(0.366f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.8, 1.0);
    glVertex3f(0.366f, 0.15f, 0.0f);
    glVertex3f(0.466f, 0.15f, 0.0f);
    glVertex3f(0.466f, 0.1f, 0.0f);
    glVertex3f(0.366f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.8, 1.0);
    glVertex3f(0.366f, 0.083f, 0.0f);
    glVertex3f(0.466f, 0.083f, 0.0f);
    glVertex3f(0.466f, 0.033f, 0.0f);
    glVertex3f(0.366f, 0.033f, 0.0f);
    glEnd();

    ////4////
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0, 0.4);
    glVertex3f(0.866f, 0.166f, 0.0f);
    glVertex3f(0.966f, 0.166f, 0.0f);
    glVertex3f(0.966f, 0.216f, 0.0f);
    glVertex3f(0.866f, 0.216f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0, 0.4);
    glVertex3f(0.866f, 0.15f, 0.0f);
    glVertex3f(0.966f, 0.15f, 0.0f);
    glVertex3f(0.966f, 0.1f, 0.0f);
    glVertex3f(0.866f, 0.1f, 0.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0, 0.4);
    glVertex3f(0.866f, 0.083f, 0.0f);
    glVertex3f(0.966f, 0.083f, 0.0f);
    glVertex3f(0.966f, 0.033f, 0.0f);
    glVertex3f(0.866f, 0.033f, 0.0f);
    glEnd();


}


void drawCity() {
    // Draw roads



    route_1();

    route_2();
    drawCar();

    // Draw trees

    drawHouse(2.5, -7.0, 0.0, 0.0);
    // Draw the second house with scale 1.5 at a different position
    drawHouse(2.5, 7.0, 0.0, 0.0);


    arbres();















    // Draw windmills
    for (int i = -100; i <= 100; i += 40) {
        for (int j = -80; j <= 80; j += 40) {
            glLoadIdentity();
            glTranslatef(i, 0, j);
            drawWindmill(10);
        }
    }
}




static void key(unsigned char key, int x, int y)
{
    switch (key)
    {


        case 's':
            theta3 += 5;
            drive -= 1;
            break;

        case 'z':
            theta3 -= 5;
            drive += 1;
            break;

            case 'y' :

               /* py=py+1;
                glutPostRedisplay();
                break;*/
            if(py<39){
                py=py+1;
                glutPostRedisplay();
                break;
            }
  case 'u' :

                py=py-1;
                glutPostRedisplay();
                break;
             case '1' :

                pos= rouler;
                rouler1=0;
                glutPostRedisplay();
                break;
                  case '2' :

                pos= rouler;
                rouler1=1;
                glutPostRedisplay();
                break;

          if (py>1){
         py=py-1;
         glutPostRedisplay();
          break;}
    }

    glutPostRedisplay();
}

void display(void){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); /* Efface les tampons d’affichage (ecran) avec la coleur noir et Z.*/
    glLoadIdentity();
    maCamera();

    glMatrixMode( GL_MODELVIEW );

    glLoadIdentity();

 //DESSIN PLAN
    glBegin(GL_QUADS);
    glColor3ub(1, 50, 32);
    glVertex3f(-500,0,500);
    glVertex3f(500,0,500);
    glVertex3f(500,0,-500);
    glVertex3f(-500,0,-500);
    glEnd();

     drawCity();

    ciel();
    clouds();


    sun();




    glLoadIdentity();
    glLoadIdentity();
    glutSwapBuffers();

    }

int main( int argc, char** argv ){

    glutInit( &argc, argv );

    // Obtenir la largeur et la hauteur de l'écran
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Initialiser la fenêtre avec la taille de l'écran
    glutInitWindowSize(screenWidth, screenHeight);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Ville");

    monInitscene();

    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutSpecialFunc(special);
    glutTimerFunc(35, timer, 0) ;



    glutDisplayFunc(display);
    glutReshapeFunc( monCadrage);

    glutMainLoop();
    return 0;
}
