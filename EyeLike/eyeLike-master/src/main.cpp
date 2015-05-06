#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>


#include "findEyeCenter.h"
#include "findEyeCorner.h"


/** Constants **/

const bool kPlotVectorField = false;

// Size constants
const int kEyePercentTop = 25;
const int kEyePercentSide = 13;
const int kEyePercentHeight = 30;
const int kEyePercentWidth = 35;
const double k=100;
const double radius=25;
double* rightgaze=new double[3];
double* leftgaze=new double[3];
double* rightlook=new double[2];
double* leftlook=new double[2];
double* screenPos=new double[2];

// Preprocessing
const bool kSmoothFaceImage = false;
const float kSmoothFaceFactor = 0.005;

// Algorithm Parameters
const int kFastEyeWidth = 50;
const int kWeightBlurSize = 5;
const bool kEnableWeight = true;
const float kWeightDivisor = 1.0;
const double kGradientThreshold = 50.0;

// Postprocessing
const bool kEnablePostProcess = true;
const float kPostProcessThreshold = 0.97;

// Eye Corner
const bool kEnableEyeCorner = false;
/** Function Headers */
void detectAndDisplay( cv::Mat frame );

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
cv::String face_cascade_name = "../haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;
// std::string main_window_name = "Capture - Face detection";
// std::string face_window_name = "Capture - Face";
cv::RNG rng(12345);
cv::Mat debugImage;
cv::Mat skinCrCbHist = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);

/**
 * @function main
 */

int counter = 0;

int main( int argc, const char** argv ) {
  CvCapture* capture;
  cv::Mat frame;

  // Load the cascades
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade, please change face_cascade_name in source code.\n"); return -1; };

  // cv::namedWindow(main_window_name,CV_WINDOW_NORMAL);
  // cv::moveWindow(main_window_name, 400, 100);
  // cv::namedWindow(face_window_name,CV_WINDOW_NORMAL);
  // cv::moveWindow(face_window_name, 10, 100);
  // cv::namedWindow("Right Eye",CV_WINDOW_NORMAL);
  // cv::moveWindow("Right Eye", 10, 600);
  // cv::namedWindow("Left Eye",CV_WINDOW_NORMAL);
  // cv::moveWindow("Left Eye", 10, 800);
 

  createCornerKernels();
  ellipse(skinCrCbHist, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
          43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);

   // Read the video stream
  capture = cvCaptureFromCAM( -1 );
  if( capture ) {
    while( true ) {
      frame = cvQueryFrame( capture );
      // mirror it
      cv::flip(frame, frame, 1);
      frame.copyTo(debugImage);

      // Apply the classifier to the frame
      if( !frame.empty() ) {
        counter ++;
        if(counter > 20){
          counter = 0;
          detectAndDisplay( frame );
        }
      }
      else {
        printf(" --(!) No captured frame -- Break!");
        break;
      }

      // imshow(main_window_name,debugImage);

      // int c = cv::waitKey(10);
      // if( (char)c == 'c' ) { break; }
      // if( (char)c == 'f' ) {
      //   imwrite("frame.png",frame);
      // }

    }
  }

  releaseCornerKernels();

  return 0;
}

