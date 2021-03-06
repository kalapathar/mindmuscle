#ifndef _GLOBALS_
#define _GLOBALS_

#include "Box2D/Box2D.h"
#include "MindInterface.h"
#include <string>

extern int GAME_WIDTH;
extern int GAME_HEIGHT;
extern string FOLDER;
extern b2World * world;
extern MindInterface * mind;
extern bool MIND_CONNECTED;
extern bool CAM_CONNECTED;
extern float Xoffset;
extern float Yoffset;

#endif // _GLOBALS_
