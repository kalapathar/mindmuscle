#include <string>
#include <iostream>
using namespace std;

#include "CalibrateState.h"
#include "../GameObject.h"
#include "../EyeInterface.h"
#include <time.h> 

GameObject * cursorobj;
GameObject * box;
GameObject * box2;
GameObject * ground;
GameObject * ceiling;
float gameCounter = 0;
b2Vec2 * force;

GameObject * wallRight;
GameObject * wallLeft;

EyeInterface * eye2;
int lastBlinkID;

std::vector<GameObject *> objectArray;

float shakePower = 0;

void CalibrateState::onEnter(){
	cursorobj = new GameObject("boxCrate",false); objectArray.push_back(cursorobj);
	box = new GameObject("boxCrate_double",true,100,100,false,GAME_WIDTH/2+50,200); objectArray.push_back(box);
	box2 = new GameObject("boxCrate",true,100,100,false,GAME_WIDTH/2,50); objectArray.push_back(box2);
	ground = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,GAME_HEIGHT); objectArray.push_back(ground);
	ceiling = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,0); objectArray.push_back(ceiling);

	wallRight = new GameObject("boxItem",true,10,GAME_HEIGHT,true,0,GAME_HEIGHT/2); objectArray.push_back(wallRight);
	wallLeft = new GameObject("boxItem",true,10,GAME_HEIGHT,true,GAME_WIDTH,GAME_HEIGHT/2); objectArray.push_back(wallLeft);

	force = new b2Vec2(0,0);
	eye2 = new EyeInterface;

	cursorobj->x = GAME_WIDTH/2.0;
	cursorobj->y = GAME_HEIGHT/2.0;

	cursorobj->alpha = 0.5;

	lastBlinkID = 0;

	shakePower = 0;
}

void CalibrateState::onExit(){
	//Delete all objects
	for(int i=0;i<objectArray.size();i++) delete objectArray[i];
	objectArray.clear();

	delete force;
	delete eye2;

}

CalibrateState::CalibrateState(){
	name = "Game";
}


void CalibrateState::update(){
	eye2->update();

	gameCounter +=0.05;

	cursorobj->x += (eye2->x-cursorobj->x) / 30;
	cursorobj->y += (eye2->y-cursorobj->y) / 30;
	//Bind the cursor to screen
	if(cursorobj->x < 0) cursorobj->x = 0;
	if(cursorobj->x > GAME_WIDTH) cursorobj->x = GAME_WIDTH;

	if(cursorobj->y < 0) cursorobj->y = 0;
	if(cursorobj->y > GAME_HEIGHT) cursorobj->y = GAME_HEIGHT;
	//cout << "(" << eye2->x << "," << eye2->y << ")" << endl;
	

	double focusValue = 0;
	focusValue = mind->focusValue;
	double normalizedFocus = (focusValue/100.0) * 10;

	if(focusValue > 30) force->y = box2->body->GetLinearVelocity().y - normalizedFocus;
	//cout << focusValue << endl;

	
	if(box2->y <= 0 || focusValue <= 30) force->y = box2->body->GetLinearVelocity().y;

	box2->body->SetLinearVelocity(*force);

	if(cursorobj->alpha > 0.5) cursorobj->alpha += (0.5-cursorobj->alpha) / 20;

	if(lastBlinkID != eye2->blinkCount){
		lastBlinkID = eye2->blinkCount;
		cursorobj->alpha = 1;
	}


	//Screenshake update
	if(shakePower > 0){
		if(shakePower < 1)shakePower = 0;
		shakePower *= 0.9;
		Xoffset = ((rand() % 100 - 50) / 100.0) * shakePower;
		Yoffset = ((rand() % 100 - 50) / 100.0) * shakePower;
	}
}

void CalibrateState::render(){
	for(int i=0;i<objectArray.size();i++) objectArray[i]->draw();

	//Draw focus text
		glColor3f(0/255.0, 0/255.0, 0/255.0);
	string focusT = "Focus : " + std::to_string(mind->focusValue);
	cursorobj->drawText(GAME_WIDTH/2-20,50,focusT.c_str());

	//Draw gaze (x,y)
	string eyeT = "Gaze : " + string("(") +  std::to_string(eye2->x) + string(",") + std::to_string(eye2->y) + string(")") ;
	cursorobj->drawText(GAME_WIDTH/2-20,70,eyeT.c_str());
}

void CalibrateState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}

	// if(c == 's'){
 //    	//Screenshake!
 //    	shakePower = 10;
 //  	}

 }

void CalibrateState::mouse(int button, int state, int x, int y){
	eye2->mouse(button,state,x,y);
}

void CalibrateState::mouse_motion(int x,int y){
	eye2->mouse_motion(x,y);
}
