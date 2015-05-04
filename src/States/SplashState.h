#ifndef _SplashState_
#define _SplashState_

#include "../State.h"
#include "../Globals.h"

/* 
Our menu state!

*/

class SplashState: public State {
public:
	SplashState();
	void onEnter();
	void onExit();

	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
};

#endif // _SplashState_