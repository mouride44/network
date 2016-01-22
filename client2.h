#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
# define LG_MESSAGE 256
int cre_socket();
void bind_socket(struct sockaddr_in pointDeRencontreLocal,socklen_t longueurAdresse,int des);
void send_msg(struct sockaddr_in loc,int desc,const char *ip,const char *port,char messageEnvoi[LG_MESSAGE];);
void recv2(struct sockaddr_in distant,int disk);
