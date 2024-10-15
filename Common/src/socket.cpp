#include "socket.h"

void read_childproc(int sig) {
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id : %d \n", pid);
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

bool ServerSocket::bindSocket(char *port) {
    struct sockaddr_in addr;
    bzero((char *) &addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(port));

    int flag = bind(fd, (struct sockaddr *) &addr, sizeof(addr));
    if (flag == -1)
        return false;
    else
        return true;
}

bool ServerSocket::listenSocket(int num) {
    int flag = listen(fd, num);
    if (flag == -1)
        return false;
    else
        return true;
}

bool ServerSocket::acceptSocket() {
    struct sockaddr_in addr;
    socklen_t addr_size;
    addr_size = sizeof(addr);
    clnt_sock = accept(fd, (struct sockaddr *) &addr, &addr_size);

    if (clnt_sock == -1)
        return false;
    else
        return true;
}

bool ServerSocket::sendFile(char *filename) {
    char buf[BUFSIZE];
    FILE *file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);// 파일 끝으로 이동
    size_t fsize = ftell(file);// 파일 크기 계산
    fseek(file, 0, SEEK_SET);
    int nsize = 0;

    while (nsize != fsize) {
        int fpsize = fread(buf, 1, BUFSIZE, file);
        nsize += fpsize;
        if (send(clnt_sock, buf, fpsize, 0) == -1) {
            return false;
        }
    }
    fclose(file);
    return true;
}