void findEyes(cv::Mat frame_gray, cv::Rect face) {
  cv::Mat faceROI = frame_gray(face);
  cv::Mat debugFace = faceROI;
  double d=k/(face.width*face.height);

  if (kSmoothFaceImage) {
    double sigma = kSmoothFaceFactor * face.width;
    GaussianBlur( faceROI, faceROI, cv::Size( 0, 0 ), sigma);
  }
  //-- Find eye regions and draw them
  int eye_region_width = face.width * (kEyePercentWidth/100.0);
  int eye_region_height = face.width * (kEyePercentHeight/100.0);
  int eye_region_top = face.height * (kEyePercentTop/100.0);
  cv::Rect leftEyeRegion(face.width*(kEyePercentSide/100.0),
                         eye_region_top,eye_region_width,eye_region_height);
  cv::Rect rightEyeRegion(face.width - eye_region_width - face.width*(kEyePercentSide/100.0),
                          eye_region_top,eye_region_width,eye_region_height);

  //-- Find Eye Centers
  cv::Point leftPupil = findEyeCenter(faceROI,leftEyeRegion);
  cv::Point rightPupil = findEyeCenter(faceROI,rightEyeRegion);
  
  cv::Point3f LeftPupil,RightPupil;
  cv::Point3f LeftOrigin,RightOrigin;

  LeftPupil.x=leftPupil.x;
  LeftPupil.y=leftPupil.y;

  RightPupil.x=rightPupil.x;
  RightPupil.y=rightPupil.y;
  
  double pupilDist=sqrt(((RightPupil.x-LeftPupil.x)*(RightPupil.x-LeftPupil.x))+((RightPupil.y-LeftPupil.y)*(RightPupil.y-LeftPupil.y)));

 

  // get corner regions
  cv::Rect leftRightCornerRegion(leftEyeRegion);
  leftRightCornerRegion.width -= leftPupil.x;
  leftRightCornerRegion.x += leftPupil.x;
  leftRightCornerRegion.height /= 2;
  leftRightCornerRegion.y += leftRightCornerRegion.height / 2;
  cv::Rect leftLeftCornerRegion(leftEyeRegion);
  leftLeftCornerRegion.width = leftPupil.x;
  leftLeftCornerRegion.height /= 2;
  leftLeftCornerRegion.y += leftLeftCornerRegion.height / 2;
  cv::Rect rightLeftCornerRegion(rightEyeRegion);
  rightLeftCornerRegion.width = rightPupil.x;
  rightLeftCornerRegion.height /= 2;
  rightLeftCornerRegion.y += rightLeftCornerRegion.height / 2;
  cv::Rect rightRightCornerRegion(rightEyeRegion);
  rightRightCornerRegion.width -= rightPupil.x;
  rightRightCornerRegion.x += rightPupil.x;
  rightRightCornerRegion.height /= 2;
  rightRightCornerRegion.y += rightRightCornerRegion.height / 2;
  rectangle(debugFace,leftRightCornerRegion,200);
  rectangle(debugFace,leftLeftCornerRegion,200);
  rectangle(debugFace,rightLeftCornerRegion,200);
  rectangle(debugFace,rightRightCornerRegion,200);
  // change eye centers to face coordinates
  rightPupil.x += rightEyeRegion.x;
  rightPupil.y += rightEyeRegion.y;
  leftPupil.x += leftEyeRegion.x;
  leftPupil.y += leftEyeRegion.y;

  LeftOrigin.x=leftEyeRegion.x+(leftEyeRegion.width/2);
  LeftOrigin.y=leftEyeRegion.y+(leftEyeRegion.height/2);
  LeftOrigin.z=(d+radius)*(LeftPupil.x-leftEyeRegion.x)/(pupilDist);

  LeftPupil.z=d+radius-sqrt(pow(radius,2)-pow(LeftPupil.x-LeftOrigin.x,2)-pow(LeftPupil.y-LeftOrigin.y,2))+LeftOrigin.z;

  RightOrigin.x=rightEyeRegion.x+(leftEyeRegion.width/2);
  RightOrigin.y=rightEyeRegion.y+(rightEyeRegion.height/2);
  RightOrigin.z=(d+radius)*(RightPupil.x-rightEyeRegion.x)/(pupilDist);

  RightPupil.z=d+radius-sqrt(pow(radius,2)-pow(RightPupil.x-RightOrigin.x,2)-pow(RightPupil.y-RightOrigin.y,2))+RightOrigin.z;

  rightgaze[0]=RightPupil.x-RightOrigin.x;
  rightgaze[1]=RightPupil.y-RightOrigin.y;
  rightgaze[2]=RightPupil.z-RightOrigin.z;

  leftgaze[0]=LeftPupil.x-LeftOrigin.x;
  leftgaze[1]=LeftPupil.y-LeftOrigin.y;
  leftgaze[2]=LeftPupil.z-LeftOrigin.z;

  double RightU=-(RightOrigin.z/rightgaze[2]);
  double LeftU=-(LeftOrigin.z/leftgaze[2]);

  rightlook[0]=RightOrigin.x+RightU*rightgaze[0];
  rightlook[1]=RightOrigin.y+RightU*rightgaze[1];


  leftlook[0]=LeftOrigin.x+LeftU*leftgaze[0];
  leftlook[1]=LeftOrigin.y+LeftU*leftgaze[1];

  screenPos[0]=(rightlook[0]+leftlook[0])/2;
  screenPos[1]=(rightlook[1]+leftlook[1])/2;

  // draw eye centers
  circle(debugFace, rightPupil, 3, 1234);
  circle(debugFace, leftPupil, 3, 1234);

  //-- Find Eye Corners
  if (kEnableEyeCorner) {
    cv::Point2f leftRightCorner = findEyeCorner(faceROI(leftRightCornerRegion), true, false);
    leftRightCorner.x += leftRightCornerRegion.x;
    leftRightCorner.y += leftRightCornerRegion.y;
    cv::Point2f leftLeftCorner = findEyeCorner(faceROI(leftLeftCornerRegion), true, true);
    leftLeftCorner.x += leftLeftCornerRegion.x;
    leftLeftCorner.y += leftLeftCornerRegion.y;
    cv::Point2f rightLeftCorner = findEyeCorner(faceROI(rightLeftCornerRegion), false, true);
    rightLeftCorner.x += rightLeftCornerRegion.x;
    rightLeftCorner.y += rightLeftCornerRegion.y;
    cv::Point2f rightRightCorner = findEyeCorner(faceROI(rightRightCornerRegion), false, false);
    rightRightCorner.x += rightRightCornerRegion.x;
    rightRightCorner.y += rightRightCornerRegion.y;
    circle(faceROI, leftRightCorner, 3, 200);
    circle(faceROI, leftLeftCorner, 3, 200);
    circle(faceROI, rightLeftCorner, 3, 200);
    circle(faceROI, rightRightCorner, 3, 200);
  }

  // imshow(face_window_name, faceROI);
//  cv::Rect roi( cv::Point( 0, 0 ), faceROI.size());
//  cv::Mat destinationROI = debugImage( roi );
//  faceROI.copyTo( destinationROI );
    std::cout<<screenPos[0]<<" "<<screenPos[1];
 
}


