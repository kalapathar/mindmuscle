#ifndef _MenuState_
#define _MenuState_

#include "State.h"

/* 
Our menu state!

*/

class MenuState: public State {
public:
	MenuState();
	void onEnter();
	void onExit();
};

#endif // _MenuState_