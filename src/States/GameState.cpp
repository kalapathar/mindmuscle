#include <string>
#include <iostream>
using namespace std;

#include "GameState.h"
#include "../GameObject.h"

GameObject * testobj;
float gameCounter = 0;

void GameState::onEnter(){
	testobj = new GameObject("boxCrate",false);
}

void GameState::onExit(){
	delete testobj;
}

GameState::GameState(){
	name = "Game";
}


void GameState::update(){
	gameCounter +=0.05;;
	testobj->x = cos(gameCounter) * 200 + 1024/2.0;
	testobj->y = 720/2.0;
	testobj->angle +=0.05;
}

void GameState::render(){
	testobj->draw();
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
