#ifndef _EyeInterface_
#define _EyeInterface_

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "OpenCV/findEyeCenter.h"
#include "OpenCV/findEyeCorner.h"

/** Constants **/
#include "OpenCV/constants.h"

#include "Globals.h"


/* 
Handles everything needed to do eye tracking.

Sets x and y to be the eye centers
*/

class EyeInterface {
public:
	int x,y;
	CvCapture* capture;
  	cv::Mat frame;
  	int counter;
  	int blinkCount;

	EyeInterface();//initialize
	~EyeInterface();
	void update();
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x,int y);
	void findEyes(cv::Mat frame_gray, cv::Rect face);
	void detectAndDisplay(cv::Mat frame );
};

#endif // _EyeInterface_