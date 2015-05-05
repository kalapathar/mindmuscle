#include <string>
#include <iostream>
using namespace std;

#include "StateMachine.h"

void StateMachine::registerState(State * st){
	//Append the state to the array
	stateArray.push_back(st);
	numStates++;
}

void StateMachine::transition(string stateName){
	if(activeState != 0){
		activeState->onExit();
	}
	//Find state with stateName
	for(int i=0;i< stateArray.size();i++){
		if(stateArray[i]->name == stateName){
			activeState = stateArray[i];
		}
	}

	//Activate it
	activeState->onEnter();
}

void StateMachine::destroy(){
	//Loop through and destroy current state
}