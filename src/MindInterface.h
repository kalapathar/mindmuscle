#ifndef _MindInterface_
#define _MindInterface_

#include "Globals.h"

/* 
This class handles everything needed to 
create a way to communicate with the 
python script that reads the mind data

*/

class MindInterface {
public:
	

	MindInterface();
	~MindInterface();
	void update();
	void disconnect();
};

#endif // _MindInterface_