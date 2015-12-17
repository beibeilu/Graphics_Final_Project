//
// File: FinalProject.cc
// Author: Jialei Fu, Beibei Lu, Wenqi Fan
// Description: This is an simple 3D game called Landing the Earth.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <stdlib.h>
#include <math.h>
#include <time.h>   // time (for random seed)
#include <stdlib.h> // random number stuff (srand, rand)
#include <iostream>

using namespace std;

// define global state variables
GLfloat light0Pos[] = {5.0, 10.0, 0.0, 0.0};
GLfloat light1Pos[] = {-5.0, 10.0, 0.0, 0.0};

// theta, phi, and dist are the eye position in 3d polar coordinates
float theta=0;       // eye position to z-axis
float phi=15;          // eye position to x-z plane
float dist=30.0;

bool startGame;
int game = 1; //1 =simple, 2= medium, 3= hardq
float speed;
int whichView = 1;//1=world, 2=ball1, 3=ball2
// data for the spheres' positions
float s1XPos, s1YPos,s1ZPos, s1XTheta, s1YTheta, s1ZTheta,s1Radius;
float s1XDelta, s1YDelta, s1ZDelta;
float s1XThetaDelta, s1YThetaDelta, s1ZThetaDelta;
float s2XPos, s2YPos, s2ZPos, s2XTheta, s2YTheta, s2ZTheta, s2Radius;
float s2XDelta, s2YDelta, s2ZDelta;
float s2XThetaDelta, s2YThetaDelta, s2ZThetaDelta;
float pXPos, pYPos, pZPos, pRadius;

void setCamera(void)
{
    // set the view transformation
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -dist);
    glRotatef(phi, 1.0, 0.0, 0.0);
    glRotatef(theta, 0.0, 1.0, 0.0);
}

void playerView() //camera in player
{
    glLoadIdentity();
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef( -pXPos+pRadius*3, -pYPos, -pZPos);
    
}


void drawGameOver()
{
    //animation for game over
    
}

void gameOver()
{
    startGame = false;
    pXPos = 0.0;
    pYPos = 15.0;
    pZPos = 0.0;
    
    drawGameOver();
    
}

// return a random integer between low  and high
double randomf(double low, double high)
{
    double r =  ((double)rand())/RAND_MAX;
    return r*(high-low) + low;
}

