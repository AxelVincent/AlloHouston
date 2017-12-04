#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../headers/main.h"


int main(int argc, char *argv[])
{
   if(argc == 2)
   {
     // On a bien 1 argument qui doit etre le numero de PORT
     creationServeur(atoi(argv[1]));
   }else
   {
     printf("Il doit y avoir 1 argument : PORT\n");
   }
   return 0;

}

void creationServeur(int numeroPort)
{
  //Creation du serveur
  // TODO Verifier si c'est bien le socket d'ecoute

  struct sockaddr_in socketEcoute;

  socketEcoute.sin_family = AF_INET;
  socketEcoute.sin_port = htons(numeroPort);
  (socketEcoute.sin_addr).s_addr = htonl(INADDR_ANY);

  //Creation de la socket d'ecoute (Primitive "socket")
  int descripteur;
  // int socket(int domaine, int type, int protocole);
  descripteur = socket(AF_INET,SOCK_STREAM,0);
  
  //Attachement de la socket (Primitive "bind")

  // int bind(int descripteur, const struct sockaddr *p, int len);
  if(descripteur>=2)
  {
    printf("socket fonctionne\n");
    if(bind(descripteur,(struct sockaddr *) &socketEcoute,sizeof(socketEcoute)) == 0)
    {
      // Bind works
      // int listen(int descripteur, int nb);
      printf("bind fonctionne\n");

      if(listen(descripteur, 100) == 0)
      {
        printf("listen fonctionne\n");

      }
      else
      {
        printf("Erreur lors du listen\n");
      }

    }
    else
    {
      //Bind don't works
      printf("Erreur lors du bind\n");
    }
  }
  else
  {
    printf("Erreur lors de la creation de la socket\n");
  }



}
