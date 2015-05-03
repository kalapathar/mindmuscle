OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm libBox2D.a
STATE_PATH = States/
STATES = $(STATE_PATH)MenuState.o $(STATE_PATH)GameState.o $(STATE_PATH)SplashState.o $(STATE_PATH)AboutState.o $(STATE_PATH)ResultsState.o $(STATE_PATH)ReadingState.o
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


#All the states
$(STATE_PATH)MenuState.o: $(STATE_PATH)MenuState.h $(STATE_PATH)MenuState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)MenuState.o -c $(STATE_PATH)MenuState.cpp

$(STATE_PATH)GameState.o: $(STATE_PATH)GameState.h $(STATE_PATH)GameState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)GameState.o -c $(STATE_PATH)GameState.cpp

$(STATE_PATH)SplashState.o: $(STATE_PATH)SplashState.h $(STATE_PATH)SplashState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)SplashState.o -c $(STATE_PATH)SplashState.cpp

$(STATE_PATH)AboutState.o: $(STATE_PATH)AboutState.h $(STATE_PATH)AboutState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)AboutState.o -c $(STATE_PATH)AboutState.cpp

$(STATE_PATH)ReadingState.o: $(STATE_PATH)ReadingState.h $(STATE_PATH)ReadingState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)ReadingState.o -c $(STATE_PATH)ReadingState.cpp

$(STATE_PATH)ResultsState.o: $(STATE_PATH)ResultsState.h $(STATE_PATH)ResultsState.cpp
	g++ -g -Wall -std=c++11 -o $(STATE_PATH)ResultsState.o -c $(STATE_PATH)ResultsState.cpp

texture.o: texture.cpp texture.h
	g++ -g -Wall -std=c++11 -c texture.cpp
	
clean:
	rm -f *.o MindMuscle