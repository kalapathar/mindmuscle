#ifndef _GameState_
#define _GameState_

#include "../State.h"

/* 
Our menu state!

*/

class GameState: public State {
public:
	GameState();
	void onEnter();
	void onExit();

	//Empty states
	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
};

#endif // _GameState_