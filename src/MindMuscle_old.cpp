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
#include "texture.h"

///Include all of our states
#include "StateMachine.h"
#include "MenuState.h"
#include "GameState.h"

#include <math.h>

StateMachine fsm;

//Initializing variables
char programName[] = "Mind Muscle";
int WIDTH = 1024; 
int HEIGHT = 720;

//Update loop variables

double lastLoopTime = 0.0;
double fps = 1.0/60.0;

int logo = 0;
double counter = 0;

void render(){
	// clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  
  //Draw everything
  float alpha = sin(counter);
  if(alpha < 0) alpha = alpha*-1;
  drawTexture(logo,  WIDTH/2-250,HEIGHT/2-250, 500,500,alpha);
  //cout << logo << endl;

  glutSwapBuffers();
}

void update(){
	double now = glutGet(GLUT_ELAPSED_TIME);
	//Run the game at 60 fps
	if ((now - lastLoopTime) / 1000.0 > fps){
		lastLoopTime = now;
		counter += 0.01;
		//Update your stuff here!
		render();
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
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  // allow blending (for transparent textures)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  logo = loadTexture("Logo.pam");

  //glutFullScreen();

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