void init(void)
{
    
    // define light property parameters
    GLfloat lightAmbient0[] = {0.2, 0.2, 1.0, 1.0};
    GLfloat lightAmbient1[] = {1.0, 0.2, 0.2, 1.0};
    GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSpecular[]= {1.0, 1.0, 1.0, 1.0};
    
    
    // define material property parameters
    GLfloat matSpecular[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat matShininess =   100.0;
    
    
    // define clear color to be black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    
    // World
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    
    // We'll use glColor to set the diffuse and ambient material properties
    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);
    
    // enable light sources
    glEnable (GL_LIGHT0);
    glEnable (GL_LIGHT1);
    
    // define default material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
    
    
    
    // shade polygons as flat surfaces
    glShadeModel(GL_FLAT);
    
    // do depth testing
    glEnable( GL_DEPTH_TEST );
    
    // initialize data structures
    // seed the random number generator
    srand (time (0));
    
    // game doea not start yet
    startGame = false;
    
    // normal speed
    speed = 1.0;
    
    // initialize world data structures
    s1Radius = 0.75;
    // position and movemnet are all random
    s1XPos = randomf( -5.0+s1Radius, 5.0-s1Radius );
    s1YPos = randomf( -15.0+s1Radius, 15.0-s1Radius );
    s1ZPos = randomf( -5.0+s1Radius, 5.0-s1Radius );
    s1XTheta = randomf( -180.0, 180.0 );
    s1YTheta = randomf( -180.0, 180.0 );
    s1ZTheta = randomf( -180.0, 180.0 );
    s1XDelta = randomf( 0.0, 0.2 );
    s1YDelta = randomf( 0.0, 0.2 );
    s1ZDelta = randomf( 0.0, 0.2 );
    s1XThetaDelta = randomf( -5.0, 5.0 );
    s1YThetaDelta = randomf( -5.0, 5.0 );
    s1ZThetaDelta = randomf( -5.0, 5.0 );
    
    s2Radius = 1.5;
    // position and movement are all random
    s2XPos = randomf( -5.0+s2Radius, 5.0-s2Radius );
    s2YPos = randomf( -15.0+s2Radius, 15.0-s2Radius );
    s2ZPos = randomf( -5.0+s2Radius, 5.0-s2Radius );
    s2XTheta = randomf( -180.0, 180.0 );
    s2YTheta = randomf( -180.0, 180.0 );
    s2ZTheta = randomf( -180.0, 180.0 );
    s2XDelta = randomf( 0.0, 0.2 );
    s2YDelta = randomf( 0.0, 0.2 );
    s2ZDelta = randomf( 0.0, 0.2 );
    s2XThetaDelta = randomf( -5.0, 5.0 );
    s2YThetaDelta = randomf( -5.0, 5.0 );
    s2ZThetaDelta = randomf( -5.0, 5.0 );
    
    pRadius = 0.3;
    pXPos = 0.0;
    pYPos = 15.0;
    pZPos = 0.0;
    
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 1 );    //enables lighting for both front and back faces of polygons.
    
    glEnable( GL_NORMALIZE);
    
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.01, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer( int val )
{
    if (startGame)
    {
        // register callback to executer again in .1 seconds
        glutTimerFunc (100,timer,0);
        
        // adjust position of sandglass in x-axes
        pYPos -= 0.2;
        if (pYPos > 15.0){
            pYPos = 15.0;
        }
        if (pYPos < -15.0) //game win and difficulty increases until win the difficult mode
        {
            pYPos = 15.0;
            
            speed += 5.0;
            if( game <= 3)
            {
                game += 1;
            } else gameOver();
        }

        
        // redraw everything
        glutPostRedisplay ();
    }
    
    // move the first sphere, bouncing off the edge if it hits it
    s1XPos += s1XDelta * speed;;
    if( s1XPos+s1Radius > 5.0 || s1XPos-s1Radius < -5.0 )
    {
        s1XPos -= s1XDelta;
        s1XDelta = -s1XDelta;
    }
    s1YPos += s1YDelta * speed;
    if( s1YPos+s1Radius > 15.0 || s1YPos-s1Radius < -15.0 )
    {
        s1YPos -= s1YDelta;
        s1YDelta = -s1YDelta;
    }
    s1ZPos += s1ZDelta * speed;
    if( s1ZPos+s1Radius > 5.0 || s1ZPos-s1Radius < -5.0 )
    {
        s1ZPos -= s1ZDelta;
    }
    
    // rotate sphere1
    s1XTheta += s1XThetaDelta * speed;
    s1YTheta += s1YThetaDelta * speed;
    s1ZTheta += s1ZThetaDelta * speed;
    
    // move the second sphere, bouncing off the edge if it hits it
    s2XPos += s2XDelta * speed;
    if( s2XPos+s1Radius > 5.0 || s2XPos-s1Radius < -5.0 )
    {
        s2XPos -= s2XDelta;
        s2XDelta = -s2XDelta;
    }
    s2YPos += s2YDelta * speed;
    if( s2YPos+s1Radius > 15.0 || s2YPos-s1Radius < -15.0 )
    {
        s2YPos -= s2YDelta;
        s2YDelta = -s2YDelta;
    }
    s2ZPos += s2ZDelta * speed;
    if( s2ZPos+s1Radius > 5.0 || s2ZPos-s1Radius < -5.0 )
    {
        s2ZPos -= s2ZDelta;
        s2ZDelta = -s2ZDelta;
    }
    
    // rotate sphere2
    s2XTheta += s2XThetaDelta * speed;
    s2YTheta += s2YThetaDelta * speed;
    s2ZTheta += s2ZThetaDelta * speed;
    
    // if the spheres intersect, have them bounce off each other
    float dist1 = sqrt( (s1XPos-s2XPos)*(s1XPos-s2XPos) +
                       (s1YPos-s2YPos)*(s1YPos-s2YPos) +
                       (s1ZPos-s2ZPos)*(s1ZPos-s2ZPos) );
    if( dist1 <= (s1Radius + s2Radius) )
    {
        // they intersect, so exchange velocities
        float temp;
        temp = s1XDelta;
        s1XDelta = s2XDelta;
        s2XDelta = temp;
        
        temp = s1YDelta;
        s1YDelta = s2YDelta;
        s2YDelta = temp;
        
        temp = s1ZDelta;
        s1ZDelta = s2ZDelta;
        s2ZDelta = temp;
    }
    
    float dist2 = sqrt( (s1XPos-pXPos)*(s1XPos-pXPos) +
                       (s1YPos-pYPos)*(s1YPos-pYPos) +
                       (s1ZPos-pZPos)*(s1ZPos-pZPos) );
    if( dist2 <= (s1Radius + pRadius) )
    {
        // they intersect, so game over
        gameOver();
    }
    float dist3 = sqrt( (s2XPos-pXPos)*(s2XPos-pXPos) +
                       (s2YPos-pYPos)*(s2YPos-pYPos) +
                       (s2ZPos-pZPos)*(s2ZPos-pZPos) );
    if( dist3 <= (s2Radius + pRadius) )
    {
        gameOver();
    }
    
    
    // the world needs redrawn
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case '4': // left
            theta += 5;
            glutPostRedisplay();
            break;
        case '6': //right
            theta -= 5;
            glutPostRedisplay();
            break;
        case '2': //down
            phi -= 5;
            // can't go < -90
            if( phi < -90 )
                
                phi = -90;
            glutPostRedisplay();
            break;
        case '8': //up
            phi += 5;
            // can't go > 90
            if( phi > 90 )
                phi = 90;
            glutPostRedisplay();
            break;
        case '3': //pgDn (back up)
            dist += 0.5;
            glutPostRedisplay();
            break;
        case '9': //pgUp (move forward)
            dist -= 0.5;
            glutPostRedisplay();
            break;
            
        case 27: /* esc */
        case 'Q':
        case 'q':
            exit(0);
            break;
            
        case 'I': // toggle start
        case 'i':
            startGame = !startGame;
            game = 1;
            // register callback if we just turned game on
            glutTimerFunc (20,timer,0);
            break;
            
        case '+':
            speed += 0.1;
            break;
        case '-':
            speed -= 0.1;
            if( speed < 0.1 )
                speed = 0.1;
            break;
            
        case 'V': //camera is placed in the usual position
        case 'v':
            whichView = 1;
            glutPostRedisplay();
            break;
        case 'P'://camera is placed on the player
        case 'p':
            whichView = 2;
            glutPostRedisplay();
        case 'W': // going toward
        case 'w':
            pZPos -= 0.3;
            if( pZPos > 5.0 )
                pZPos = 5.0;
            glutPostRedisplay();
            break;
            
        case 'S': //going back
        case 's':
            pZPos += 0.3;
            if( pZPos < -5.0 )
                pZPos = -5.0;
            glutPostRedisplay();
            break;

        case 'A':
        case 'a'://going left
            pXPos -= 0.3;
            if( pXPos < -5.0 )
                pXPos = -5.0;
            glutPostRedisplay();
            break;
            
        case 'D': //going right
        case 'd':
            pXPos += 0.3;
            if( pXPos > 5.0 )
                pXPos = 5.0;
            glutPostRedisplay();
            break;
    }
}


