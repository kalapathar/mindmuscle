# Set up compiler options and libraries
OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

# Makefile rules

Menu: Menu.o texture.o
	g++ $(OPTS) -o Menu Menu.o texture.o $(LIBS)

Menu.o: Menu.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c Menu.cpp

texture.o: texture.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c texture.cpp