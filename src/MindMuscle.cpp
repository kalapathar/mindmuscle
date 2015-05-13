
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

#include "Box2D/Box2D.h"
#include "MindInterface.h"

#include "texture.h"
#include "Globals.h"


//Declare globals
int GAME_WIDTH = 1024;
int GAME_HEIGHT = 720;
bool MIND_CONNECTED = true;//Assume true
string FOLDER;
b2World * world;
MindInterface * mind;

///Include all of our states
#include "StateMachine.h"

#include "States/SplashState.h"
#include "States/MenuState.h"
#include "States/GameState.h"
#include "States/ResultsState.h"
#include "States/AboutState.h"
#include "States/ReadingState.h"

#include <math.h>
#include <cstring>

StateMachine fsm;



//Initializing variables
char programName[] = "Mind Muscle";
int mindPower = 0;


//Update loop variables

double lastLoopTime = 0.0;
double box2dLoopTime = 0.0;
double fps = 1.0/60.0;

float32 timeStep = 1.0f / 60.0f;
int32 velocityIterations = 6;
int32 positionIterations = 2;

string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
      if(fgets(buffer, 128, pipe) != NULL)
        result += buffer;
    }
    pclose(pipe);
    return result;
}

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
  
  //For some reason I need to update box2d at a different rate otherwise things are super slow?
  if ((now - box2dLoopTime) / 1000.0 > timeStep * fps){
    box2dLoopTime = now;
    world->Step(timeStep, velocityIterations, positionIterations);
  }

	//Run the game at 60 fps
	if ((now - lastLoopTime) / 1000.0 > fps){
		lastLoopTime = now;
    
    if(fsm.activeState) {
      fsm.activeState->update();
      
      MakeShiftMessageSystem();

    }

    //Render everything
		render();

    if(MIND_CONNECTED)  mind->update();
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

void onClose(){
  cout << "NO MIND" << endl;
  if(MIND_CONNECTED) delete mind;
}

void init(){
  //Initialize our state machine by registering all of our states
  MenuState * menu = new MenuState;
  SplashState * splash = new SplashState;
  GameState * game = new GameState;
  ReadingState * reading = new ReadingState;
  AboutState * about = new AboutState;
  ResultsState * results = new ResultsState;

  fsm.registerState(menu);
  fsm.registerState(splash);
  fsm.registerState(game);
  fsm.registerState(reading);
  fsm.registerState(about);
  fsm.registerState(results);

  //Start menu state
  fsm.transition("Splash");
  //fsm.transition("Menu");

  //Initialize box2d world!
  b2Vec2 gravity(0.0f,10.0f);
  world = new b2World(gravity,true);

  //Check if the Neurosky usb is connected
  string output = exec("lsusb");
  size_t found = output.find("QinHeng Electronics HL-340 USB-Serial adapter");
  if (found == string::npos) MIND_CONNECTED = false;//dongle not connected!

  if(MIND_CONNECTED) mind = new MindInterface;


}

void init_gl_window()
{
  char *argv[] = {programName};
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(GAME_WIDTH,GAME_HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  
  // clear the window to black
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., GAME_WIDTH-1, GAME_HEIGHT-1, 0., -1.0, 1.0);

  // allow blending (for transparent textures)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  init();

  //glutFullScreen();

  atexit(onClose);

  glutDisplayFunc(render);
  glutIdleFunc(update);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);
  glutMainLoop();

  



}


int main(int argc, char *argv[]){
  FOLDER = argv[0];

	//Initialize the window
	init_gl_window();



	return 0;
}