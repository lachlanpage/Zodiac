#include "irc.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>


int irc_login(int socket, char* nickname) {
    char login_str[] = "NICK %s\r\nUSER KEVIN localhost 0 :Ronnie\r\n";
    char login_two_str[1000];
    sprintf(login_two_str, login_str, nickname);

    if(send(socket, login_two_str, sizeof(login_two_str),0) < 0)
        return 0;
    return 1;
}
