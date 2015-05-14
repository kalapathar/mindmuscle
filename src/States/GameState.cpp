#include <string>
#include <iostream>
using namespace std;

#include "GameState.h"
#include "../GameObject.h"
#include "../EyeInterface.h"

GameObject * testobj;
GameObject * box;
GameObject * box2;
GameObject * ground;
float gameCounter = 0;
b2Vec2 * force;

GameObject * wallRight;
GameObject * wallLeft;

EyeInterface * eye2;
int lastBlinkID;


void GameState::onEnter(){
	testobj = new GameObject("boxCrate",false);
	box = new GameObject("boxCrate_double",true,100,100,false,GAME_WIDTH/2+50,-200);
	box2 = new GameObject("boxCrate",true,100,100,false,GAME_WIDTH/2,0);
	ground = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,500);

	wallRight = new GameObject("boxItem",true,10,GAME_HEIGHT,true,0,100);
	wallLeft = new GameObject("boxItem",true,10,GAME_HEIGHT,true,GAME_WIDTH,100);

	force = new b2Vec2(0,0);
	eye2 = new EyeInterface;

	testobj->x = GAME_WIDTH/2.0;
	testobj->y = GAME_HEIGHT/2.0;

	testobj->alpha = 0.5;

	lastBlinkID = 0;
}

void GameState::onExit(){
	delete testobj;
	delete box;
	delete box2;
	delete ground;

	delete force;
	delete eye2;

	delete wallRight;
	delete wallLeft;
}

GameState::GameState(){
	name = "Game";
}


void GameState::update(){
	eye2->update();

	gameCounter +=0.05;

	testobj->x += (eye2->x-testobj->x) / 30;
	testobj->y += (eye2->y-testobj->y) / 30;
	//cout << "(" << testobj->x << "," << testobj->y << ")" << endl;
	

	double focusValue = 0;
	if(MIND_CONNECTED) focusValue = mind->focusValue;
	double normalizedFocus = (focusValue/100.0) * 10;

	if(focusValue > 30) force->y = box2->body->GetLinearVelocity().y - normalizedFocus;
	//cout << focusValue << endl;

	
	if(box2->y <= 0) force->y = box2->body->GetLinearVelocity().y;

	box2->body->SetLinearVelocity(*force);

	if(testobj->alpha > 0.5) testobj->alpha += (0.5-testobj->alpha) / 20;

	if(lastBlinkID != eye2->blinkCount){
		lastBlinkID = eye2->blinkCount;
		testobj->alpha = 1;
	}
}

void GameState::render(){
	testobj->draw();
	box->draw();
	box2->draw();
	ground->draw();
	wallRight->draw();
	wallLeft->draw();
}

void GameState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}
}

void GameState::mouse(int button, int state, int x, int y){

}

void GameState::mouse_motion(int x,int y){

}
