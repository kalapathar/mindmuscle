#include <string>
#include <iostream>
using namespace std;

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "MenuState.h"
#include "texture.h"

bool mouseIsDragging = false;

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
}

void MenuState::keyboard(unsigned char c, int x, int y){

}

void MenuState::mouse(int button, int state, int x, int y){
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
}

void MenuState::mouse_motion(int x,int y){
	updateHoverStates(x, y);
}


MenuState::MenuState(){
	name = "Menu";
}