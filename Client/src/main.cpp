#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "socket.h"

int main(void) {
    Socket s = Socket();

    std::cout << s.a << std::endl;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr));

    connect(sockfd, (struct sockaddr *) &(serverAddress), sizeof(serverAddress));

    std::string message = "Hello Server!";

    send(sockfd, message.c_str(), message.size(), 0);
    std::cout << "Sent Message: " << message << std::endl;

    close(sockfd);

    return 0;

}