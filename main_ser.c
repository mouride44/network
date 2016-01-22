#include<stdio.h>
#include<stdlib.h>
/*#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>*/
#include "client2.c"
#include "serveur.c"
#include<unistd.h>
#include<errno.h>
#define  LG_MESSAGE 256

int main(int argc ,char *argv[]){
    struct sockaddr_in client[10];
    int ab,n,c,i;
    int actuel=0;
    char messageRecu[LG_MESSAGE];
    char messageEnvoi[LG_MESSAGE];
    socklen_t longueurAdresse;
    struct sockaddr_in local_s;

   socklen_t longueurAdress_s;
   //struct sockaddr_in distant_s;
   n=atoi(argv[1]);
   ab= cre_socket_ser( );
  sprintf(messageEnvoi, "demande d'enregistrement!\n");
  bind_socket(local_s, longueurAdresse,ab);
 // bind_socket_re(local_s,longueurAdress_s,ab,n);
  send_msg(local_s,ab,argv[1],argv[2],messageEnvoi);
 //printf("les valears ! (%d)\n", n);
  //ab= cre_socket_ser( );
  printf("socket (%d)\n",ab);
  //bind_socket_re(local_s,longueurAdress_s,ab,n);
  struct sockaddr_in distant_s={0};
  Traitement(distant_s,ab,  messageRecu, longueurAdresse ,actuel);  

return 0;

}

