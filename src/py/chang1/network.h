#ifndef _NETWORK_
#define _NETWORK_

void multicast(const char *msg);
void receiveMulticast( const char *msg );  // user supplied
bool listen(char *buffer, int bufMaxLen);
void initNetwork(int port);

#endif
