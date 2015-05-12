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

void GameState::onEnter(){
	testobj = new GameObject("boxCrate",false);
	box = new GameObject("boxCrate_double",true,100,100,false,GAME_WIDTH/2+50,-200);
	box2 = new GameObject("boxCrate",true,100,100,false,GAME_WIDTH/2,0);
	ground = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,500);

	wallRight = new GameObject("boxItem",true,10,GAME_HEIGHT,true,0,100);
	wallLeft = new GameObject("boxItem",true,10,GAME_HEIGHT,true,GAME_WIDTH,100);

	force = new b2Vec2(0,0);
	eye2 = new EyeInterface;

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
	testobj->x = GAME_WIDTH/2.0;
	testobj->y = GAME_HEIGHT/2.0;
	testobj->angle +=0.05;

	testobj->x += (eye2->x-testobj->x);
	testobj->y += (eye2->y-testobj->y);
	
	if(box2-> y < 200){
		force->y +=1;
	} else {
		force->y -=1;
	}
	//cout << eye2->x << endl;


	if(eye2->x > 200){//45 is the center for pupil. 200 for the face
		force->x += 1;
	} else {
		force->x -= 1;
	}
	if(abs(force->x) > 25){
		force->x = 25 * (abs(force->x)/force->x);
	}

	
	box2->body->SetLinearVelocity(*force);

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
