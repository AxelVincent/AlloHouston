#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "../headers/main.h"

#define INVALID_SOCKET -1


int main(int argc, char *argv[])
{
   if(argc == 3)
   {
    // On a bien 1 argument qui doit etre l'adresse IP cible
    printf("HostName fournit : %s, port : %s\n", argv[1], argv[2]);

    // INTITIALISATION sockaddr_in
    struct sockaddr_in s;
    int numeroPort = atoi(argv[2]);
    s.sin_family = AF_INET;
    s.sin_port = htons(numeroPort);
    (s.sin_addr).s_addr = htonl(INADDR_ANY);

    // INTITIALISATION sockaddr_in
    struct hostent* h;

    //Creation de la socket d'ecoute (Primitive "socket")
    int p;
    // int socket(int domaine, int type, int protocole);
    p = socket(AF_INET,SOCK_STREAM,0);
    //On récupère l'adresse IP de l'host fournit
    h = gethostbyname(argv[1]);
    struct in_addr addr;
    addr.s_addr = (u_long)h->h_addr_list[0];
    printf("IP Address is : %s\n", inet_ntoa(addr));

   }else
   {
     printf("Il doit y avoir 2 argument : HOST, PORT\n");
   }
   return 0;

}

int creationClient(char* hostname, int numeroPort, int descripteurSocketClient)
{

  struct sockaddr_in socketService;

  socketService.sin_family = AF_INET;
  socketService.sin_port = htons(numeroPort);
  (socketService.sin_addr).s_addr = inet_addr("127.0.0.1");

  int descripteur = socket(AF_INET,SOCK_STREAM,0);

  if(descripteur>=3)
  {
    printf("socket fonctionne\n");

    // int connect(int descripteur, const struct sockaddr *p, int len);
    if(connect(descripteur,(struct sockaddr *) &socketService,sizeof(socketService)) == 0)
    {
      printf("Connexion sur %s:%d\n", inet_ntoa(socketService.sin_addr), htons(numeroPort));
      return descripteur;
    }
    else
    {
        printf("Erreur lors de la connexion\n");
    }

  }
  else
  {
    printf("Erreur lors de la creation de la socket\n");
  }
  return -1;

}
