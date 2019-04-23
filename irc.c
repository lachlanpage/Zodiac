#include "irc.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <string.h>
#include <unistd.h>


int irc_login(int socket, char* nickname) {
    char login_str[] = "NICK %s\r\nUSER KEVIN localhost 0 :Ronnie\r\n";
    char login_two_str[1000];
    sprintf(login_two_str, login_str, nickname);

    if(send(socket, login_two_str, sizeof(login_two_str),0) < 0)
        return 0;
    return 1;
}

int irc_join_channel(int socket, char* channel) {
    char join_str[] = "JOIN %s\r\n";
    char join_two_str[1000];
    sprintf(join_two_str, join_str, channel);

    if(send(socket, join_two_str, sizeof(join_two_str),0) < 0)
        return 0;
    return 1;
}

int irc_send_privmsg(int socket, char* channel, char* msg)
{
    char privmsg[512];
    sleep(3);
    memset(privmsg, 0, sizeof(privmsg));
    sprintf(privmsg, "PRIVMSG %s :%s \r\n", channel, msg);
    int result = send(socket, privmsg, strlen(privmsg), 0);
    return result;
}
