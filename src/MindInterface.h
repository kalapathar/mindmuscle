#ifndef _MindInterface_
#define _MindInterface_

#include <string>
#include "Globals.h"
#include "PracticalSocket.h" // For UDPSocket and SocketException

/* 
This class handles everything needed to 
create a way to communicate with the 
python script that reads the mind data

*/

class MindInterface {
private:
	 int ECHOMAX;
	 const unsigned short echoServPort = 1336;//Port number
	 UDPSocket * sock;
	 char echoBuffer[255];         // Buffer for echo string
     int recvMsgSize;                  // Size of received message
     string sourceAddress;             // Address of datagram source
     unsigned short sourcePort;        // Port of datagram source

     int counter ;
     int initPython;
public:
	MindInterface();
	~MindInterface();
	void update();
	void disconnect();
};

#endif // _MindInterface_