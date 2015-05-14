#include <string>
#include <iostream>
using namespace std;
#include <fstream>

#include "ResultsState.h"
#include "../texture.h"
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

int results;

double maximumX, maximumY;
double minX,minY;
double factorX1,factorY1,factorX2,factorY2;
double array_length;
ofstream * outFile;
int reading_counter;
int reading_counter2;
std::vector<int> mindData;


void ResultsState::onEnter(){
	results = loadTexture("Images/results.pam");

  //Set up output
  outFile = new ofstream("data",std::ios_base::app);
  reading_counter = 0;

	//Read whatever is in the file right now, the rest are obtained from the reading below
	ifstream f("data");
  double x,y;  	

   while(f>>x && f>>y){
    mindData.push_back(x);
    mindData.push_back(y);

    reading_counter2 = x;
  }


  
    f.close();
   
   //Get min/max
    for(int i=0;i<mindData.size()-1;i+=2){
      if(mindData[i] > maximumX) maximumX = mindData[i];
      if(mindData[i+1] > maximumY) maximumY = mindData[i+1];

      if(mindData[i] < minX) minX = mindData[i];
      if(mindData[i+1] < minY) minY = mindData[i+1];
    }  

}

void ResultsState::onExit(){
	outFile->close();
  delete outFile;
}

ResultsState::ResultsState(){
	name = "Results";
}


void ResultsState::update(){
	if(reading_counter >= 30){
    reading_counter = 0;
    int X = reading_counter2;
    int Y = mind->focusValue;
    cout << "Focus\t" << Y << endl;
    (*outFile) << endl;
    (*outFile) << X;
    (*outFile) << " ";
    (*outFile) << Y;
    mindData.push_back(X);
    mindData.push_back(Y);
    reading_counter2++;

    //Get min/max
    for(int i=0;i<mindData.size()-1;i+=2){
      if(mindData[i] > maximumX) maximumX = mindData[i];
      if(mindData[i+1] > maximumY) maximumY = mindData[i+1];

      if(mindData[i] < minX) minX = mindData[i];
      if(mindData[i+1] < minY) minY = mindData[i+1];
    }
    
  }
  reading_counter++;


  
}

void ResultsState::render(){
	double width = 427;
	double height = 147;
	drawTexture(results,  GAME_WIDTH/2-width/2,GAME_HEIGHT/2-height/2, width,height,1.0,0.0,1.0,1.0,1.0); 

   glLineWidth(2);
   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_LINES);

   int axisOffsetX = 50;
   int axisOffsetY = 50;

   int fixY=150;
   int fixX=150;

   glVertex3f(axisOffsetX,fixY,0);
   glVertex3f(axisOffsetX,GAME_HEIGHT-axisOffsetY,0);

    float timeAxisY = GAME_HEIGHT-axisOffsetY;

   glVertex3f(axisOffsetX,timeAxisY,0);
   glVertex3f(GAME_WIDTH-fixX,timeAxisY,0);
   int num_points = (mindData.size()/2);

   for(int i=0;i<(num_points-1) * 2;i+=2){
  
 factorX1= (mindData[i]-minX)/(maximumX-minX);
 factorY1= (mindData[i+1]-minY)/(maximumY-minY);
 factorX2= (mindData[i+2]-minX)/(maximumX-minX);
 factorY2= (mindData[i+3]-minY)/(maximumY-minY);
   //cout<<"maximumX::"<<maximumX<<endl;
   //cout<<"maximumY::"<<maximumY<<endl;

   float X1 = (GAME_WIDTH)* factorX1;
   float Y1 = (GAME_HEIGHT-fixY)* factorY1 * -1 + timeAxisY;

   float X2 = (GAME_WIDTH)* factorX2;
   float Y2 = (GAME_HEIGHT-fixY)* factorY2 * -1 + timeAxisY;

   glVertex3f(X1+axisOffsetX,Y1,0); //cout << "First Point\t (" << X1 << " , " << Y1 << ")" << endl;
   glVertex3f(X2+axisOffsetX,Y2,0); //cout << "Second Point\t (" << X2<< " , " << Y2 << ")" << endl;
   //cout << "===========\t" << i << endl;
	}
	glEnd();
}
void ResultsState::keyboard(unsigned char c, int x, int y){

	if((int)c == 27){//When escape is pressed
		//Back to the menu
		 msg = "trans_Menu";
         sent = 1;
	}
}

void ResultsState::mouse(int button, int state, int x, int y){

}

void ResultsState::mouse_motion(int x,int y){

}
