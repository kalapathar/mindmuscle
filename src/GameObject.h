#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include "Box2D/Box2D.h"

/* 
Base class for every drawable on screen

*/

class GameObject {

public:
	int textureID;//Represents current texture to draw
	float x,y,angle;//Coordinates
	float width,height;//Dimensions of image
	b2Body * body;//Pointer to box2d body
	int depth;//For drawing order
	int alpha;//Transparency

	static int numObjects;//Represents the number of objects created

	//Constructor
	GameObject(const char * filename,bool isBox2d);

	//Destructor
	~GameObject();

	//methods
	void draw();//Render at the correct position
};

#endif // _GAMEOBJECT_