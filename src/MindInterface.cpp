#include <string>
#include <iostream>
#include <cstdlib>           // For atoi()

using namespace std;

#include <string.h>
#include <sys/socket.h>
#include "MindInterface.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException

void cpy(const char * src,char * dest){
	int index = 0;
  
  while(*src != '\0'){
    dest[index] = *src;
    index++;
    src++;
  }
  dest[index] = '\0';
}

bool goodEnoughCompare(char * str,const char * str2,int max=99999){
	//Compares two strings until it hits a nullbyte in one of them
	int index = 0;
	while(str[index] != '\0' && str2[index] != '\0' && index < max){
		if(str[index] != str2[index]) return false;
		index ++;
	}
	return true;
}

void MindInterface::zeroBombBuffer(){
	//Fills the buffer with nullbytes
	for(int i=0;i<ECHOMAX;i++){
		echoBuffer[i] = '\0';
	}
}

MindInterface::MindInterface(){
	ECHOMAX = 255;//Max buffer size
	sock = new UDPSocket(echoServPort);//initialze socket

	struct timeval tv;
	tv.tv_sec = 0;  
	tv.tv_usec = 1; 
	int sockDesc = sock->getSockDec();//Get the socket ID
	setsockopt(sockDesc, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));//Set the timeout

	counter = 0;//Initialize counter
    initPython = 0;
 
 	msgID = 0;//idle is the default message


 	focusValue = 0;
 	// // //Some states
 	connected = false;

 	messages = new char * [6];
 	messages[0] = new char[strlen("idle")+1]; cpy("idle",messages[0]);
 	messages[1] =  new char[strlen("init_connect")+1]; cpy("init_connect",messages[1]);
 	messages[2] =  new char[strlen("attempt_connect")+1]; cpy("attempt_connect",messages[2]);
 	messages[3] =  new char[strlen("get_status")+1]; cpy("get_status",messages[3]);
 	messages[4] =  new char[strlen("get_focus")+1]; cpy("get_focus",messages[4]);
 	messages[5] =  new char[strlen("disconnect")+1]; cpy("disconnect",messages[5]);
 }

MindInterface::~MindInterface(){
	//Send a final goodbye, to close the connection with the headset automatically
	//This final reply has to be blocking
	//Cannot let the game close without disconnecting properly
	struct timeval tv;
	tv.tv_sec = 0;  
	tv.tv_usec = 0;  
	int sockDesc = sock->getSockDec();//Get the socket ID
	setsockopt(sockDesc, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));//Set the timeout

	sock->recvFrom(echoBuffer, ECHOMAX, sourceAddress,
                                        sourcePort);//Recieve whatever the server is sending, we don't care

	msgID = 5;//Go kill yourself! (The server, not you, beautiful grader!)
	sock->sendTo(messages[msgID], strlen(messages[msgID]), sourceAddress, sourcePort);
	cout << "C++ dead" << endl;
	
	for(int i=0;i<6;i++){
		delete messages[i];
	}
	delete [] messages;
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
	//Check every few frames if a message was received 
	counter ++;
	if(counter > 30){

		//If not connected yet, keep trying to connect
		// if(!connected){
		// 	cout << current_status << endl;
		// 	cout << checkStatus << endl;
		// 	if(goodEnoughCompare(current_status,"connected") ) connected = true;
		// 	if(!initialConnected){
				
		// 		sendMSG("init_connect");
		// 	} else {
		// 		if(checkStatus == 0) {
		// 			sendMSG("attempt_connect");//Sent attempt connect once
		// 			checkStatus = 1;
		// 		}
		// 		else if(checkStatus == 1){
		// 			sendMSG("get_status");//And get the status once
		// 			checkStatus = 0;
		// 		}

		// 	}
		// }
		// //If connected, keep reading focus levels and blinks
		// if(connected){
		// 	//Keep polling for the focus
		// 	sendMSG("get_focus");
		// 	cout << "focus\t" << focusValue << endl;
		// }

		counter = 0;
		try {
			recvMsgSize = sock->recvFrom(echoBuffer, ECHOMAX, sourceAddress,
	                                        sourcePort);
			
			//recieved message
			const char * idleMSG = "idle";
			const char * initMSG = "initialized_connection"; 	
			const char * conMSG = "attempted_connect"; 	
			const char * disconMSG = "disconnecting"; 
			const char * blinkMSG = "blink";

			//Respond to the server
			sock->sendTo(messages[msgID], strlen(messages[msgID]), sourceAddress, sourcePort);

				
			if(goodEnoughCompare(echoBuffer,idleMSG)){
				cout << "Idle" << endl;
				//Just echo back idle, keep the server running
	    		
	    		msgID = 0;
			}
			if(goodEnoughCompare(echoBuffer,initMSG)){
				cout << "Initialized connection!" << endl;
				initialConnected = true;
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
				int cutSize = strlen("focus");
				char * focusChar = new char[recvMsgSize-cutSize+1];
				//Copy
				int index = 0;
				for(int i=cutSize;i<recvMsgSize;i++){
					focusChar[index++] = echoBuffer[i];
				}
				focusChar[index++] = '\0';//End with a nullbyte

				int focusNum = atoi(focusChar);
				focusValue = focusNum;

				//Clean up, no memory leaks!
				delete [] focusChar;
				//Go back to being idle
				msgID = 0;
			}

			if(goodEnoughCompare(echoBuffer,"status",6)){
				//The focus number is sent with the prefix "focus"
				//So we cut that off
				int cutSize = strlen("status");
				char * statusChar = new char[recvMsgSize-cutSize+1];
				//Copy
				int index = 0;
				for(int i=cutSize;i<recvMsgSize;i++){
					statusChar[index++] = echoBuffer[i];
				}
				statusChar[index++] = '\0';//End with a nullbyte

				strcpy(current_status,statusChar);

				//Go back to being idle
				msgID = 0;

				//Clean up, no memory leaks!
				delete [] statusChar;
			}

			
			zeroBombBuffer();
			
			

    	} catch (SocketException &e) {}
        if(initPython == 0){
        	initPython = 1;
        	system("python2 py/parsepackets.py &");//Start the python script that does all the magic
        }
	}	
}
