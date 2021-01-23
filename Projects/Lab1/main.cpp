//============================================================
// STUDENT NAME: Jim Vincent Andes Engay
// STUDENT NO.: A0206031B
// NUS EMAIL ADDRESS: e0425954@u.nus.edu
// COMMENTS TO GRADER: 
// 
// ============================================================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS
/////////////////////////////////////////////////////////////////////////////

#define PI                  3.1415926535897932384626433832795

#define MAX_NUM_OF_DISCS    200     // Limit the number of discs.
#define MIN_RADIUS          10.0    // Minimum radius of disc.
#define MAX_RADIUS          50.0    // Maximum radius of disc.
#define NUM_OF_SIDES        18      // Number of polygon sides to approximate a disc.


#define MIN_X_SPEED         1.0     // Minimum speed of disc in X direction.
#define MAX_X_SPEED         20.0    // Maximum speed of disc in X direction.
#define MIN_Y_SPEED         1.0     // Minimum speed of disc in Y direction.
#define MAX_Y_SPEED         20.0    // Maximum speed of disc in Y direction.

#define DESIRED_FPS         30      // Approximate desired number of frames per second.

#define ANGLE_BETWEEN_VERTEX (2 * PI) / (NUM_OF_SIDES); // Angle between vertex.
#define REFRESH_TIME        1000/DESIRED_FPS    // Refresh rate.


/////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
/////////////////////////////////////////////////////////////////////////////

typedef struct discType 
{
    double pos[2];          // The X and Y coordinates of the center of the disc.
    double speed[2];        // The velocity of the disc in X and Y directions. Can be negative.
    double radius;          // Radius of the disc.
    unsigned char color[3]; // R, G, B colors of the disc.
} discType;

int numDiscs = 0;                   // Number of discs that have been added.

discType disc[ MAX_NUM_OF_DISCS ];  // Array for storing discs.

bool drawWireframe = false;         // Draw polygons in wireframe if true, otherwise
                                    // otherwise polygons are filled.

int winWidth = 800;                 // Window width in pixels.
int winHeight = 600;                // Window height in pixels.



/////////////////////////////////////////////////////////////////////////////
// Draw the disc in its color using GL_TRIANGLE_FAN.
/////////////////////////////////////////////////////////////////////////////

void DrawDisc( const discType *d )
{
    static bool firstTime = true;
    static double unitDiscVertex[ NUM_OF_SIDES + 1 ][2];

    if ( firstTime )
    {
        // Pre-compute and store the vertices' positions of a unit-radius disc.
        for (int i = 0; i < NUM_OF_SIDES + 1; ++i) {
            double currentAngle = (double) i * ANGLE_BETWEEN_VERTEX;
            unitDiscVertex[i][0] = cos(currentAngle);
            unitDiscVertex[i][1] = sin(currentAngle);
        }
        firstTime = false;

    }
   
    // Setting up the the disc information
    double xCentre = d -> pos[0];
    double yCentre = d -> pos[1];
    double radius = d -> radius;
    glColor3ubv(d -> color);
    
    // Plotting the Circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xCentre, yCentre);
        // Plotting all the coordinates.
        for (int i = 0; i < NUM_OF_SIDES + 1; ++i) {
            glVertex2f(xCentre + (radius * unitDiscVertex[i][0]),
                       yCentre + (radius * unitDiscVertex[i][1]));
        }
    glEnd();
}



/////////////////////////////////////////////////////////////////////////////
// The display callback function.
/////////////////////////////////////////////////////////////////////////////

void MyDisplay( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

    if ( drawWireframe ) 
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    for ( int i = 0; i < numDiscs; i++ ) DrawDisc( &disc[i] );

    // Double Buffering
    glutSwapBuffers();
}

double randomDouble(double min, double max)
{
    // Random fraction between 0 to 1
    double fraction = (double) rand() / RAND_MAX;
    double randomValue = fraction * (max - min);
    return randomValue + min;
}

double randomVelocity(double min, double max) {
    // Velocity can be negative.
    double randomValue = randomDouble(min, max);
    if (rand() % 2 == 0) {
        return -randomValue;
    } else {
        return randomValue;
    }
}

int randomColour()
{
    return rand() % 256;
}




/////////////////////////////////////////////////////////////////////////////
// The mouse callback function.
// If mouse left button is pressed, a new disc is created with its center 
// at the mouse cursor position. The new disc is assigned the followings:
// (1) a random radius between MIN_RADIUS and MAX_RADIUS,
// (2) a random speed in X direction in the range 
//     from -MAX_X_SPEED to -MIN_X_SPEED, and from MIN_X_SPEED to MAX_X_SPEED.
// (3) a random speed in Y direction in the range 
//     from -MAX_Y_SPEED to -MIN_Y_SPEED, and from MIN_Y_SPEED to MAX_Y_SPEED.
// (4) R, G, B color, each ranges from 0 to 255.
/////////////////////////////////////////////////////////////////////////////

