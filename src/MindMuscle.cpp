///Standard libraries
#include <iostream>
#include <string>
using namespace std;
//Include openGL stuff
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
///Include all of our states
#include "StateMachine.h"
#include "MenuState.h"
#include "GameState.h"

StateMachine fsm;

//Initializing variables
char programName[] = "Mind Muscle";
int WIDTH = 720; 
int HEIGHT = 540;

//Update loop variables

double lastLoopTime = 0.0;
double fps = 1.0/60.0;


void render(){
	// clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  
  //Draw everything

  glutSwapBuffers();
}

void update(){
	double now = glutGet(GLUT_ELAPSED_TIME);
	//Run the game at 60 fps
	if ((now - lastLoopTime) / 1000.0 > fps){
		lastLoopTime = now;
		
		//Update your stuff here!
		
	} 
}



void init_gl_window()
{
  char *argv[] = {programName};
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  glutFullScreen();

  glutDisplayFunc(render);
  glutIdleFunc(update);
  glutMainLoop();


}


int main(){

	//Initialize the window
	init_gl_window();


	MenuState menu;
	GameState game;
	fsm.registerState(&menu);
	fsm.registerState(&game);


	fsm.transition("Menu");
	fsm.transition("Game");
	fsm.transition("Menu");

	return 0;
}