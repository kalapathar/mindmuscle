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
GameObject * ledgeOne;
GameObject * ledgeTwo;

float level_gameCounter = 0;
b2Vec2 * level_force;

GameObject * level_wallRight;
GameObject * level_wallLeft;

EyeInterface * level_eye2;
int level_lastBlinkID;

std::vector<GameObject *> level_objectArray;
std::vector<GameObject *> level_boxArray;

std::vector<GameObject *> bombArray;
std::vector<GameObject *> explodeArray;

float level_shakePower = 0;
int level_prevCursorX;
int level_prevCursorY;

GameObject * activelevel_box;
int level_liftThreshold = 30;

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

	levelone_timer = 60;//60 * 30;

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
	levelStats[3] = 0;//Average focus
	levelStats[4] = 0;//Highest focus
	levelStats[5] = 0;//Time to complete the level
	totalCount = 0;

	instructions = new GameObject("leveltwo_instructions",false,379,35); level_objectArray.push_back(instructions);
	instructions->x = GAME_WIDTH/2;
	instructions->y = 100;

	level_ground = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,GAME_HEIGHT); level_objectArray.push_back(level_ground);
	level_ceiling = new GameObject("boxItem",true,GAME_WIDTH,10,true,GAME_WIDTH/2,0); level_objectArray.push_back(level_ceiling);
	level_wallRight = new GameObject("boxItem",true,10,GAME_HEIGHT,true,0,GAME_HEIGHT/2); level_objectArray.push_back(level_wallRight);
	level_wallLeft = new GameObject("boxItem",true,10,GAME_HEIGHT,true,GAME_WIDTH,GAME_HEIGHT/2); level_objectArray.push_back(level_wallLeft);

	level_box = new GameObject("boxCrate_double",true,100,100,false,50,GAME_HEIGHT/2 +100); level_objectArray.push_back(level_box);
	level_boxArray.push_back(level_box);

	//Create the ledges
	ledgeOne = new GameObject("boxItem",true,200,10,true,100,GAME_HEIGHT/2 + 200); level_objectArray.push_back(ledgeOne);
	ledgeTwo = new GameObject("boxItem",true,200,10,true,GAME_WIDTH - 100,GAME_HEIGHT/2 + 200); level_objectArray.push_back(ledgeTwo);
}

void destroyLevelTwo(){
	levelStats[3] /= totalCount;

	delete level_box;
	delete level_ground;
	delete level_ceiling;
	delete level_wallLeft;
	delete level_wallRight;
	delete instructions;
	delete ledgeOne;
	delete ledgeTwo;
	level_objectArray.clear();
	level_boxArray.clear();

	level_objectArray.push_back(level_cursorobj);
}

void initLevelThree(){
	levelone_timer = 0;
	levelStats[6] = 0;//Average focus
	levelStats[7] = 0;//Highest focus
	levelStats[8] = 0;//Num of bombs exploded
	totalCount = 0;
	level_gameCounter = 0;


	instructions = new GameObject("levelthree_instructions",false,379,35); level_objectArray.push_back(instructions);
	instructions->x = GAME_WIDTH/2;
	instructions->y = 100;

	//Resuze the cursor
	level_cursorobj->width = 100;
	level_cursorobj->height = 100;
}

