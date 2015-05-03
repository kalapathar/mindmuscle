#include <string>
#include <iostream>
using namespace std;

#include "GameState.h"

void GameState::onEnter(){
	
}

void GameState::onExit(){
	
}

GameState::GameState(){
	name = "Game";
}


void GameState::update(){

}

void GameState::render(){

}

void GameState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}
}

void GameState::mouse(int button, int state, int x, int y){

}

void GameState::mouse_motion(int x,int y){

}
