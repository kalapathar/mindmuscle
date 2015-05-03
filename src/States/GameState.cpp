#include <string>
#include <iostream>
using namespace std;

#include "GameState.h"

void GameState::onEnter(){
	cout << "Hello GAME" << endl;
}

void GameState::onExit(){
	cout << "Goodbye GAME" << endl;
}

GameState::GameState(){
	name = "Game";
}

//Empty states
void GameState::update(){

}

void GameState::render(){

}

void GameState::keyboard(unsigned char c, int x, int y){

}

void GameState::mouse(int button, int state, int x, int y){

}

void GameState::mouse_motion(int x,int y){

}
