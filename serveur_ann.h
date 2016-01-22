#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include "serveur.h"
#include "client2.h"
# define LG_MESSAGE 256
# define maxclient 3
 void Traitement_cann(struct sockaddr_in distant,int des, char messageRecu[LG_MESSAGE],socklen_t longueurAdresse,int actuel );
