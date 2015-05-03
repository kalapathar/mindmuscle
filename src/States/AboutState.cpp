#include <string>
#include <iostream>
using namespace std;

#include "AboutState.h"

#include "../texture.h"

int about;

void AboutState::onEnter(){
	about = loadTexture("Images/about.pam");
}

void AboutState::onExit(){
	
}

AboutState::AboutState(){
	name = "About";
}


void AboutState::update(){

}

void AboutState::render(){
	double width = 577;
	double height = 267;
	drawTexture(about,  1024/2-width/2,720/2-height/2, width,height);
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
