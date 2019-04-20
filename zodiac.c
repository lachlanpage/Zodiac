#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>

#define IP "192.168.8.118"
#define CHANNEL "#net"
#define PORT 6667

int main(int argc, char **argv) {

    int sockfd;
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(IP);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    if(connect(sockfd, (struct sockaddr* )&serv_addr, sizeof(serv_addr)) < 0) {
        perror("socket connection failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