// draw a radius 1 wire sphere centered around the origin.  The longitude// lines (i.e., north and south poles) will meet on the y-axis.  A line
// through the north and south poles will also be drawn, as well as a small
// "flag" on the north pole line.
void drawSphere ()
{
    glPushMatrix ();
    glRotatef (90.0, 1.0, 0.0, 0.0);
    glutWireSphere (1.0, 20, 20);
    glPopMatrix ();
    glBegin( GL_POLYGON );
    
    glVertex3f( 0.0, 1.5, 0.0 );
    glVertex3f( 0.0, -1.5, 0.0 );
    glVertex3f( 0.0, 1.5, 0.0 );
    glVertex3f( 0.25, 1.5, 0.0 );
    glEnd();
}

void drawWin()
{
    glBegin( GL_LINE_LOOP );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -0.5, 2, -0.5 );
    glVertex3f( -0.5, -2, -0.5 );
    glVertex3f( -0.5, -2, 0.5 );
    glVertex3f( -0.5, 2, 0.5 );
    glVertex3f( 0.5, 2, 0.5 );
    glVertex3f( 0.5, 2, -0.5 );
    glVertex3f( 0.5, -2, -0.5 );
    glVertex3f( 0.5, -2, 0.5 );
    glEnd();
}


void DrawGrid(int HalfWidth, int HalfHeight)
{
    glBegin(GL_LINES);
    for(int i=-HalfWidth;i<=HalfWidth;i++)
    {
        glVertex3f((float)i,0,(float)-HalfHeight);
        glVertex3f((float)i,0,(float)HalfHeight);
    }
    for(int i=-HalfHeight;i<=HalfHeight;i++)
    {
        glVertex3f((float)-HalfWidth,0,(float)i);
        glVertex3f((float)HalfWidth,0,(float)i);
    }
    
    glEnd();
    
}

