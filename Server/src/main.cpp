#include <iostream>
#include <string>

#include "socket.h"
#include "server.h"

using std::cout;
using std::endl;
using std::string;

int main() {
    int state;
    pid_t pid;
    struct sigaction act;

    uint16_t port = 12345;

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);


    MessageProvider server;


    if (!(server.bindProcess(port))) {
        error_handling("bind error");
        return -1;
    }
    if (!(server.listenProcess(5))) {
        error_handling((char const *const) "listen error");
        return -1;
    }

    server.run();
}