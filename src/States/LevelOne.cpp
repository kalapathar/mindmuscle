#include <string>
#include <iostream>
using namespace std;

#include "LevelOne.h"
#include "../GameObject.h"
#include "../EyeInterface.h"
#include <time.h> 

GameObject * level_cursorobj;
GameObject * level_box;
GameObject * level_ground;
GameObject * level_ceiling;
float level_gameCounter = 0;
b2Vec2 * level_force;

GameObject * level_wallRight;
GameObject * level_wallLeft;

EyeInterface * level_eye2;
int level_lastBlinkID;

std::vector<GameObject *> level_objectArray;
std::vector<GameObject *> level_boxArray;


float level_shakePower = 0;
int level_prevCursorX;
int level_prevCursorY;

GameObject * activelevel_box;
int level_liftThreshold = 10;

int level;
int levelone_timer;

GameObject * instructions;

int levelStats[9];
int totalCount;

void initLevelOne(){

	levelStats[0] = 0;//Average focus
	levelStats[1] = 0;//Highest focus
	levelStats[2] = 0;//Time above 50%
	totalCount = 0;

	levelone_timer = 60* 30000;//60 * 30;

	level_box = new GameObject("boxCrate_double",true,100,100,false,GAME_WIDTH/2+50,200); level_objectArray.push_back(level_box);
	level_ground = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,GAME_HEIGHT); level_objectArray.push_back(level_ground);
	level_ceiling = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,0); level_objectArray.push_back(level_ceiling);

	level_boxArray.push_back(level_box);

	instructions = new GameObject("levelone_instructions",false,395,70); level_objectArray.push_back(instructions);
	instructions->x = GAME_WIDTH/2;
	instructions->y = 100;
	

	level_wallRight = new GameObject("boxItem",true,10,GAME_HEIGHT,true,0,GAME_HEIGHT/2); level_objectArray.push_back(level_wallRight);
	level_wallLeft = new GameObject("boxItem",true,10,GAME_HEIGHT,true,GAME_WIDTH,GAME_HEIGHT/2); level_objectArray.push_back(level_wallLeft);
}
void destroyLevelOne(){
	//Calculate the average
	levelStats[0] /= totalCount;

	delete level_box;
	delete level_ground;
	delete level_ceiling;
	delete level_wallLeft;
	delete level_wallRight;
	delete instructions;
	level_objectArray.clear();
	level_boxArray.clear();

	level_objectArray.push_back(level_cursorobj);
}

void initLevelTwo(){

}

void destroyLevelTwo(){

}

void LevelOne::onEnter(){
	initLevelOne();

	level = 1;


	level_cursorobj = new GameObject("outline",false,185,185); level_objectArray.push_back(level_cursorobj);
	level_force = new b2Vec2(0,0);
	level_eye2 = new EyeInterface;
	level_cursorobj->x = GAME_WIDTH/2.0;
	level_cursorobj->y = GAME_HEIGHT/2.0;
	level_cursorobj->gFactor = 0;
	level_cursorobj->bFactor = 0;
	level_lastBlinkID = 0;
	level_shakePower = 0;
	activelevel_box = 0;
	level_prevCursorX = level_cursorobj->x;
	level_prevCursorY = level_cursorobj->y;
}

void LevelOne::onExit(){
	//Delete all objects
	for(int i=0;i<level_objectArray.size();i++) delete level_objectArray[i];
	level_objectArray.clear();
	level_boxArray.clear();

	delete level_force;
	delete level_eye2;
}

LevelOne::LevelOne(){
	name = "LevelOne";
}


