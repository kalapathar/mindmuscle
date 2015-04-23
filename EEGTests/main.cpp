#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "ThinkGearStreamParser.h"
using namespace std;

void callBack(unsigned char extendedCodeLevel,unsigned char code, unsigned char numBytes, const unsigned char * value, void *customData){
    cout << "Working!" << " " << numBytes << endl;

}

int read_port(void)
{
	const char * portName = "/dev/ttyS0";
    int fd = open(portName, O_RDONLY | O_NOCTTY);
    if (fd == -1)
    {
        /* Could not open the port. */
        perror("open_port: Unable to open - ");
    }

    char buffer[32];
    int n = read(fd, buffer, sizeof(buffer));
    if (n < 0)
        fputs("read failed!\n", stderr);
    return (fd);
}

int main()
{
    ThinkGearStreamParser * parser = new ThinkGearStreamParser;//Create our parser object
    //Initialize
    void * customData;
    cout << THINKGEAR_initParser( parser, PARSER_TYPE_PACKETS,&callBack,customData ) << endl;

    // while(true){
    //     cout << THINKGEAR_parseByte(parser,0) << endl;
    // }


    cout << read_port() << endl;

    return 0;
}
