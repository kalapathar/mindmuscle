#include <string>
#include <iostream>
using namespace std;

#include "AboutState.h"

void AboutState::onEnter(){
	
}

void AboutState::onExit(){
	
}

AboutState::AboutState(){
	name = "About";
}


void AboutState::update(){

}

void AboutState::render(){

}

void AboutState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}
}

void AboutState::mouse(int button, int state, int x, int y){

}

void AboutState::mouse_motion(int x,int y){

}
