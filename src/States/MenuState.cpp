#include <string>
#include <iostream>
using namespace std;

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "MenuState.h"
#include "../texture.h"

bool mouseIsDragging = false;

int menuT, calibrateT, measureT, aboutT, resultsT; // Texture IDs

int OffsetX = -20;
int OffsetY = 110;


// Button rects
struct Button {
    int w, h, x, y;
    bool active; // hovered
};
Button calibrateB = {
    170,
    56,
    147 + OffsetX,
    54 + OffsetY,
    false
};
Button measureB = {
    162,
    56,
    763 + OffsetX,
    148 + OffsetY,
    false
};
Button aboutB = {
    118,
    56,
    157 + OffsetX,
    249 + OffsetY,
    false
};
Button resultsB = {
    134,
    56,
    164 + OffsetX,
    361 + OffsetY,
    false
};

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



void MenuState::onEnter(){
	menuT = loadTexture("Images/Menu.pam");
    calibrateT = loadTexture("Images/Menu-calibrate.pam");
    measureT = loadTexture("Images/Menu-measure.pam");
    aboutT = loadTexture("Images/Menu-about.pam");
    resultsT = loadTexture("Images/Menu-results.pam");
}

void MenuState::onExit(){
	

}

void MenuState::update(){


}

void MenuState::render(){
	if (calibrateB.active) {
        drawTexture(calibrateT, OffsetX,OffsetY, 1024, 512,1.0,0.0,1.0,1.0,1.0); // texID,   x,y,    width, height
    } else if (measureB.active) {
        drawTexture(measureT, OffsetX,OffsetY, 1024, 512,1.0,0.0,1.0,1.0,1.0);  // texID,   x,y,    width, height
    } else if (aboutB.active) {
        drawTexture(aboutT, OffsetX,OffsetY, 1024, 512,1.0,0.0,1.0,1.0,1.0);  // texID,   x,y,    width, height
    } else if (resultsB.active) {
        drawTexture(resultsT, OffsetX,OffsetY, 1024, 512,1.0,0.0,1.0,1.0,1.0);  // texID,   x,y,    width, height
    } else {
        drawTexture(menuT, OffsetX,OffsetY, 1024, 512,1.0,0.0,1.0,1.0,1.0);  // texID,   x,y,    width, height
    }
}

void MenuState::keyboard(unsigned char c, int x, int y){
   

}

void MenuState::mouse(int button, int state, int x, int y){
	if ( GLUT_LEFT_BUTTON == button ) {
        if ( GLUT_DOWN == state ) {
            mouseIsDragging = true;

            // the user just pressed down on the mouse-- do something
        } else {
            //Handle button pressed
            if(calibrateB.active){
                //Transition to game state 
                msg = "trans_Game";
                sent = 1;
            }

            if(measureB.active){
                //Transition to reading state 
                msg = "trans_Reading";
                sent = 1;
            }

            if(aboutB.active){
                //Transition to about state 
                msg = "trans_About";
                sent = 1;
            }

            if(resultsB.active){
                //Transition to game state 
                msg = "trans_Results";
                sent = 1;
            }


            mouseIsDragging = false;
        }
    } else if ( GLUT_RIGHT_BUTTON == button ) {
    }
}

void MenuState::mouse_motion(int x,int y){
	updateHoverStates(x, y);
}


MenuState::MenuState(){
	name = "Menu";
}