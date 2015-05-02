#include <string>
#include <iostream>
using namespace std;

#include "MenuState.h"

void MenuState::onEnter(){
	cout << "Hello Menu" << endl;
}

void MenuState::onExit(){
	cout << "Goodbye menu" << endl;
}

MenuState::MenuState(){
	name = "Menu";
}