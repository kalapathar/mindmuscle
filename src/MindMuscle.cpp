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

#include "States/SplashState.h"
#include "States/MenuState.h"
#include "States/GameState.h"

#include <math.h>
#include <cstring>

StateMachine fsm;

//Initializing variables
char programName[] = "Mind Muscle";
int WIDTH = 1024; 
int HEIGHT = 720;

//Update loop variables

double lastLoopTime = 0.0;
double fps = 1.0/60.0;

void MakeShiftMessageSystem(){
  if(fsm.activeState->sent){
      //Check if this state is trying to send us a message
      //Makeshift messaging system for now
      int i =0;
      const char * transmitMsg = "trans_";
      while(fsm.activeState->msg[i] == transmitMsg[i]){
        i++;
        if(i == strlen(transmitMsg)){
          //It's trying to transition to a new state! Get the name
          char * stateName = new char[fsm.activeState->msg.length() - strlen(transmitMsg)+1];
          int index = 0;
          while(fsm.activeState->msg[i]!='\0'){
            stateName[index++] = fsm.activeState->msg[i++];
          }
          stateName[index] = '\0';
          //Finally, transition!
          fsm.transition(stateName);
        }
      }
      fsm.activeState->sent = 0;
    }
}

void render(){
	// clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  
  //Run the active state render function
  if(fsm.activeState)fsm.activeState->render();

  glutSwapBuffers();
}

void update(){
	double now = glutGet(GLUT_ELAPSED_TIME);
	//Run the game at 60 fps
	if ((now - lastLoopTime) / 1000.0 > fps){
		lastLoopTime = now;

		//Update your stuff here!
    if(fsm.activeState) {
      fsm.activeState->update();
      
      MakeShiftMessageSystem();

    }

    //Render everything
		render();
	} 
}

void keyboard( unsigned char c, int x, int y )
{
  if(fsm.activeState) fsm.activeState->keyboard(c,x,y);
}

void mouse(int button, int state, int x, int y)
{
  if(fsm.activeState) fsm.activeState->mouse(button,state,x,y);
}

void mouse_motion(int x,int y)
{

  if(fsm.activeState) fsm.activeState->mouse_motion(x,y);
}

void init(){
  //Initialize our state machine by registering all of our states
  MenuState * menu = new MenuState;
  SplashState * splash = new SplashState;
  GameState * game = new GameState;
  fsm.registerState(menu);
  fsm.registerState(splash);
  fsm.registerState(game);

  //Start menu state
  fsm.transition("Splash");
  //fsm.transition("Menu");

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

  init();

  //glutFullScreen();

  glutDisplayFunc(render);
  glutIdleFunc(update);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);
  glutMainLoop();


}


int main(){

	//Initialize the window
	init_gl_window();



	return 0;
}