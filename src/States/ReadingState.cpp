#include <string>
#include <iostream>
using namespace std;

#include "ReadingState.h"
#include "../EyeInterface.h"

#include "../texture.h"

int reading;
EyeInterface * eye;

void ReadingState::onEnter(){
	reading = loadTexture("Images/reading.pam");
	eye = new EyeInterface;
}

void ReadingState::onExit(){
	delete eye;
}

ReadingState::ReadingState(){
	name = "Reading";
}


void ReadingState::update(){
	eye->update();
		// cout << gaze_x <<" "<< gaze_y <<endl;


}

void ReadingState::render(){
	double width = 485;
	double height = 147;
	drawTexture(reading,  GAME_WIDTH/2-width/2,GAME_HEIGHT/2-height/2, width,height,1.0,0.0,1.0,1.0,1.0); 
}

void ReadingState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}
}

void ReadingState::mouse(int button, int state, int x, int y){

}

void ReadingState::mouse_motion(int x,int y){

}