void display(void)
{
    
    // define material property parameters
    GLfloat matSpecular[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat matShininess =   100.0;
    
    
    
    // define default material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
    
    // clear frame buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Light 0 - Camera
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    
    // define view transformation
    switch( whichView )
    {
        case 1:
            setCamera();
            break;
        case 2:
            playerView();
            break;
    }
    
    
    glEnable(GL_LIGHTING);
    
    
    // draw player
    glPushMatrix(); // push world frame so we can get back here
    glTranslatef( pXPos, pYPos, pZPos );
    glColor3f( 1.0, 1.0, 1.0 );
    glPushMatrix();
    glScalef( s1Radius, s1Radius, s1Radius );
    drawSphere();
    glPopMatrix();
    
    // back to world frame
    glPopMatrix();
    
    if( startGame )
    {// draw sphere1
        glPushMatrix(); // push world frame so we can get back here
        glTranslatef( s1XPos, s1YPos, s1ZPos );
        glRotatef( s1XTheta, 1, 0, 0 );
        glRotatef( s1YTheta, 0, 1, 0 );
        glRotatef( s1ZTheta, 0, 0, 1 );
        glColor3f( 1.0, 0.0, 0.0 );
        glPushMatrix();
        glScalef( s1Radius, s1Radius, s1Radius );
        drawSphere();
        glPopMatrix();
        
        // back to world frame
        glPopMatrix();
        
        // draw sphere2
        glPushMatrix(); // push world frame so we can get back here
        glTranslatef( s2XPos, s2YPos, s2ZPos );
        glRotatef( s2XTheta, 1, 0, 0 );
        glRotatef( s2YTheta, 0, 1, 0 );
        glRotatef( s2ZTheta, 0, 0, 1 );
        glColor3f( 1.0, 1.0, 0.0 );
        glPushMatrix();
        glScalef( s2Radius, s2Radius, s2Radius );
        drawSphere();
        glPopMatrix();
        
        // back to world frame
        glPopMatrix();
    }
    
    
    //call it like this
    
    // Bottom
    glPushMatrix(); // push world frame so we can get back here
    glTranslatef( 0, -15, 0 );
    glColor3f( 0.5, 0.5, 0.5 );
    DrawGrid(5, 5);
    glPopMatrix();
    
    // Top
    glPushMatrix(); // push world frame so we can get back here
    glTranslatef( 0, 15, 0 );
    glColor3f( 0.5, 0.5, 0.5 );
    DrawGrid(5, 5);
    glPopMatrix();
    
    // Back
    glPushMatrix(); // push world frame so we can get back here
    glTranslatef( 0, 0, -5 );
    glRotatef(90, 1, 0, 0);
    glColor3f( 0.5, 0.5, 0.5 );
    DrawGrid(5, 15);
    glPopMatrix();
    
    // Left
    glPushMatrix(); // push world frame so we can get back here
    glRotatef(90, 0, 0, 1);
    glTranslatef( 0, -5, 0 );
    glColor3f( 0.5, 0.5, 0.5 );
    DrawGrid(15, 5);
    glPopMatrix();
    
    // Right
    glPushMatrix(); // push world frame so we can get back here
    glRotatef(90, 0, 0, 1);
    glTranslatef( 0, 5, 0 );
    glColor3f( 0.5, 0.5, 0.5 );
    DrawGrid(15, 5);
    glPopMatrix();
    
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // initialize glut, create window, etc.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,850);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Landing the Earth");
    
    // initialize program data structures
    init();
    
    // register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    // do everything!
    glutMainLoop();
    
    return 0;
}