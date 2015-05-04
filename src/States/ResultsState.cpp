#include <string>
#include <iostream>
using namespace std;

#include "ResultsState.h"
#include "../texture.h"

int results;

void ResultsState::onEnter(){
	results = loadTexture("Images/results.pam");
}

void ResultsState::onExit(){
	
}

ResultsState::ResultsState(){
	name = "Results";
}


void ResultsState::update(){

}

void ResultsState::render(){
	double width = 427;
	double height = 147;
	drawTexture(results,  GAME_WIDTH/2-width/2,GAME_HEIGHT/2-height/2, width,height);
}

void ResultsState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}
}

void ResultsState::mouse(int button, int state, int x, int y){

}

void ResultsState::mouse_motion(int x,int y){

}