void MyMouse( int btn, int state, int x, int y )
{
    if ( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        if ( numDiscs >= MAX_NUM_OF_DISCS )
            printf( "Already reached maximum number of discs.\n" );
        else
        {
            // The velocity of the disc in X and Y directions. Can be negative.
            double speedX = randomVelocity(MIN_X_SPEED, MAX_X_SPEED);
            double speedY = randomVelocity(MIN_Y_SPEED, MAX_Y_SPEED);
            
            // Radius of the disc.
            double radius = randomDouble(MIN_RADIUS, MAX_RADIUS);
            
            // unsigned char color[3]; // R, G, B colors of the disc.
            int R = rand() % 256;
            int G = rand() % 256;
            int B = rand() % 256;
            
            // Adjust the y - coordinate.
            y = winHeight - 1 - y;
            
            // Create the current disc.
            discType currentDisc = { {x, y},
                {speedX, speedY},
                radius,
                {R, G, B}
            };
            
            // Update discs.
            disc[numDiscs] = currentDisc;
            numDiscs++;
            glutPostRedisplay();
        }
    }
}





/////////////////////////////////////////////////////////////////////////////
// The reshape callback function.
// It also sets up the viewing.
/////////////////////////////////////////////////////////////////////////////

void MyReshape( int w, int h )
{
    winWidth = w;
    winHeight = h;

    glViewport( 0, 0, winWidth, winHeight );

    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();
    gluOrtho2D(0, winWidth, 0, winHeight);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}



/////////////////////////////////////////////////////////////////////////////
// The keyboard callback function.
/////////////////////////////////////////////////////////////////////////////

void MyKeyboard( unsigned char key, int x, int y )
{
    switch ( key )
    {
        // Quit program.
        case 'q':
        case 'Q': exit(0);
                  break;

        // Toggle wireframe or filled polygons.
        case 'w':
        case 'W': drawWireframe = !drawWireframe;
                  glutPostRedisplay();
                  break;

        // Reset and erase all discs.
        case 'r':
        case 'R': numDiscs = 0;
                  glutPostRedisplay();
                  break;
    }
}



/////////////////////////////////////////////////////////////////////////////
// Updates the positions of all the discs.
//
// Increments the position of each disc by its speed in each of the
// X and Y directions. Note that the speeds can be negative.
// At its new position, if the disc is entirely or partially outside the
// left window boundary, then shift it right so that it is inside the
// window and just touches the left window boundary. Its speed in the X 
// direction must now be reversed (negated). Similar approach is 
// applied for the cases of the right, top, and bottom window boundaries.
/////////////////////////////////////////////////////////////////////////////

void UpdateAllDiscPos( void )
{
    for ( int i = 0; i < numDiscs; i++ )
    {
        // discType *currentDiscPointer = &disc[i];
        // *currentDiscPointer.pos[0] += currentDiscPointer.speed[0];
        // *currentDiscPointer.pos[1] += currentDiscPointer.speed[1];
        discType& currentDiscPointer = disc[i];
\
        // Increments the position of each disc by its speed in each of the
        // X and Y directions. Note that the speeds can be negative.
        
        currentDiscPointer.pos[0] += currentDiscPointer.speed[0];
        currentDiscPointer.pos[1] += currentDiscPointer.speed[1];
        
        double xCentre = currentDiscPointer.pos[0];
        double yCentre = currentDiscPointer.pos[1];
        double radius = currentDiscPointer.radius;
        

        // Adjust position and reverse the velocity
        // when the disc is within/outside the boundary
        if (xCentre - radius <= 0) {
            // Left window boundary.
            currentDiscPointer.pos[0] = radius;
            currentDiscPointer.speed[0] = -currentDiscPointer.speed[0];
        } else if (xCentre + radius >= winWidth) {
            // Right window boundary.
            currentDiscPointer.pos[0] = winWidth - radius;
            currentDiscPointer.speed[0] = -currentDiscPointer.speed[0];
        }
        
        if (yCentre - radius <= 0) {
            // Bottom window boundary.
            currentDiscPointer.pos[1] = radius;
            currentDiscPointer.speed[1] = -currentDiscPointer.speed[1];
        } else if (yCentre + radius >= winHeight) {
            // Top window boundary.
            currentDiscPointer.pos[1] = winHeight - radius;
            currentDiscPointer.speed[1] = -currentDiscPointer.speed[1];
        }
    }
    glutPostRedisplay();
}



/////////////////////////////////////////////////////////////////////////////
// The timer callback function.
/////////////////////////////////////////////////////////////////////////////

void MyTimer( int v )
{
    UpdateAllDiscPos();
    glutTimerFunc(REFRESH_TIME, MyTimer, v);
}



/////////////////////////////////////////////////////////////////////////////
// The init function.
// It initializes some OpenGL states.
/////////////////////////////////////////////////////////////////////////////

void MyInit( void )
{
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // Black background color.
    glShadeModel( GL_FLAT );
}



/////////////////////////////////////////////////////////////////////////////
// The main function.
/////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize( winWidth, winHeight );
    glutCreateWindow( "Lab1" );

    MyInit();

    // Register the callback functions.
    glutDisplayFunc( MyDisplay ); 
    glutReshapeFunc( MyReshape );
    glutMouseFunc( MyMouse );
    glutKeyboardFunc( MyKeyboard );
    glutTimerFunc(0, MyTimer, 0);

    // Display user instructions in console window.
    printf( "Click LEFT MOUSE BUTTON in window to add new disc.\n" );
    printf( "Press 'w' to toggle wireframe.\n" );
    printf( "Press 'r' to erase all discs.\n" );
    printf( "Press 'q' to quit.\n\n" );

    // Enter GLUT event loop.
    glutMainLoop();
    return 0;
}
