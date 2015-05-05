#ifndef _AboutState_
#define _AboutState_

#include "../State.h"
#include "../Globals.h"

/* 
Our menu state!

*/

class AboutState: public State {
public:
	AboutState();
	void onEnter();
	void onExit();

	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
};

#endif // _AboutState_