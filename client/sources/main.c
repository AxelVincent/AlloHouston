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
    struct hostent* host_info;

    //Creation de la socket d'ecoute (Primitive "socket")
    int p;
    // int socket(int domaine, int type, int protocole);
    p = socket(AF_INET,SOCK_STREAM,0);
    //On récupère l'adresse IP de l'host fournit
    char *host_name = argv[1];
    host_info = gethostbyname(host_name);

    if (host_info == NULL)
    {
        return(-1);
    }

    if (host_info->h_addrtype == AF_INET)
    {
        struct in_addr **address_list = (struct in_addr **)host_info->h_addr_list;
        for(int i = 0; address_list[i] != NULL; i++)
        {
            printf("Adresse ipv4 : %s\n", inet_ntoa(*address_list[i]));
        }
    }
    else if (host_info->h_addrtype == AF_INET6)
    {
        struct in6_addr **address_list = (struct in6_addr **)host_info->h_addr_list;
        for(int i = 0; address_list[i] != NULL; i++)
        {
            printf("Adresse ipv6\n");
        }
    }

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
