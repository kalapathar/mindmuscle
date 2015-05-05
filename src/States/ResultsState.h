#ifndef _ResultsState_
#define _ResultsState_

#include "../State.h"
#include "../Globals.h"
/* 
Our menu state!

*/

class ResultsState: public State {
public:
	ResultsState();
	void onEnter();
	void onExit();

	void update();
	void render();
	void keyboard(unsigned char c, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
};

#endif // _ResultsState_