// by Olaf Hall-Holt, 2009
#include<iostream>
using std::cerr;
using std::endl;
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<errno.h>
#include<assert.h>
#include<string.h>
#include"network.h"

struct sockaddr_in sendAddr, receiveAddr;
int sendID, receiveID;

void initSendSocket(const char *groupAddr, int port) {
    sendID = socket(AF_INET, SOCK_DGRAM, 0);
    assert( sendID >= 0 );
    memset(&sendAddr, 0, sizeof(sendAddr));
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_addr.s_addr = inet_addr(groupAddr);
    sendAddr.sin_port = htons(port);
}

void initReceiveSocket(const char *groupAddr, int port)
{
    receiveID = socket( AF_INET, SOCK_DGRAM, 0);
    assert( receiveID >= 0 );
    int enable=1;
    int ret = setsockopt( receiveID, SOL_SOCKET, SO_REUSEADDR,
                         &enable, sizeof(enable) );
    assert( 0 == ret );
    memset( &receiveAddr, 0, sizeof(receiveAddr) );
    receiveAddr.sin_family = AF_INET;
    receiveAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    receiveAddr.sin_port = htons(port);
    ret = bind( receiveID,
               (struct sockaddr *) &receiveAddr, sizeof(receiveAddr));
    assert( 0 == ret );
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(groupAddr);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    ret = setsockopt( receiveID, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                     &mreq, sizeof(mreq) );
    std::cout << "uhh..." << ret;
    assert( 0 == ret );
    // set to be non-blocking
    int flags = fcntl(receiveID, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(receiveID, F_SETFL, flags);
}

void multicast(const char *msg)
{
    // cerr << "multicast: " << msg << endl;
    int nbytes = sendto( sendID, msg, strlen(msg), 0,
                        (struct sockaddr *) &sendAddr,
                        sizeof(sendAddr) );
    assert( nbytes >= 0 );
}

bool listen(char *buffer, int bufMaxLen)
{
    buffer[0] = 0;
    int addrlen = sizeof(receiveAddr);
    int nbytes = recvfrom( receiveID, buffer, bufMaxLen, 0,
                          (struct sockaddr *) &receiveAddr,
                          (socklen_t *) &addrlen);
    if ( -1 == nbytes ) {
        assert( EAGAIN == errno );  // non-blocking
        // cerr << "listen." << endl;
        return false;
    } else {
        assert( nbytes >= 0 );
        buffer[nbytes]=0;
        receiveMulticast(buffer);
        // cerr << "listen: " << buffer << endl;
        return true;
    }
}

void initNetwork(int port)
{
    const char *multicast = "224.1.2.3";
    initSendSocket(multicast, port);
    initReceiveSocket(multicast, port);
}

#if 0
// basic testing code
#include<sstream>
int main(int argc, char **argv)
{
    initNetwork(25100);
    int counter = 0;
    while ( 1 ) {
        std::stringstream ss;
        ss << argv[1] << counter; ss.flush();
        if ( ++counter % 3 == 0)
            multicast(ss.str().c_str());
        //multicast(argv[1]);
        const int bufMaxLen = 1000;
        char buffer[bufMaxLen];
        listen(buffer, bufMaxLen);
        sleep(1);
    }
}
#endif
