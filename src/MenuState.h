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

	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);

};

#endif // _MenuState_