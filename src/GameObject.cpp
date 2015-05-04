#include <string>
#include <string.h>
#include <iostream>
using namespace std;

#include "GameObject.h"
#include "texture.h"

//Initialize static variable
int GameObject::numObjects = 0;

//Hardocoded until I can figure out how to make these global
int GAME_WIDTH = 1024;
int GAME_HEIGHT = 720;

GameObject::GameObject(const char * filename,bool isBox2d){
	//Create texture from filename. Create box2d if isBox2d and assign defaults to everything else.
	char fullname[200];
	strcpy(fullname,"Images/");
	strcat(fullname,filename);
	strcat(fullname,".pam");
	textureID = loadTexture(fullname);
	///TODO: Catch error if image is not found and set default image so it doesn't crash

	if(isBox2d){
		//Create box2d body
	} else {
		body = 0;
	}

	width = 100;
	height = 100;
	x = 0; y = 0; angle = 0;
	alpha = 1;
	depth = numObjects;
	numObjects++;//Increment object counter

}

GameObject::~GameObject(){
	//Destroy texture and box2d body if exists

	if(body != 0){
		//Destroy box2d body
	}
}

void GameObject::draw(){
	if(body != 0){
		//If box2d exists, set x,y and angle to body's coordinates
	}
	drawTexture(textureID,  x-width/2,y-height/2, width,height,alpha,angle);
}