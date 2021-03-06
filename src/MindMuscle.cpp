
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
bool CAM_CONNECTED = true;//Assume true
string FOLDER;
b2World * world;
MindInterface * mind;
float Xoffset = 0;
float Yoffset = 0;

///Include all of our states
#include "StateMachine.h"

#include "States/SplashState.h"
#include "States/MenuState.h"
#include "States/CalibrateState.h"
#include "States/ResultsState.h"
#include "States/AboutState.h"
#include "States/ReadingState.h"
#include "States/LevelOne.h"

#include <math.h>
#include <cstring>
#include <time.h>

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
        
        mind->update();
        
    }
}

void keyboard( unsigned char c, int x, int y )
{
    
    mind->keyboard(c,x,y);
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
    //Close current state
    fsm.destroy();
    delete mind;
    
}

void init(){
    //Initialize our state machine by registering all of our states
    MenuState * menu = new MenuState;
    SplashState * splash = new SplashState;
    CalibrateState * game = new CalibrateState;
    ReadingState * reading = new ReadingState;
    AboutState * about = new AboutState;
    ResultsState * results = new ResultsState;
    LevelOne * levelone = new LevelOne;
    
    fsm.registerState(menu);
    fsm.registerState(splash);
    fsm.registerState(game);
    fsm.registerState(reading);
    fsm.registerState(about);
    fsm.registerState(results);
    fsm.registerState(levelone);
    
    //Start menu state
    fsm.transition("Splash");
    //fsm.transition("Menu");
    
    //Initialize box2d world!
    b2Vec2 gravity(0.0f,10.0f);
    world = new b2World(gravity,true);
    
    //Check if the Neurosky usb is connected
    string output = exec("lsusb");
    size_t found_mind = output.find("QinHeng Electronics HL-340 USB-Serial adapter");
    CAM_CONNECTED = (output.find("Webcam") != string::npos ) || (output.find("webcam") != string::npos ) ;//Webcam not found!
    if (found_mind == string::npos) MIND_CONNECTED = false;//dongle not connected!
    
    if(!CAM_CONNECTED){
        cout << "\t=== Warning ===" << endl;
        cout << "\tNo webcam detected! \n\tReverting to mouse position instead of gaze position" << endl;
        cout << "\t==============" << endl;
    }
    
    if(!MIND_CONNECTED){
        cout << "\t=== Warning ===" << endl;
        cout << "\tThe Neurosky headset was not detected! \n\tReverting to keypresses instead of EEG data" << endl;
        cout << "\t==============" << endl;
    }
    
    /* initialize random seed: */
    srand (time(NULL));
    
    
    mind = new MindInterface;
    
    
}

void resize(int width, int height) {
    // we ignore the params and do:
    //glutGet(GLUT_WINDOW_WIDTH)
    if (width != GAME_WIDTH || height != GAME_HEIGHT) glutReshapeWindow(GAME_WIDTH, GAME_HEIGHT);
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
    glutReshapeFunc(resize);
    
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