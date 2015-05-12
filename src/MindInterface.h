#ifndef _MindInterface_
#define _MindInterface_

#include <string>

#include "PracticalSocket.h" // For UDPSocket and SocketException

/* 
This class handles everything needed to 
create a way to communicate with the 
python script that reads the mind data


*/

class MindInterface {
private:
      int ECHOMAX;
      const unsigned short echoServPort = 1337;//Port number
      UDPSocket * sock;
      char echoBuffer[255];         // Buffer for echo string
     int recvMsgSize;                  // Size of received message
     string sourceAddress;             // Address of datagram source
     unsigned short sourcePort;        // Port of datagram source

     int counter ;
     int initPython;
    

     int msgID;
     char ** messages;
     void zeroBombBuffer();//Helper functions
public:
      bool connected;
     bool initialConnected;
     int checkStatus;
     char current_status[255];
     int focusValue;

     MindInterface();
     ~MindInterface();
     void update();
     void sendMSG(const char * msg);

};

#endif // _MindInterface_