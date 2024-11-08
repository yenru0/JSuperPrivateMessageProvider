#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "socket.h"

int main(void) {

    ClientSocket socket;
    std::string message;

    socket.set_address("127.0.0.1", 12345);

    socket.connectSocket();


    while(true) {
        std::cin >> message;
        if(message == ":quit") {
            break;
        } else {
            socket.sendMsg(message);
        }
    }

    return 0;
}