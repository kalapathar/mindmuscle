#ifndef _GameState_
#define _GameState_

#include "State.h"

/* 
Our menu state!

*/

class GameState: public State {
public:
	GameState();
	void onEnter();
	void onExit();
};

#endif // _GameState_