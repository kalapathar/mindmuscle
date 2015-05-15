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
std::vector<GameObject *> boxArray;


float shakePower = 0;
int prevCursorX;
int prevCursorY;

GameObject * activeBox;
int liftThreshold = 30;

void CalibrateState::onEnter(){
	
	box = new GameObject("boxCrate_double",true,100,100,false,GAME_WIDTH/2+50,200); objectArray.push_back(box);
	box2 = new GameObject("boxCrate",true,100,100,false,GAME_WIDTH/2,50); objectArray.push_back(box2);
	cursorobj = new GameObject("outline",false,185,185); objectArray.push_back(cursorobj);
	ground = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,GAME_HEIGHT); objectArray.push_back(ground);
	ceiling = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,0); objectArray.push_back(ceiling);

	boxArray.push_back(box);
	boxArray.push_back(box2);
	activeBox = 0;

	wallRight = new GameObject("boxItem",true,10,GAME_HEIGHT,true,0,GAME_HEIGHT/2); objectArray.push_back(wallRight);
	wallLeft = new GameObject("boxItem",true,10,GAME_HEIGHT,true,GAME_WIDTH,GAME_HEIGHT/2); objectArray.push_back(wallLeft);

	force = new b2Vec2(0,0);
	eye2 = new EyeInterface;

	cursorobj->x = GAME_WIDTH/2.0;
	cursorobj->y = GAME_HEIGHT/2.0;
	cursorobj->gFactor = 0;
	cursorobj->bFactor = 0;

	cursorobj->alpha = 0.5;

	lastBlinkID = 0;

	shakePower = 0;

	prevCursorX = cursorobj->x;
	prevCursorY = cursorobj->y;
}

void CalibrateState::onExit(){
	//Delete all objects
	for(int i=0;i<objectArray.size();i++) delete objectArray[i];
	objectArray.clear();
	boxArray.clear();

	delete force;
	delete eye2;

}

CalibrateState::CalibrateState(){
	name = "Game";
}


void CalibrateState::update(){
	eye2->update();

	gameCounter +=0.05;


	cursorobj->x = prevCursorX;
	cursorobj->y = prevCursorY;
	cursorobj->x += (eye2->x-cursorobj->x) / 30;
	cursorobj->y += (eye2->y-cursorobj->y) / 30;
	//Bind the cursor to screen
	if(cursorobj->x < 0) cursorobj->x = 0;
	if(cursorobj->x > GAME_WIDTH) cursorobj->x = GAME_WIDTH;

	if(cursorobj->y < 0) cursorobj->y = 0;
	if(cursorobj->y > GAME_HEIGHT) cursorobj->y = GAME_HEIGHT;
	//Round the position to prevent artifacts
	cursorobj->x = (int)cursorobj->x;
	cursorobj->y = (int)cursorobj->y;
	cursorobj->alpha = 1.0;

	double focusValue = 0;
	focusValue = mind->focusValue;
	double normalizedFocus = (focusValue/100.0);

	//Change color of cursor based on focus:
	cursorobj->rFactor = 1.0 - normalizedFocus;
	cursorobj->gFactor = normalizedFocus;

	prevCursorX = cursorobj->x;
	prevCursorY = cursorobj->y;

	//Snap the cursor to closest box
	if(focusValue < liftThreshold) activeBox = 0;
	for(int i=0;i<boxArray.size();i++){
		float dy = boxArray[i]->y - cursorobj->y;
		float dx = boxArray[i]->x - cursorobj->x;
		float distance = sqrt(dx * dx + dy * dy);
		if(distance < 50){//Radius of circle is 50
			//If close enough, snap
			
			activeBox = boxArray[i];
		}
	}
	

	if(activeBox){
		cursorobj->x = activeBox->x;
		cursorobj->y = activeBox->y;
		//Lift with focus
		// if(focusValue > liftThreshold) force->y = activeBox->body->GetLinearVelocity().y - normalizedFocus * 3;
		// if(activeBox->y <= 0 || focusValue <= liftThreshold) force->y = activeBox->body->GetLinearVelocity().y;
		
		if(activeBox->y > (1.0 - normalizedFocus) * GAME_HEIGHT) force->y = activeBox->body->GetLinearVelocity().y - 3;
                else force->y = 0;
                
		//Move left/right with gaze
		int Xspeed = 1;
		if(eye2->x > activeBox->x) force->x += Xspeed; else  force->x -= Xspeed; 
		if(force->x > 30) force->x = 30;
		if(force->x < -30) force->x = -30;

		activeBox->body->SetLinearVelocity(*force);

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
	cursorobj->drawText(GAME_WIDTH/2-20,50,focusT.c_str(),0);

	//Draw gaze (x,y)
	string eyeT = "Gaze : " + string("(") +  std::to_string(eye2->x) + string(",") + std::to_string(eye2->y) + string(")") ;
	cursorobj->drawText(GAME_WIDTH/2-20,70,eyeT.c_str(),0);
}

void CalibrateState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}

	if(c == 's'){
    	//Screenshake!
    	shakePower = 30;
  	}

 }

void CalibrateState::mouse(int button, int state, int x, int y){
	eye2->mouse(button,state,x,y);
}

void CalibrateState::mouse_motion(int x,int y){
	eye2->mouse_motion(x,y);
}
