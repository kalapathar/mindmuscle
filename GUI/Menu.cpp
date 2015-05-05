#include<iostream>
#include<fstream>
using namespace std;
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<math.h>
#include<stdlib.h>
#include"texture.h"

bool mouseIsDragging = false;

int WIDTH = 1024;
int HEIGHT = 512;
char programName[] = "Menu";

int menuT, calibrateT, measureT, aboutT, resultsT; // Texture IDs

// Button rects
struct Button {
    int w, h, x, y;
    bool active; // hovered
};
Button calibrateB = {
    170,
    56,
    147,
    54,
    false
};
Button measureB = {
    162,
    56,
    763,
    148,
    false
};
Button aboutB = {
    118,
    56,
    157,
    249,
    false
};
Button resultsB = {
    134,
    56,
    164,
    361,
    false
};

void drawWindow()
{
    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // draw stuff
    if (calibrateB.active) {
        drawTexture(calibrateT, 0, 0, 1024, 512); // texID,   x,y,    width, height
    } else if (measureB.active) {
        drawTexture(measureT, 0, 0, 1024, 512); // texID,   x,y,    width, height
    } else if (aboutB.active) {
        drawTexture(aboutT, 0, 0, 1024, 512); // texID,   x,y,    width, height
    } else if (resultsB.active) {
        drawTexture(resultsT, 0, 0, 1024, 512); // texID,   x,y,    width, height
    } else {
        drawTexture(menuT, 0, 0, 1024, 512); // texID,   x,y,    width, height
    }
    
    // tell the graphics card that we're done-- go ahead and draw!
    //   (technically, we are switching between two color buffers...)
    glutSwapBuffers();
}

// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
    int win = glutGetWindow();
    switch(c) {
        case 'q':
        case 'Q':
        case 27:
            // get rid of the window (as part of shutting down)
            glutDestroyWindow(win);
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    WIDTH = w;  HEIGHT = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);
}

// Updates the hover visibilites for textures depending on the position of the mouse
void updateHoverStates(int x, int y) {
    if (x >= calibrateB.x && x <= calibrateB.x+calibrateB.w &&
        y >= calibrateB.y && y <= calibrateB.y+calibrateB.h) {
        calibrateB.active = true;
    } else {
        calibrateB.active = false;
    }
    
    if (x >= measureB.x && x <= measureB.x+measureB.w &&
        y >= measureB.y && y <= measureB.y+measureB.h) {
        measureB.active = true;
    } else {
        measureB.active = false;
    }
    
    if (x >= aboutB.x && x <= aboutB.x+aboutB.w &&
        y >= aboutB.y && y <= aboutB.y+aboutB.h) {
        aboutB.active = true;
    } else {
        aboutB.active = false;
    }
    
    if (x >= resultsB.x && x <= resultsB.x+resultsB.w &&
        y >= resultsB.y && y <= resultsB.y+resultsB.h) {
        resultsB.active = true;
    } else {
        resultsB.active = false;
    }
}

// the mouse function is called when a mouse button is pressed down or released
void mouse(int button, int state, int x, int y)
{
    if ( GLUT_LEFT_BUTTON == button ) {
        if ( GLUT_DOWN == state ) {
            mouseIsDragging = true;
            // the user just pressed down on the mouse-- do something
        } else {
            // the user just let go the mouse-- do something
            mouseIsDragging = false;
        }
    } else if ( GLUT_RIGHT_BUTTON == button ) {
    }
    
    glutPostRedisplay();
}

// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x,int y)
{
    updateHoverStates(x, y);
    
    // the mouse button is pressed, and the mouse is moving....
    glutPostRedisplay();
}

// the init function sets up the graphics card to draw properly
void init(void)
{
    // clear the window to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // set up the coordinate system:  number of pixels along x and y
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);
    
    // allow blending (for transparent textures)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    // welcome message
    cout << "Welcome to " << programName << "." << endl;
}


// init_gl_window is the function that starts the ball rolling, in
//  terms of getting everything set up and passing control over to the
//  glut library for event handling.  It needs to tell the glut library
//  about all the essential functions:  what function to call if the
//  window changes shape, what to do to redraw, handle the keyboard,
//  etc.
void init_gl_window()
{
    char *argv[] = { programName };
    int argc = sizeof(argv) / sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(100,100);
    glutCreateWindow(programName);
    init();
    
    menuT = loadTexture("Menu.pam");
    calibrateT = loadTexture("Menu-calibrate.pam");
    measureT = loadTexture("Menu-measure.pam");
    aboutT = loadTexture("Menu-about.pam");
    resultsT = loadTexture("Menu-results.pam");
    
    glutDisplayFunc(drawWindow);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
    glutMainLoop();
}

int main()
{
    init_gl_window();
}
