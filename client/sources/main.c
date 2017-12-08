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
#define SIZE_MSG 1024

/**
* @file client/main.c
* @date 5 Dec 2017
* @brief Main du client
*
* @see ../headers/main.h
*/


/**
* @fn int main(int argc, char *argv[])
* @brief Fonction main du client
* @param argc le nombre de paramètres
* @param argv[] les paramètres de la commande
* @return 1 si reussite, 0 sinon
*/
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
      char *prefixe, *str;

      char messageRecu[SIZE_MSG];
      char messageEnvoye[SIZE_MSG];
      while(continuer)
      {
        receptionMessageServeur(descripteurClient, messageRecu);

        if(strcmp(messageRecu,"stop") == 0)
        {
          continuer = 0;
        }
        else
        {
          str = messageRecu;
          prefixe = strsep(&str, ";");
          if(strcmp(prefixe,"noread") != 0)
          {
            lectureEntreeClient(descripteurClient, messageEnvoye);
            if(strcmp(messageEnvoye,"stop") == 0)
            {
              fprintf(stderr,"%sFin de transmission.%s\n",BLU,RESET);
              continuer = 0;
            }
          }

        }
      }

      close(descripteurClient);

    }
    else
    {
      fprintf(stderr, RED "ALLO HOUSTON : Probleme pour resoudre le nom de domaine" RESET "\n");
      exit(-1);
    }

   }else
   {
     fprintf(stderr, RED "ALLO HOUSTON : Il doit y avoir 2 argument :"MAG" HOST" RED","MAG" PORT" RESET "\n");
     exit(-1);
   }
   return 0;

}


/**
* @fn char* getHostName(char* host_name)
* @brief Recupère le hostname grace a la fonction gethostbyname
* @param host_name le nom de l'host
* @return le nom de l'adresse
*/
char* getHostName(char* host_name)
{
  struct hostent* host_info;
  host_info = gethostbyname(host_name);

  if (host_info == NULL)
  {
      return(NULL);
  }

  if (host_info->h_addrtype == AF_INET)
  {
      struct in_addr **address_list = (struct in_addr **)host_info->h_addr_list;
      printf("Adresse ipv4 : %s\n", inet_ntoa(*address_list[0]));
      return inet_ntoa(*address_list[0]);
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


/**
* @fn int creationClient(char* adresse, int numeroPort)
* @brief Créer le client
* @param adresse le nom de l'host
* @param numeroPort le numero de port
* @return le descripteur de fichier
*/
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

    if(connect(descripteur,(struct sockaddr *) &socketService,sizeof(socketService)) == 0)
    {
      printf("Connexion sur %s:%d\n", inet_ntoa(socketService.sin_addr), htons(socketService.sin_port));
      return descripteur;
    }
    else
    {
        fprintf(stderr, RED "ALLO HOUSTON : Erreur lors de la connexion" RESET "\n");
        exit(-1);
    }

  }
  else
  {
    fprintf(stderr, RED "ALLO HOUSTON : Erreur lors de la creation de la socket" RESET "\n");
    exit(-1);
  }

}


/**
* @fn void lectureEntreeClient(int descripteurSocketClient, char * messageAEnvoyer)
* @brief Ecrit au serveur
* @param descripteurSocketClient le socket a qui parler
* @param messageAEnvoyer le message a envoyer
* @return void
*/
void lectureEntreeClient(int descripteurSocketClient, char * messageAEnvoyer)
{
  int resultWrite;
  fgets(messageAEnvoyer, SIZE_MSG, stdin);
  strtok(messageAEnvoyer, "\n");
  printf("Message envoye : %s \n",messageAEnvoyer );
  resultWrite = write(descripteurSocketClient, messageAEnvoyer, SIZE_MSG);
}


/**
* @fn void receptionMessageServeur(int descripteurSocketClient, char *commandeRecu)
* @brief recoit les messages
* @param descripteurSocketClient le socket a qui parler
* @param commandeRecu la command recu
* @return void
*/
void receptionMessageServeur(int descripteurSocketClient, char *commandeRecu){

  //Reception des messages serveur

  //Declaration des variables
  char *token1, *token2, *str;
  //Reception du message
  read(descripteurSocketClient, commandeRecu, SIZE_MSG);
  //Copie du message recu dans str
  str = commandeRecu;

  //Recuperation de la premiere partie de la chaine
  token2 = strtok(str, ";");
  //copie de la chaine recuperee
  token1 = token2;
  //Recuperation de la deuxieme partie de la chaine
  token2 = strtok(NULL, ";");

  //Si la deuxieme chaine est null on affiche la premiere, sinon on affiche la deuxieme
  if(token2 == NULL)
  {
    printf("%s", token1);
  }
  else
  {
    printf("%s", token2);
  }

}
