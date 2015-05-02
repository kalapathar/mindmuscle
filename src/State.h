#ifndef _STATE_
#define _STATE_


/* 
The state class is a basic state system in its own right, but is meant to
be used with StateMachine.

All it really is is a name, and a function to run when it's created, 
and a function to run when it's destroyed

*/

class State {
public:
	//State variables
	string name;
	//Our transition functions that will be overriden 
	virtual void onEnter()=0;
	virtual void onExit()=0;
	virtual void update()=0;
	virtual void render()=0;
	virtual void keyboard(unsigned char c, int x, int y)=0;
	virtual void mouse(int button, int state, int x, int y)=0;
	virtual void mouse_motion(int x,int y)=0;
};

#endif // _STATE_