void destroyLevelThree(){
	levelStats[6] /= totalCount;

	delete instructions;
	level_objectArray.clear();
	level_boxArray.clear();

	level_objectArray.push_back(level_cursorobj);
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

	bombArray.clear();
	explodeArray.clear();

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
		// if(focusValue > level_liftThreshold) level_force->y = activelevel_box->body->GetLinearVelocity().y - normalizedFocus * 3;
		// if(activelevel_box->y <= 0 || focusValue <= level_liftThreshold) level_force->y = activelevel_box->body->GetLinearVelocity().y;
		
		if(activelevel_box->y > (1.0 - normalizedFocus) * GAME_HEIGHT) level_force->y = activelevel_box->body->GetLinearVelocity().y - 3;
                else level_force->y = 0;

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

		//Calculate the stats
		totalCount ++;
		levelStats[0] += focusValue;
		if(focusValue > levelStats[1]) levelStats[1] = focusValue;
		levelStats[2]++;

		//If they get to the other ledge, or close enough, go to the next level
		int dy = 504 - level_boxArray[0]->y;
		int dx = 910 - level_boxArray[0]->x;
		int distance = sqrt(dx * dx + dy * dy);
		if(distance < 50){
			level++;
			destroyLevelTwo();
			initLevelThree();
		}

	}

	if(level == 3){
		//Level three update

		//Spawn a bomb every second
		if(levelone_timer < 0){
			levelone_timer = 60;
			GameObject * bomb = new GameObject("bomb",false,64,64); level_objectArray.push_back(bomb);
			bomb->x = rand() % GAME_WIDTH;
			bomb->y = -50;
			bombArray.push_back(bomb);
			level_gameCounter ++;
		}
		levelone_timer--;


		//Bomb update
		for(int i=bombArray.size()-1;i>=0;i--){
			bombArray[i]->y +=2;
			bombArray[i]->angle += 0.05;
			//Check if cursor is hitting any bomb with a high enough focus
			float dy = bombArray[i]->y - level_cursorobj->y;
			float dx = bombArray[i]->x - level_cursorobj->x;
			float distance = sqrt(dx * dx + dy * dy);
			bool removeBomb = false;
			if(distance < 50 && focusValue > 50){
				//Add explosion and do screenshake
				//Increase count
				bombArray[i]->alpha = 0;
				
				levelStats[8]++;
				level_shakePower = 30;
				GameObject * explode = new GameObject("explode",false,195,245); level_objectArray.push_back(explode);
				explode->x = bombArray[i]->x;
				explode->y = bombArray[i]->y;
				explodeArray.push_back(explode);
				bombArray[i]->x = -100;
			}

			//Remove bomb if it's outside the screen
			if(bombArray[i]->y > GAME_HEIGHT + bombArray[i]->height){
				removeBomb = true;
			}

			if(removeBomb){
				delete bombArray[i];
				
				//Remove it from object array too
				for(int j=0;j<level_objectArray.size();j++){
					if(level_objectArray[j] == bombArray[i]) {
						level_objectArray.erase(level_objectArray.begin()+j);
						break;
					}
				}
				bombArray.erase(bombArray.begin()+i);//Remove it from the array
			}
		}

		for(int i=0;i<explodeArray.size();i++){
			explodeArray[i]->alpha -= 0.02;
			//If the alpha is 0, remove it
			if(explodeArray[i]->alpha <= 0){
				delete explodeArray[i];
				
				//And from the object array
				for(int j=0;j<level_objectArray.size();j++){
					if(level_objectArray[j] == explodeArray[i]) {
						level_objectArray.erase(level_objectArray.begin()+j);
						break;
					}
				}
				//From the explodeArray
				explodeArray.erase(explodeArray.begin()+i);
			}
		}


		//After thirty seconds, go to the final screen
		if(level_gameCounter > 30){
			destroyLevelThree();
			level++;
			
		}
	}
}

void LevelOne::render(){
	for(int i=0;i<level_objectArray.size();i++) level_objectArray[i]->draw();

	if(level == 1){
		//Timer text
		glColor3f(0/255.0, 0/255.0, 0/255.0);
		string timeText = "Time left : " + std::to_string(levelone_timer/60);
		level_box->drawText(GAME_WIDTH/2-70,170,timeText.c_str());
	}
	if(level == 3){
		glColor3f(0/255.0, 0/255.0, 0/255.0);
		string bombText = "Bombs destroyed : " + std::to_string(levelStats[8]);
		instructions->drawText(GAME_WIDTH/2-70,170,bombText.c_str());
	}
}

void LevelOne::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}

	// if(c == 's'){
 //    	//Screenshake!
 //    	level_shakePower = 30;
 //  	}

 }

void LevelOne::mouse(int button, int state, int x, int y){
	level_eye2->mouse(button,state,x,y);
}

void LevelOne::mouse_motion(int x,int y){
	level_eye2->mouse_motion(x,y);
}
