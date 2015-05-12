#include <string>
#include <iostream>
#include <cstdlib>           // For atoi()

using namespace std;

#include <sys/socket.h>
#include "MindInterface.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException


MindInterface::MindInterface(){
	ECHOMAX = 255;//Max buffer size
	sock = new UDPSocket(echoServPort);//initialze socket

	struct timeval tv;
	tv.tv_sec = 0;  /* 30 Secs Timeout */
	tv.tv_usec = 1;  // Not init'ing this can cause strange errors
	int sockDesc = sock->getSockDec();//Get the socket ID
	setsockopt(sockDesc, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));//Set the timeout

	counter = 0;//Initialize counter
    initPython = 0;
    
    //
}

MindInterface::~MindInterface(){
	if(initPython){
		system("pkill python2");//Kill the process
		cout << "KILLED PROCESS" << endl;
	}
	delete sock;
}

void MindInterface::update(){
	//Check every second if a message was received 
	counter ++;
	if(counter > 60){
		counter = 0;
		try {
			recvMsgSize = sock->recvFrom(echoBuffer, ECHOMAX, sourceAddress,
	                                        sourcePort);
			cout << "Received packet from " << sourceAddress << ":"
	    << sourcePort << endl;
	    sock->sendTo(echoBuffer, recvMsgSize, sourceAddress, sourcePort);
    	} catch (SocketException &e) {}
        if(initPython == 0){
        	initPython = 1;
        	system("python2 py/chang1/test-server.py &");
        }
	}	
}



void MindInterface::disconnect(){
	
}