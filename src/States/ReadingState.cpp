#include <string>
#include <iostream>
using namespace std;

#include "ReadingState.h"

#include "../texture.h"

int reading;

void ReadingState::onEnter(){
	reading = loadTexture("Images/reading.pam");
}

void ReadingState::onExit(){
	
}

ReadingState::ReadingState(){
	name = "Reading";
}


void ReadingState::update(){

}

void ReadingState::render(){
	double width = 485;
	double height = 147;
	drawTexture(reading,  GAME_WIDTH/2-width/2,GAME_HEIGHT/2-height/2, width,height);
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
