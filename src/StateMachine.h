#ifndef _STATEMACHINE_
#define _STATEMACHINE_

#include "State.h"
#include <vector>

/* 
This handles the creation, destruction and transitions of states
*/

class StateMachine {
public:
	//State variables
	State * activeState = 0;
	std::vector<State *> stateArray;
	int numStates=0;

	//My functions
	void registerState(State * st);//Creates a new state and stores it in stateArray
	void transition(string stateName);//Exits current state and calls new one
	void destroy();//Exits current state

};

#endif // _STATEMACHINE_