#include <string>
#include <string.h>
#include <iostream>
using namespace std;

#include "GameObject.h"
#include "texture.h"

//Initialize static variable
int GameObject::numObjects = 0;

b2Body * GameObject::createBox(float w,float h,bool isStatic){
	// Define the dynamic body. We set its position and call the body factory.
	w = w / 2;
	h = h / 2;

	b2BodyDef bodyDef;
	if(!isStatic) bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x,y);
	b2Body* body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(w,h);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	if(!isStatic){
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.2f;
		// Override the default friction.
		fixtureDef.friction = 0.3f;
	}
	else {
		fixtureDef.density = 0.0f;
	}

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	return body;
}

// the drawText function draws some text at location x, y
//   note:  the text to be drawn is a C-style string!
void GameObject::drawText(double x, double y, const char *text)
{
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}

GameObject::GameObject(const char * filename,bool isBox2d,float w,float h,bool isStatic,float X,float Y) {
	//Create texture from filename. Create box2d if isBox2d and assign defaults to everything else.
	char fullname[200];
	strcpy(fullname,"Images/");
	strcat(fullname,filename);
	strcat(fullname,".pam");
	textureID = loadTexture(fullname);
	///TODO: Catch error if image is not found and set default image so it doesn't crash

	width = w;
	height = h;
	x = X; y = Y; angle = 0;
	alpha = 1.0;
	depth = numObjects;
	numObjects++;//Increment object counter
	initDelay = 0;
	rFactor = 1.0;
	gFactor = 1.0;
	bFactor = 1.0;


	if(isBox2d){
		//Create box2d body
		body = createBox(w,h,isStatic);
	} else {
		body = 0;
	}
}

GameObject::~GameObject(){
	//Destroy texture and box2d body if exists
	cout << "Destroy game object" << endl;
	if(body != 0){
		//Destroy box2d body
		world->DestroyBody(body);
		body = 0;
	}
}

void GameObject::draw(){

	if(initDelay > 0){
		initDelay --;
		return;
	}
	if(body != 0){
		//If box2d exists, set x,y and angle to body's coordinates
		x = body->GetPosition().x;
		y = body->GetPosition().y;
		angle = -body->GetAngle();
	}

	drawTexture(textureID,  x-width/2 + Xoffset,y-height/2 + Yoffset, width,height,alpha,angle,rFactor,gFactor,bFactor);
}