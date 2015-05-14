#ifndef _CalibrateState_
#define _CalibrateState_

#include "../State.h"

/* 
Our menu state!

*/

class CalibrateState: public State {
public:
	CalibrateState();
	void onEnter();
	void onExit();

	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
};

#endif // _CalibrateState_