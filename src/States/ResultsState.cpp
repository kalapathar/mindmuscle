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

int results;
double data[100];
double maximumX, maximumY;
double factorX1,factorY1,factorX2,factorY2;
double array_length;

void ResultsState::onEnter(){
	results = loadTexture("Images/results.pam");

	//Read file
	ifstream f("data");
  double x,y;
  int i=0;
  	
  array_length = 0;

   while(f>>x && f>>y){
    data[i]= y;
    data[i+1]= x;
    cout << x << "\t" << y << "\t" << i << "\t" << endl;
    i=i+2;
    array_length +=2;
  }
  
    f.close();
     
     //auto array_length = end(data) - begin(data);
     //cout<<array_length;
     
    //array_length =(sizeof(data)/sizeof(double));

    for(int i=0;i<array_length;i+=2){
      if (data[i]>maximumX){
        maximumX=data[i];
      }
      if (i+1 <= array_length-1 && data[i+1]>maximumY){
        maximumY=data[i+1];
      }

    }

}

void ResultsState::onExit(){
	
}

ResultsState::ResultsState(){
	name = "Results";
}


void ResultsState::update(){
	

}

void ResultsState::render(){
	double width = 427;
	double height = 147;
	drawTexture(results,  GAME_WIDTH/2-width/2,GAME_HEIGHT/2-height/2, width,height);

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
   int num_points = (array_length/2);

   for(int i=0;i<(num_points-1) * 2;i+=2){


  // cout<<data[i]<<endl;

  // cout<<data[i+1]<<endl;
  // cout<<data[i+2]<<endl;
  // cout<<data[i+3]<<endl;
  
 factorX1=data[i]/maximumX;
 factorY1=data[i+1]/maximumY;
 factorX2=data[i+2]/maximumX;
 factorY2=data[i+3]/maximumY;
   cout<<"maximumX::"<<maximumX<<endl;
   cout<<"maximumY::"<<maximumY<<endl;

   float X1 = (GAME_WIDTH)* factorX1;
   float Y1 = (GAME_HEIGHT-fixY)* factorY1 * -1 + timeAxisY;

   float X2 = (GAME_WIDTH)* factorX2;
   float Y2 = (GAME_HEIGHT-fixY)* factorY2 * -1 + timeAxisY;

   glVertex3f(X1+axisOffsetX,Y1,0); cout << "First Point\t (" << X1 << " , " << Y1 << ")" << endl;
   glVertex3f(X2+axisOffsetX,Y2,0); cout << "Second Point\t (" << X2<< " , " << Y2 << ")" << endl;
   cout << "===========\t" << i << endl;
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
