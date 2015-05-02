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