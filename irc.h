#ifndef IRC_H
#define IRC_H

int irc_login(int socket, char* nickname);
int irc_join_channel(int socket, char* channel);
int irc_send_privmsg(int socket, char* channel, char* msg);

#endif
