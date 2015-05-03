#include <string>
#include <iostream>
using namespace std;

#include "SplashState.h"
#include "../texture.h"

int logo;//Texture ID
float alpha = 0;
int dir = 1;

void SplashState::onEnter(){
	logo = loadTexture("Images/Logo.pam");
}

void SplashState::onExit(){
	//TODO: Destroy logo?
	
}

SplashState::SplashState(){
	name = "Splash";
}

//Empty states
void SplashState::update(){

	alpha += dir * 0.01;
	if(alpha >= 1 && dir > 0) dir = -1;
	if(alpha <= 0 && dir < 0){
		msg = "trans_Menu";
		sent = 1;
	}
}

void SplashState::render(){
	double width = 700;
	double height = 700;
	drawTexture(logo,  1024/2-width/2,720/2-height/2, width,height,alpha);
}

void SplashState::keyboard(unsigned char c, int x, int y){

}

void SplashState::mouse(int button, int state, int x, int y){

}

void SplashState::mouse_motion(int x,int y){

}
