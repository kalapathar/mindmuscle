OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm libBox2D.a
STATES = MenuState.o GameState.o SplashState.o
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

MindMuscle: MindMuscle.o StateMachine.o $(STATES) texture.o
	g++ $(OPTS) -o MindMuscle MindMuscle.o StateMachine.o $(STATES) texture.o $(LIBS)

StateMachine.o: StateMachine.cpp StateMachine.h
	g++ -g -Wall -std=c++11 -c StateMachine.cpp

MenuState.o: MenuState.h MenuState.cpp
	g++ -g -Wall -std=c++11 -c MenuState.cpp

GameState.o: GameState.h GameState.cpp
	g++ -g -Wall -std=c++11 -c GameState.cpp

SplashState.o: SplashState.h SplashState.cpp
	g++ -g -Wall -std=c++11 -c SplashState.cpp

texture.o: texture.cpp texture.h
	g++ -g -Wall -std=c++11 -c texture.cpp
	
clean:
	rm -f *.o MindMuscle