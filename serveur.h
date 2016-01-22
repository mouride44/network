#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
# define LG_MESSAGE 256
# define maxclient 3
int  cre_socket_ser();
int tab_port(int n,int a);
void bind_socket_re(struct sockaddr_in pointDeRencontreLocal,socklen_t longueurAdresse,int des,int port);
void recv_msg(struct sockaddr_in pointDeRencontreDistant,int descripteurSocket, char messageRecu[LG_MESSAGE],socklen_t longueurAdresse;);
void tab_client (struct sockaddr_in pers,int actuel );
void send_all_client(int sock, struct sockaddr_in cli[maxclient],struct sockaddr_in sender,char messageE[LG_MESSAGE],int ac,socklen_t longueurAdresse);
int client_exist(struct sockaddr_in client[maxclient] ,struct sockaddr_in cl,int act);
void affiche_connecte(struct sockaddr_in tabe[maxclient],int nu);
 void Traitement(struct sockaddr_in pointDeRencontreDistant,int descripteurSocket, char messageRecu[LG_MESSAGE],socklen_t longueurAdresse,int actuel);
struct sockaddr_in get_client(struct sockaddr_in cli[maxclient],struct sockaddr_in send,int actuel);
