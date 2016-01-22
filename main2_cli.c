#include<stdio.h>
#include<stdlib.h>
/*#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>*/
#include "client2.c"
int main(int argc ,char *argv[]){
     int i,j;
     int ab,c;
     int ecri;
     struct sockaddr_in local_c;
     socklen_t longueurAdress_c;
     struct sockaddr_in distant_c,distant;
     char messageEnvoi[LG_MESSAGE];
      memset(messageEnvoi, 0x00, LG_MESSAGE*sizeof(char));

     for(j=3;j<argc ;j++){
             sprintf(messageEnvoi+strlen(messageEnvoi), "%s\n",argv[j]);
}   

      c=cre_socket( );
           if(c< 0){
               perror("socket"); // Affiche le message d’erreur
               exit(-1); // On sort en indiquant un code erreur
}
       printf("Socket(serveur) créée avec succès ! (%d)\n", c);
       bind_socket( local_c,longueurAdress_c,c);
       while(1){
             send_msg(distant_c,c,argv[1],argv[2],messageEnvoi);

recv2(distant_c,c);
}
//close(c);
return 0;
}
