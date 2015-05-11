OPTS = -Wall -g -std=c++11

test-peer: test-peer.o network.o
	g++ $(OPTS) -o test-peer network.o test-peer.o

test-peer.o: test-peer.cpp
	g++ $(OPTS) -c test-peer.cpp

network.o: network.cpp network.h
	g++ $(OPTS) -c network.cpp


UDPEchoClient: UDPEchoClient.o PracticalSocket.o
	g++ $(OPTS) -o UDPEchoClient PracticalSocket.o UDPEchoClient.o

UDPEchoClient.o: UDPEchoClient.cpp
	g++ $(OPTS) -c UDPEchoClient.cpp

PracticalSocket.o: PracticalSocket.cpp PracticalSocket.h
	g++ $(OPTS) -c PracticalSocket.cpp


UDPEchoServer: UDPEchoServer.o PracticalSocket.o
	g++ $(OPTS) -o UDPEchoServer PracticalSocket.o UDPEchoServer.o

UDPEchoServer.o: UDPEchoServer.cpp
	g++ $(OPTS) -c UDPEchoServer.cpp
