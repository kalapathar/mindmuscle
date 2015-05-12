#include <string>
#include <iostream>
#include <cstdlib>           // For atoi()

using namespace std;

#include <string.h>
#include <sys/socket.h>
#include "MindInterface.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException

bool goodEnoughCompare(char * str,const char * str2,int max=99999){
	//Compares two strings until it hits a nullbyte in one of them
	int index = 0;
	while(str[index] != '\0' && str2[index] != '\0' && index < max){
		if(str[index] != str2[index]) return false;
		index ++;
	}
	return true;
}

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
 
 	msgID = 0;//idle is the default message
 	//Initialize the messages array

 	messages = new char * [6];
 	messages[0] = "idle";
 	messages[1] = "init_connect";
 	messages[2] = "attempt_connect";
 	messages[3] = "get_status";
 	messages[4] = "get_focus";
 	messages[5] = "disconnect";
 }

MindInterface::~MindInterface(){
	if(initPython){
		system("pkill python2");//Kill the process
		cout << "KILLED PROCESS" << endl;
	}
	delete sock;
}

void MindInterface::sendMSG(const char * msg){

	for(int i=0;i<6;i++){
		if(goodEnoughCompare(messages[i],msg)){
			msgID = i;
			break;
		}
	}
}

void MindInterface::update(){
	//Check every second if a message was received 
	counter ++;
	if(counter > 60){
		counter = 0;
		try {
			recvMsgSize = sock->recvFrom(echoBuffer, ECHOMAX, sourceAddress,
	                                        sourcePort);
			
			//recieved message
			const char * idleMSG = "idle";
			const char * initMSG = "initialized_connection"; 	
			const char * conMSG = "attempted_connect"; 	
			const char * disconMSG = "disconnecting"; 

			//Respond to the server
			sock->sendTo(messages[msgID], strlen(messages[msgID]), sourceAddress, sourcePort);

				
			if(goodEnoughCompare(echoBuffer,idleMSG)){
				cout << "Idle" << endl;
				//Just echo back idle, keep the server running
	    		
	    		msgID = 0;
			}
			if(goodEnoughCompare(echoBuffer,initMSG)){
				cout << "Initialized connection!" << endl;
				//Woohoo! Now go back to being idle
	    		msgID = 0;
			}
			if(goodEnoughCompare(echoBuffer,conMSG)){
				cout << "Attempted connection!" << endl;
				//Go back to being idle
	    		msgID = 0;
			}
			if(goodEnoughCompare(echoBuffer,disconMSG)){
				cout << "Disconnecting!" << endl;
				//Succesfully disconnecting! Go back to being idle
	    		msgID = 0;
			}

			//Now for the tricky part
			if(goodEnoughCompare(echoBuffer,"focus",5)){
				//The focus number is sent with the prefix "focus"
				//So we cut that off
				char * focusChar = new char[strlen(echoBuffer)-5];
				//Copy
				int index = 0;
				for(int i=5;i<strlen(echoBuffer);i++){
					focusChar[index++] = echoBuffer[i];
				}

				cout << "Focus\t" << focusChar << endl;
				//Go back to being idle
				msgID = 0;
			}

			if(goodEnoughCompare(echoBuffer,"status",6)){
				//The focus number is sent with the prefix "focus"
				//So we cut that off
				char * statusChar = new char[strlen(echoBuffer)-6];
				//Copy
				int index = 0;
				for(int i=6;i<strlen(echoBuffer);i++){
					statusChar[index++] = echoBuffer[i];
				}

				cout << "Status\t" << statusChar << endl;
				//Go back to being idle
				msgID = 0;
			}

			
			

    	} catch (SocketException &e) {}
        if(initPython == 0){
        	initPython = 1;
        	system("python2 py/parsepackets.py &");
        }
	}	
}



void MindInterface::disconnect(){
	
}