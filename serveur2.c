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
#define PORT IPPORT_USERRESERVED
int main()
{
int descripteurSocket;
struct sockaddr_in pointDeRencontreLocal;
struct sockaddr_in pointDeRencontreDistant;
socklen_t longueurAdresse;
char messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
int lus; /* nb d’octets lus */
int retour;
// Crée un socket de communication
descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0);
/pointDeRencontreDistant/ Teste la valeur renvoyée par l’appel système socket()
if(descripteurSocket < 0) /* échec ? */
{
perror("socket"); // Affiche le message d’erreur
exit(-1); // On sort en indiquant un code erreur
}
printf("Socket créée avec succès ! (%d)\n", descripteurSocket);
// On prépare l’adresse d’attachement locale
longueurAdresse = sizeof(struct sockaddr_in);
memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
pointDeRencontreLocal.sin_family= PF_INET;
pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); 
pointDeRencontreLocal.sin_port= htons(8979); // <- 5000
// On demande l’attachement local de la socket
if((bind(descripteurSocket, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse))
< 0)
{
perror("bind");
exit(-2);
}
printf("Socket attachée avec succès !\n");
longueurAdresse = sizeof(pointDeRencontreDistant);
// Initialise à 0 la structure sockaddr_in (c’est l’appel recvfrom qui remplira cettestructure)
memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
// Initialise à 0 le message
memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char));
// Réceptionne un message du client
lus = recvfrom(descripteurSocket, messageRecu, sizeof(messageRecu), 0, (struct sockaddr
*)&pointDeRencontreDistant, &longueurAdresse);
switch(lus)
{
case -1 : /* une erreur ! */
perror("recvfrom");
close(descripteurSocket);
exit(-3);
case 0 :
fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
close(descripteurSocket);
return 0;
default: /* réception de n octets */
printf("Message %s reçu avec succès (%d octets)\n\n", messageRecu, lus);
}
//--> Fin de l’étape n°4 !
// On ferme la ressource avant de quitter
close(descripteurSocket);
return 0;
}
