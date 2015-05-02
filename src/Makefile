OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm libBox2D.a
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

MindMuscle: MindMuscle.o StateMachine.o MenuState.o GameState.o
	g++ $(OPTS) -o MindMuscle MindMuscle.o StateMachine.o MenuState.o GameState.o $(LIBS)

StateMachine.o: StateMachine.cpp StateMachine.h
	g++ -g -Wall -std=c++11 -c StateMachine.cpp

MenuState.o: MenuState.h MenuState.cpp
	g++ -g -Wall -std=c++11 -c MenuState.cpp

GameState.o: GameState.h GameState.cpp
	g++ -g -Wall -std=c++11 -c GameState.cpp

clean:
	rm -f *.o MindMuscle