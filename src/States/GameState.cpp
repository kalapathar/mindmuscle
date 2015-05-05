#include <string>
#include <iostream>
using namespace std;

#include "GameState.h"
#include "../GameObject.h"

GameObject * testobj;
GameObject * box;
GameObject * box2;
GameObject * ground;
float gameCounter = 0;

void GameState::onEnter(){
	testobj = new GameObject("boxCrate",false);
	box = new GameObject("boxCrate_double",true,100,100,false,GAME_WIDTH/2+50,-200);
	box2 = new GameObject("boxCrate",true,100,100,false,GAME_WIDTH/2,0);
	ground = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,500);

}

void GameState::onExit(){
	delete testobj;
	delete box;
	delete box2;
	delete ground;
}

GameState::GameState(){
	name = "Game";
}


void GameState::update(){
	gameCounter +=0.05;;
	testobj->x = cos(gameCounter) * 200 + GAME_WIDTH/2.0;
	testobj->y = GAME_HEIGHT - 100;
	testobj->angle +=0.05;

	//cout << box->y << endl;
}

void GameState::render(){
	testobj->draw();
	box->draw();
	box2->draw();
	ground->draw();
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
