#ifndef _MindInterface_
#define _MindInterface_

#include "PyInstall/include/python2.7/Python.h"
#include "Globals.h"

/* 
This class handles everything needed to 
create a way to communicate with the 
python script that reads the mind data

*/

class MindInterface {
public:
	PyObject *pName, *pModule, *pDict;
	int state;
	int counter;
	long focusValue;

	MindInterface();
	~MindInterface();
	void update();
	void init_connect();
	void attempt_connect();
	void get_focus();
	int get_status();
	void disconnect();
};

#endif // _MindInterface_