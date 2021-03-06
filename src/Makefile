OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm libBox2D.a -rdynamic /usr/lib64/libopencv_videostab.so.2.4.7 /usr/lib64/libopencv_video.so.2.4.7 /usr/lib64/libopencv_ts.so.2.4.7 /usr/lib64/libopencv_superres.so.2.4.7 /usr/lib64/libopencv_stitching.so.2.4.7 /usr/lib64/libopencv_photo.so.2.4.7 /usr/lib64/libopencv_ocl.so.2.4.7 /usr/lib64/libopencv_objdetect.so.2.4.7 /usr/lib64/libopencv_ml.so.2.4.7 /usr/lib64/libopencv_legacy.so.2.4.7 /usr/lib64/libopencv_imgproc.so.2.4.7 /usr/lib64/libopencv_highgui.so.2.4.7 /usr/lib64/libopencv_flann.so.2.4.7 /usr/lib64/libopencv_features2d.so.2.4.7 /usr/lib64/libopencv_core.so.2.4.7 /usr/lib64/libopencv_contrib.so.2.4.7 /usr/lib64/libopencv_calib3d.so.2.4.7 /usr/lib64/libopencv_video.so.2.4.7 /usr/lib64/libopencv_objdetect.so.2.4.7 /usr/lib64/libopencv_ml.so.2.4.7 /usr/lib64/libopencv_features2d.so.2.4.7 /usr/lib64/libopencv_highgui.so.2.4.7 /usr/lib64/libopencv_imgproc.so.2.4.7 /usr/lib64/libopencv_flann.so.2.4.7 /usr/lib64/libopencv_core.so.2.4.7 

STATE_PATH = States/
STATES = $(STATE_PATH)LevelOne.o $(STATE_PATH)MenuState.o $(STATE_PATH)CalibrateState.o $(STATE_PATH)SplashState.o $(STATE_PATH)AboutState.o $(STATE_PATH)ResultsState.o $(STATE_PATH)ReadingState.o
EYELIBS = OpenCV/helpers.o OpenCV/findEyeCorner.o OpenCV/findEyeCenter.o
PYLIBS = 

ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

MindMuscle: MindMuscle.o StateMachine.o $(STATES) texture.o GameObject.o NumberObject.o EyeInterface.o MindInterface.o PracticalSocket.o $(EYELIBS)
	g++ $(OPTS) -o MindMuscle MindMuscle.o StateMachine.o $(STATES) texture.o GameObject.o NumberObject.o EyeInterface.o MindInterface.o PracticalSocket.o $(EYELIBS) $(LIBS) $(PYLIBS)
StateMachine.o: StateMachine.cpp StateMachine.h
	g++ -g -Wall -std=c++11 -c StateMachine.cpp

GameObject.o: GameObject.cpp GameObject.h 
	g++ -g -Wall -std=c++11 -c GameObject.cpp

NumberObject.o: NumberObject.cpp NumberObject.h
	g++ -g -Wall -std=c++11 -c NumberObject.cpp

MindMuscle.o: Globals.h MindMuscle.cpp
	g++ -g -Wall -std=c++11 -c MindMuscle.cpp

#All the states
$(STATE_PATH)LevelOne.o: $(STATE_PATH)LevelOne.h $(STATE_PATH)LevelOne.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)LevelOne.o -c $(STATE_PATH)LevelOne.cpp

$(STATE_PATH)MenuState.o: $(STATE_PATH)MenuState.h $(STATE_PATH)MenuState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)MenuState.o -c $(STATE_PATH)MenuState.cpp

$(STATE_PATH)CalibrateState.o: $(STATE_PATH)CalibrateState.h $(STATE_PATH)CalibrateState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)CalibrateState.o -c $(STATE_PATH)CalibrateState.cpp

$(STATE_PATH)SplashState.o: $(STATE_PATH)SplashState.h $(STATE_PATH)SplashState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)SplashState.o -c $(STATE_PATH)SplashState.cpp

$(STATE_PATH)AboutState.o: $(STATE_PATH)AboutState.h $(STATE_PATH)AboutState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)AboutState.o -c $(STATE_PATH)AboutState.cpp

$(STATE_PATH)ReadingState.o: $(STATE_PATH)ReadingState.h $(STATE_PATH)ReadingState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)ReadingState.o -c $(STATE_PATH)ReadingState.cpp

$(STATE_PATH)ResultsState.o: $(STATE_PATH)ResultsState.h $(STATE_PATH)ResultsState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)ResultsState.o -c $(STATE_PATH)ResultsState.cpp

#Eye detection files
EyeInterface.o: EyeInterface.h EyeInterface.cpp
	g++ $(OPTS) -c EyeInterface.cpp

OpenCV/helpers.o: OpenCV/helpers.h OpenCV/helpers.cpp
	g++ $(OPTS) -o OpenCV/helpers.o -c OpenCV/helpers.cpp

OpenCV/findEyeCorner.o: OpenCV/findEyeCorner.h OpenCV/findEyeCorner.cpp
	g++ $(OPTS) -o OpenCV/findEyeCorner.o -c OpenCV/findEyeCorner.cpp

OpenCV/findEyeCenter.o: OpenCV/findEyeCenter.h OpenCV/findEyeCenter.cpp
	g++ $(OPTS) -o OpenCV/findEyeCenter.o -c OpenCV/findEyeCenter.cpp

#Mind Interface
MindInterface.o: MindInterface.h MindInterface.cpp PracticalSocket.o
	g++ $(OPTS) -c MindInterface.cpp

PracticalSocket.o: PracticalSocket.cpp PracticalSocket.h
	g++ $(OPTS) -c PracticalSocket.cpp

texture.o: texture.cpp texture.h
	g++ -g -Wall -std=c++11 -c texture.cpp
	
clean:
	rm -f *.o MindMuscle
