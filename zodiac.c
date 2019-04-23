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

#include "irc.h"
#include "parser.h"

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

    if(irc_login(sockfd, "MR BIG BOT") < 0) {
        perror("irc login failed");
        exit(EXIT_FAILURE);
    }

    // This is IRC listener
    char buffer[4096];
    while(1) {
        int recv_length = recv(sockfd, &buffer, sizeof(buffer), 0);
        // recv_length take one to stop duplication of \r\n end line
        for( int i = 0; i < recv_length-1; i++ ) {
            switch (buffer[i]) {
                // Reached end of message
                case '\r':
                case '\n':
                {
                    buffer[i] = '\0';
                    if(parse_line(sockfd, &buffer, recv_length) < 0)
                        exit(EXIT_FAILURE);
                    break;
                }
            }
        }
    }

    return 0;
}
