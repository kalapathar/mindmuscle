#ifndef _ReadingState_
#define _ReadingState_

#include "../State.h"

/* 
Our menu state!

*/

class ReadingState: public State {
public:
	ReadingState();
	void onEnter();
	void onExit();

	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
};

#endif // _ReadingState_