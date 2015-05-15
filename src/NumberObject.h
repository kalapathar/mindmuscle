#ifndef _NUMBEROBJECT_
#define _NUMBEROBJECT_

#include "Globals.h"
#include "GameObject.h"
#include <iostream>

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "NumberObject.h"

class NumberObject {
public:
    unsigned int curNumber = 0;
    float w, h, X, Y;
    
    GameObject* tensObj = NULL; // ID of the tens GameObject
    GameObject* onesObj = NULL; // ID of the ones GameObject
    
    NumberObject(float w=128, float h=256, float X=0, float Y=0, unsigned int number=0);
    
    ~NumberObject();
    
    void initObjects(unsigned int number);
    void updateNumber(unsigned int number);
    void draw();
    
    const char * intToString(unsigned int number);
};

#endif // _NUMBEROBJECT_