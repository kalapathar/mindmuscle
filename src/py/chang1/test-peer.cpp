#include <iostream>
#include <unistd.h>
#include <fstream>
#include "network.h"

using namespace std;

unsigned int sleepTime = 1 * 1000000; // seconds -> microseconds

void receiveMulticast( const char *msg ) {
    cout << "Got message: " << msg << endl;
}

int main() {
    // Open up a network on a port
    initNetwork(1337);
    
    for (;;) {
        usleep(sleepTime);
        multicast("yomama");
        cout << "yomama" << endl;
    }
}