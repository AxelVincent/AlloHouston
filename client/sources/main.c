#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "../headers/main.h"
#include "../headers/color.h"

#define INVALID_SOCKET -1
#define SIZE_MSG 256


int main(int argc, char *argv[])
{
   if(argc == 3)
   {
    // On a bien 1 argument qui doit etre l'adresse IP cible
    printf("HostName fournit : %s, port : %s\n", argv[1], argv[2]);

    char *host_name = argv[1];
    int numeroPort = atoi(argv[2]);
    char* adresse = getHostName(host_name);
    if(adresse != NULL)
    {
      int continuer = 1;

      int descripteurClient = creationClient(adresse, numeroPort);
      char* messageRecu;

      while(continuer)
      {
        messageRecu = receptionMessageServeur(descripteurClient);
        if(strcmp(messageRecu,"stop") == 0)
        {
          continuer = 0;
        }
        else
        {
          interactionServeur(descripteurClient);
        }
      }

      close(descripteurClient);

    }
    else
    {
      fprintf(stderr, RED "Probleme pour resoudre le nom de domaine" RESET "\n");
      exit(-1);
    }

   }else
   {
     fprintf(stderr, RED "Il doit y avoir 2 argument :"MAG" HOST" RED","MAG" PORT" RESET "\n");
     exit(-1);
   }
   return 0;

}

char* getHostName(char* host_name){
  struct hostent* host_info;
  host_info = gethostbyname(host_name);

  if (host_info == NULL)
  {
      return(NULL);
  }

  if (host_info->h_addrtype == AF_INET)
  {
      struct in_addr **address_list = (struct in_addr **)host_info->h_addr_list;
      for(int i = 0; address_list[i] != NULL; i++)
      {
          printf("Adresse ipv4 : %s\n", inet_ntoa(*address_list[i]));
          return inet_ntoa(*address_list[i]);
      }
  }
  else if (host_info->h_addrtype == AF_INET6)
  {
      struct in6_addr **address_list = (struct in6_addr **)host_info->h_addr_list;
      for(int i = 0; address_list[i] != NULL; i++)
      {
          printf("Adresse ipv6\n");
          return "ipV6";
      }
  }
  return NULL;

}

int creationClient(char* adresse, int numeroPort)
{

  struct sockaddr_in socketService;

  socketService.sin_family = AF_INET;
  socketService.sin_port = htons(numeroPort);
  (socketService.sin_addr).s_addr = inet_addr(adresse);

  int descripteur = socket(AF_INET,SOCK_STREAM,0);

  if(descripteur>=3)
  {
    printf("socket fonctionne\n");

    // int connect(int descripteur, const struct sockaddr *p, int len);
    if(connect(descripteur,(struct sockaddr *) &socketService,sizeof(socketService)) == 0)
    {
      printf("Connexion sur %s:%d\n", inet_ntoa(socketService.sin_addr), htons(socketService.sin_port));
      return descripteur;
    }
    else
    {
        fprintf(stderr, RED "Erreur lors de la connexion" RESET "\n");
        exit(-1);
    }

  }
  else
  {
    fprintf(stderr, RED "Erreur lors de la creation de la socket" RESET "\n");
    exit(-1);
  }

}



void interactionServeur(int descripteurSocketClient){

  // Recevoir la liste des villes
  // Afficher la liste des villes

  char messageAEnvoyer[SIZE_MSG];
  printf("Que voulez vous dire au serveur ? ");
  scanf("%256[0-9a-zA-Z ]", &messageAEnvoyer);
  printf(" Le message a envoyer est bien : %s \n",messageAEnvoyer );
  write(descripteurSocketClient, messageAEnvoyer, SIZE_MSG);

}

char* receptionMessageServeur(int descripteurSocketClient){

  //Reception des messages serveur

  char* commandeRecu;
  read(descripteurSocketClient, commandeRecu, SIZE_MSG);
  printf("Message reçu du père : %s\n", commandeRecu);
  return commandeRecu;

}
