#include <string>
#include <iostream>
using namespace std;

#include "ResultsState.h"

void ResultsState::onEnter(){
	
}

void ResultsState::onExit(){
	
}

ResultsState::ResultsState(){
	name = "Results";
}


void ResultsState::update(){

}

void ResultsState::render(){

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
