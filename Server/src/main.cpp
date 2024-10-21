#include <iostream>
#include <string>
#include "socket.h"

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

    ServerSocket serv_sock;

    if (!(serv_sock.bindSocket(port))) {
        error_handling("bind error");
        return -1;
    }
    if (!(serv_sock.listenSocket(5))) {
        error_handling((char const *const) "listen error");
        return -1;
    }

    bool is_conn = false;

    while (true) {
        if (is_conn) {
            if (serv_sock.recvMsg()) {
                std::string rmsg = serv_sock.getBufferedMsg();
                if (rmsg == ":quit") {
                    cout << "break;" << endl;
                    break;
                }
                cout << "received msg: " << rmsg << endl;
            } else {
                serv_sock.closeAcceptSocket();
                is_conn = false;
                cout << "close AS conn false" << endl;

            }
        } else {
            if (!(serv_sock.acceptSocket())) { continue; }
            else { cout << "new client connected" << endl; }

            is_conn = true;
            cout << "conn true" << endl;
            /*
            if (pid ==   -1) {
                serv_sock.closeAcceptSocket();
                is_conn = false;
                cout << "close AS" << endl;
                continue;
            } else if (pid == 0) {
                serv_sock.closeListenSocket();
                is_conn = true;
                cout << "close LS" << endl;
                continue;
            }
             */
        }

    }
    serv_sock.closeListenSocket();
    cout << "UNEXPECTED" << endl;
    return 1;
}