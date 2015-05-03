#include <string>
#include <iostream>
using namespace std;

#include "ReadingState.h"

void ReadingState::onEnter(){
	
}

void ReadingState::onExit(){
	
}

ReadingState::ReadingState(){
	name = "Reading";
}


void ReadingState::update(){

}

void ReadingState::render(){

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