cv::Mat findSkin (cv::Mat &frame) {
  cv::Mat input;
  cv::Mat output = cv::Mat(frame.rows,frame.cols, CV_8U);

  cvtColor(frame, input, CV_BGR2YCrCb);

  for (int y = 0; y < input.rows; ++y) {
    const cv::Vec3b *Mr = input.ptr<cv::Vec3b>(y);
//    uchar *Or = output.ptr<uchar>(y);
    cv::Vec3b *Or = frame.ptr<cv::Vec3b>(y);
    for (int x = 0; x < input.cols; ++x) {
      cv::Vec3b ycrcb = Mr[x];
//      Or[x] = (skinCrCbHist.at<uchar>(ycrcb[1], ycrcb[2]) > 0) ? 255 : 0;
      if(skinCrCbHist.at<uchar>(ycrcb[1], ycrcb[2]) == 0) {
        Or[x] = cv::Vec3b(0,0,0);
      }
    }
  }
  return output;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( cv::Mat frame ) {
  std::vector<cv::Rect> faces;
  // cv::Mat frame_gray;

  std::vector<cv::Mat> rgbChannels(3);
  cv::split(frame, rgbChannels);
  cv::Mat frame_gray = rgbChannels[2];

  //cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //equalizeHist( frame_gray, frame_gray );
  //cv::pow(frame_gray, CV_64F, frame_gray);
  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150) );
 findSkin(debugImage);

  for( int i = 0; i < faces.size(); i++ )
  {
    rectangle(debugImage, faces[i], 1234);
  }
  //-- Show what you got
  if (faces.size() > 0) {
    findEyes(frame_gray, faces[0]);
  }
}
