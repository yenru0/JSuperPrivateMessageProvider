#include <iostream>

#include "socket.h"


int main() {
    int state, pid;
    struct sigaction act;

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

    ServerSocket serv_sock;

    if(!(serv_sock.bindSocket()))
}