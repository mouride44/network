
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
//#include "serveur.h"
//#include "client2.h"
# define LG_MESSAGE 256
# define maxclient 3


 void Traitement_cann(struct sockaddr_in distant,int des, char messageRecu[LG_MESSAGE],socklen_t longueurAdresse,int actuel){
     int a=0;
   while(1){
         int lus;
        int envoi;
        int i,r,j;
       struct sockaddr_in p;
    
   
      longueurAdresse = sizeof(distant);
   // Initialise à 0 la structure sockaddr_in (c’est l’appel recvfrom qui remplira cettestructure)
      memset(&distant, 0x00, longueurAdresse);
  // Initialise à 0 le message
       memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char));
  // Réceptionne un message du client
      lus = recvfrom(des, messageRecu, sizeof(messageRecu), 0, (struct sockaddr *)&distant, &longueurAdresse);
  
     switch(lus){

          case -1 : 
              perror("recvfrom");
              close(des);
              exit(-3);
         case 0 :
              fprintf(stderr, "Aucune donnée n’a été envoyé !\n\n");
              close(des);
         default: 
              printf("Message\n %s recu (%d octets)\n", messageRecu, lus);
}
   typedef struct clien
      {
       struct sockaddr_in sin;
       char *canal[10];
    }clien ;
   clien client[maxclient];
   struct clien c={0};
         c.sin=distant;
         //c.canal[actuel]=messageRecu;
         client[ actuel]=c;
          char *canal[LG_MESSAGE];
         canal[0]="canal1";
         canal[1]="canal2";
         canal[2]="canal3";
         canal[3]="canal4";
         canal[4]="canal5";
         canal[5]="canal6";
         canal[6]="canal7";
         canal[7]="canal8";
         canal[8]="canal9";
         canal[9]="canal10";
        	
         actuel++; 
     
        
        
        
       if( strchr(messageRecu, '\n') ) *strchr(messageRecu, '\n') = '\0';
       
       
       for(i=0;i<actuel;i++){
           if (strcmp(messageRecu,canal[i])==0){
                   printf("l'information du canal %s:%d\n:%s\n",inet_ntoa(client[i].sin.sin_addr),ntohs(client[i].sin.sin_port),canal[i]);
          }
          else{
           }
         
       }
      
  }
}
