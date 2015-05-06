OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm -rdynamic /usr/lib64/libopencv_videostab.so.2.4.7 /usr/lib64/libopencv_video.so.2.4.7 /usr/lib64/libopencv_ts.so.2.4.7 /usr/lib64/libopencv_superres.so.2.4.7 /usr/lib64/libopencv_stitching.so.2.4.7 /usr/lib64/libopencv_photo.so.2.4.7 /usr/lib64/libopencv_ocl.so.2.4.7 /usr/lib64/libopencv_objdetect.so.2.4.7 /usr/lib64/libopencv_ml.so.2.4.7 /usr/lib64/libopencv_legacy.so.2.4.7 /usr/lib64/libopencv_imgproc.so.2.4.7 /usr/lib64/libopencv_highgui.so.2.4.7 /usr/lib64/libopencv_flann.so.2.4.7 /usr/lib64/libopencv_features2d.so.2.4.7 /usr/lib64/libopencv_core.so.2.4.7 /usr/lib64/libopencv_contrib.so.2.4.7 /usr/lib64/libopencv_calib3d.so.2.4.7 /usr/lib64/libopencv_video.so.2.4.7 /usr/lib64/libopencv_objdetect.so.2.4.7 /usr/lib64/libopencv_ml.so.2.4.7 /usr/lib64/libopencv_features2d.so.2.4.7 /usr/lib64/libopencv_highgui.so.2.4.7 /usr/lib64/libopencv_imgproc.so.2.4.7 /usr/lib64/libopencv_flann.so.2.4.7 /usr/lib64/libopencv_core.so.2.4.7 

main: main.o helpers.o findEyeCorner.o findEyeCenter.o
	g++ $(OPTS) -o main main.o helpers.o findEyeCorner.o findEyeCenter.o $(LIBS)

main.o: main.cpp
	g++ $(OPTS) -c main.cpp

helpers.o: helpers.h helpers.cpp
	g++ $(OPTS) -c helpers.cpp

findEyeCorner.o: findEyeCorner.h findEyeCorner.cpp
	g++ $(OPTS) -c findEyeCorner.cpp

findEyeCenter.o: findEyeCenter.h findEyeCenter.cpp
	g++ $(OPTS) -c findEyeCenter.cpp

