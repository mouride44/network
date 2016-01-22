/*#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>*/
#include "client2.h"
# define LG_MESSAGE 256
//creation socket
int  cre_socket(){
    int descripteurSocket;
    descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0); 
    return descripteurSocket;
}
// attaché
void bind_socket(struct sockaddr_in pointDeRencontreLocal,socklen_t longueurAdresse,int des){

     longueurAdresse = sizeof(struct sockaddr_in);
     memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
     pointDeRencontreLocal.sin_family= PF_INET;
     pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // n’importe quelle interface
    //locale disponible
     pointDeRencontreLocal.sin_port= htons(0); // l’os choisira un numéro de port libre
     // On demande l’attachement local de la socket

   if((bind(des, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse))< 0){
       perror("bind");
       exit(-2);
  }
    printf("Socket(client) attachée avec succès !\n");
}

//envoyer un message a un serveur
void send_msg(struct sockaddr_in pointDeRencontreDistant,int descripteurSocket,const char *ip,const char *port,char messageEnvoi[LG_MESSAGE]){
    //char messageEnvoi[LG_MESSAGE];
     socklen_t longueurAdresse;
    int ecrits;
   // Obtient la longueur en octets de la structure sockaddr_in
    longueurAdresse = sizeof(pointDeRencontreDistant);
   // Initialise à 0 la structure sockaddr_in
    memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
  // Renseigne la structure sockaddr_in avec les
    pointDeRencontreDistant.sin_family = PF_INET;
  // On choisit le numéro de port d’écoute du serveur
    pointDeRencontreDistant.sin_port = htons(atoi(port)); 
   inet_aton(ip, &pointDeRencontreDistant.sin_addr); // à modifier selon ses
  ecrits = sendto(descripteurSocket, messageEnvoi, strlen(messageEnvoi), 0, (struct
  sockaddr *)&pointDeRencontreDistant, longueurAdresse);
   //printf("le port %d\n",pointDeRencontreDistant.sin_port);
  switch(ecrits)
    {
       case -1 : /* une erreur ! */
           perror("sendto");
           close(descripteurSocket);
           exit(-3);
       case 0 :
          fprintf(stderr, "Aucune donnée n’a été envoyée !\n\n");
          close(descripteurSocket);

       default: /* envoi de n octets */
            if(ecrits != strlen(messageEnvoi))
             fprintf(stderr, "Erreur dans l’envoie des données !\n\n");
        else
            printf("Message\n %s envoyé avec succès (%d octets)\n", messageEnvoi, ecrits);
}
}

//  recoit le message du serveur
void recv2(struct sockaddr_in distant,int disk){
 
   char mes[LG_MESSAGE];
   socklen_t longAdress;
   int lus;
   while(1){
      longAdress = sizeof(distant);
      // Initialise à 0 la structure sockaddr_in (c’est l’appel recvfrom qui remplira cettestructure)
      memset(&distant, 0x00, longAdress);
      // Initialise à 0 le message
     memset(mes, 0x00, LG_MESSAGE*sizeof(char));
     // Réceptionne un message du client
     lus = recvfrom(disk, mes, sizeof(mes), 0, (struct sockaddr*)&distant, &longAdress);

    switch(lus)
          {
          case -1 : 
              perror("recvfrom");
              close(disk);
              exit(-3);
         case 0 :
             fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
             close(disk);
         default:
               printf("%s (%d octets)\n\n", mes, lus);
}
}
      close(disk);
}