void LevelOne::update(){
	level_eye2->update();

	level_gameCounter +=0.05;


	level_cursorobj->x = level_prevCursorX;
	level_cursorobj->y = level_prevCursorY;
	level_cursorobj->x += (level_eye2->x-level_cursorobj->x) / 30;
	level_cursorobj->y += (level_eye2->y-level_cursorobj->y) / 30;
	//Bind the cursor to screen
	if(level_cursorobj->x < 0) level_cursorobj->x = 0;
	if(level_cursorobj->x > GAME_WIDTH) level_cursorobj->x = GAME_WIDTH;

	if(level_cursorobj->y < 0) level_cursorobj->y = 0;
	if(level_cursorobj->y > GAME_HEIGHT) level_cursorobj->y = GAME_HEIGHT;
	//Round the position to prevent artifacts
	level_cursorobj->x = (int)level_cursorobj->x;
	level_cursorobj->y = (int)level_cursorobj->y;
	level_cursorobj->alpha = 1.0;

	double focusValue = 0;
	focusValue = mind->focusValue;
	double normalizedFocus = (focusValue/100.0);

	//Change color of cursor based on focus:
	level_cursorobj->rFactor = 1.0 - normalizedFocus;
	level_cursorobj->gFactor = normalizedFocus;

	level_prevCursorX = level_cursorobj->x;
	level_prevCursorY = level_cursorobj->y;

	//Snap the cursor to closest level_box
	if(focusValue < level_liftThreshold) activelevel_box = 0;
	for(int i=0;i<level_boxArray.size();i++){
		float dy = level_boxArray[i]->y - level_cursorobj->y;
		float dx = level_boxArray[i]->x - level_cursorobj->x;
		float distance = sqrt(dx * dx + dy * dy);
		if(distance < 50){//Radius of circle is 50
			//If close enough, snap
			
			activelevel_box = level_boxArray[i];
		}
	}
	

	if(activelevel_box){
		level_cursorobj->x = activelevel_box->x;
		level_cursorobj->y = activelevel_box->y;
		//Lift with focus
		cout << activelevel_box->y << "\t" << GAME_HEIGHT/2.0 << endl;
		//(1.0 - normalizedFocus) *
		if(activelevel_box->y > (1.0 - normalizedFocus) * GAME_HEIGHT) level_force->y = activelevel_box->body->GetLinearVelocity().y - 3;
		else level_force->y = 0;
		//if(activelevel_box->y <= 0 || focusValue <= level_liftThreshold) level_force->y = activelevel_box->body->GetLinearVelocity().y;
		
		//Move left/right with gaze
		int Xspeed = 1;
		if(level_eye2->x > activelevel_box->x) level_force->x += Xspeed; else  level_force->x -= Xspeed; 
		if(level_force->x > 30) level_force->x = 30;
		if(level_force->x < -30) level_force->x = -30;

		activelevel_box->body->SetLinearVelocity(*level_force);

	}



	//Screenshake update
	if(level_shakePower > 0){
		if(level_shakePower < 1)level_shakePower = 0;
		level_shakePower *= 0.9;
		Xoffset = ((rand() % 100 - 50) / 100.0) * level_shakePower;
		Yoffset = ((rand() % 100 - 50) / 100.0) * level_shakePower;
	}

	if(level == 1){
		//Level one update
		levelone_timer--;

		//Calculate the stats
		totalCount ++;
		levelStats[0] += focusValue;
		if(focusValue > levelStats[1]) levelStats[1] = focusValue;
		if(focusValue > 50) levelStats[2]++;


		//If timer runs out, go to next state
		if(levelone_timer <= 0){
			level++;
			destroyLevelOne();
			initLevelTwo();
		}
	}

	if(level == 2){
		//Level two update
	}

	if(level == 3){
		//Level three update
	}
	cout<<normalizedFocus<<endl;
}

void LevelOne::render(){
	for(int i=0;i<level_objectArray.size();i++) level_objectArray[i]->draw();

	if(level == 1){
		//Timer text
		glColor3f(0/255.0, 0/255.0, 0/255.0);
		string timeText = "Time left : " + std::to_string(levelone_timer/60);
		level_box->drawText(GAME_WIDTH/2-70,170,timeText.c_str());
	}
}

void LevelOne::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}

	if(c == 's'){
    	//Screenshake!
    	level_shakePower = 30;
  	}

 }

void LevelOne::mouse(int button, int state, int x, int y){
	level_eye2->mouse(button,state,x,y);
}

void LevelOne::mouse_motion(int x,int y){
	level_eye2->mouse_motion(x,y);
}
