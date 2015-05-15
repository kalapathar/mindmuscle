#ifndef _LevelOne_
#define _LevelOne_

#include "../State.h"

/* 
Our menu state!

*/

class LevelOne: public State {
public:
	
	LevelOne();
	void onEnter();
	void onExit();

	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
};

#endif // _LevelOne_