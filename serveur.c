/*#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>*/
#include "serveur.h"
#include "client2.h"
# define LG_MESSAGE 256
# define maxclient 3
//creation socket
int  cre_socket_ser(){
   int descripteurSocket;
   descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0); 
   return descripteurSocket;
}

void bind_socket_re(struct sockaddr_in pointDeRencontreLocal,socklen_t longueurAdresse,int des,int port){
  longueurAdresse = sizeof(struct sockaddr_in);
  memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
  pointDeRencontreLocal.sin_family= PF_INET;
  pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // n’importe quelle interface
 //locale disponible
  pointDeRencontreLocal.sin_port= htons(port); 
  printf("le port d'ecoute %d\n",port);
 if((bind(des, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse))< 0){
    perror("bind");
    exit(-2);
  }
 printf("Socket(serveur) attachée avec succès !\n");
}
void recv_msg(struct sockaddr_in pointDeRencontreDistant,int descripteurSocket, char messageRecu[LG_MESSAGE],socklen_t longueurAdresse){
    
     int lus;
     int envoi;
     longueurAdresse = sizeof(pointDeRencontreDistant);
  // Initialise à 0 la structure sockaddr_in (c’est l’appel recvfrom qui remplira cettestructure)
     memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
  // Initialise à 0 le message
     memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char));
  // Réceptionne un message du client
     lus = recvfrom(descripteurSocket, messageRecu, sizeof(messageRecu), 0, (struct sockaddr *)&pointDeRencontreDistant, &longueurAdresse);
 
   switch(lus)
   {
       case -1 : /* une erreur ! */
         perror("recvfrom");
         close(descripteurSocket);
         exit(-3);
       case 0 :
          fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
          close(descripteurSocket);
        default: /* réception de n octets */
               printf("Message %s reçu avec succès (%d octets)\n\n", messageRecu, lus);

}
}
 void Traitement(struct sockaddr_in pointDeRencontreDistant,int descripteurSocket, char messageRecu[LG_MESSAGE],socklen_t longueurAdresse,int actuel){

   while(1){
    int lus;
    int envoi;
    int i,r;
    struct sockaddr_in p;
    struct sockaddr_in client[maxclient];
   longueurAdresse = sizeof(pointDeRencontreDistant);
  // Initialise à 0 la structure sockaddr_in (c’est l’appel recvfrom qui remplira cettestructure)
  memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
  // Initialise à 0 le message
  memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char));
  // Réceptionne un message du client
  lus = recvfrom(descripteurSocket, messageRecu, sizeof(messageRecu), 0, (struct sockaddr *)&pointDeRencontreDistant, &longueurAdresse);
   //printf("ecrit(%d)\n",lus);
  // printf("Requéte reçu de %s:%d\n",inet_ntoa(pointDeRencontreDistant.sin_addr),ntohs(pointDeRencontreDistant.sin_port))
     switch(lus)

  
   {

      case -1 : 
           perror("recvfrom");
           close(descripteurSocket);
            exit(-3);
     case 0 :
         fprintf(stderr, "Aucune donnée n’a été envoyé !\n\n");
       close(descripteurSocket);
  default: 
     printf("Message\n %s recu (%d octets)\n", messageRecu, lus);
}
        struct sockaddr_in c=pointDeRencontreDistant;
        client[actuel]=c;
        actuel++;
           
    
        printf("actuel(%d)\n",actuel);
        // printf("Requéte reçu %s:%d\n",inet_ntoa(client[actuel-1].sin_addr),ntohs(client[actuel-1].sin_port));
         for (i=0;i<actuel;i++)
         printf("Requéte reçu %s:%d\n",inet_ntoa(client[i].sin_addr),ntohs(client[i].sin_port));
         // r = client_exist( client ,pointDeRencontreDistant,actuel);
         
  
        p=get_client(client,pointDeRencontreDistant, actuel);
       // if(&p==NULL) continue;
        if(actuel>1)
            send_all_client(descripteurSocket,client,pointDeRencontreDistant, messageRecu,actuel,longueurAdresse);


  }
}
int client_exist(struct sockaddr_in client[maxclient] ,struct sockaddr_in cl,int act){
  int i=0;

  for(i=0;i<act;i++){
         
       if(client[i].sin_addr.s_addr==cl.sin_addr.s_addr && client[i].sin_port==cl.sin_port){
         
             return 1;
         
                      }
                }
          
         return 0;
  

      }

void tab_client (struct sockaddr_in pers,int actuel ){
                   struct sockaddr_in clients[10];
                    clients[actuel]=pers;
                     actuel++;
                  }
 void send_all_client(int sock, struct sockaddr_in client[maxclient],struct sockaddr_in sender,char messageE[LG_MESSAGE],int act,socklen_t longueurAdresse){
     int i;
     int ecrits; 
     for(i=0;i<act-1;i++){
          // if(&sender!=&client[i]){
     ecrits = sendto(sock, messageE, strlen(messageE), 0, (struct
                   sockaddr *)&client[i], longueurAdresse);

   }
     switch(ecrits)
                    {
                    case -1 : /* une erreur ! */
                               perror("sendto");
                               close(sock);
                               exit(-3);
                     case 0 :
                            fprintf(stderr, "Aucune donnée n’a été envoyée !\n\n");
                            close(sock);
    //return 0;
     default: /* envoi de n octets */
    if(ecrits != strlen(messageE))
    fprintf(stderr, "Erreur dans l’envoie des données !\n\n");
     else
   printf("Message\n %s envoyé avec succès (%d octets)\n", messageE, ecrits);
}
}
struct sockaddr_in get_client(struct sockaddr_in cli[maxclient],struct sockaddr_in send,int actuel){
  int i=0;
  for(i=0;i<actuel;i++){
         if (cli[i].sin_addr.s_addr==send.sin_addr.s_addr && cli[i].sin_port==send.sin_port){
      
      return cli[i];
     }
}
}

//}

void affiche_connecte(struct sockaddr_in tab[maxclient],int n){
   int i=0;
   for(i=0;i<n;i++){
               printf("clients connectés %s:%d\n",inet_ntoa(tab[i].sin_addr),ntohs(tab[i].sin_port));
  
           
   }
 
}












