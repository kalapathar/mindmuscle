#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include "Box2D/Box2D.h"
#include "Globals.h"

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


/* 
Base class for every drawable on screen

*/

class GameObject {
public:

	int initDelay;
	int textureID;//Represents current texture to draw
	float x,y,angle;//Coordinates
	float width,height;//Dimensions of image
	b2Body * body;//Pointer to box2d body
	int depth;//For drawing order
	float alpha;//Transparency
	float rFactor;
	float gFactor;
	float bFactor;

	static int numObjects;//Represents the number of objects created

	//Constructor
	GameObject(const char * filename,bool isBox2d,
		float w=100,float h=100,bool isStatic=false,
		float X=0,float Y=0);
	//Destructor
	~GameObject();

	//methods
	void draw();//Render at the correct position
	//Helper functions
	b2Body * createBox(float w,float h,bool bodyType);
	void drawText(double x, double y, const char *text,int size=0);

	
};

#endif // _GAMEOBJECT_