#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../headers/service.h"
#define SIZE_MSG 256


void nouveauService(int descripteurSocketService)
{
	// Rechercher par :
	// 					- ville de départ
	//					- ville d'arrivée
	//					- horaire de départ (train en question si l'heure est exacte, sinon le suivant)
	//					- tranche horaire (départ, obtention d'une liste)
	char * messageRecu;
	printf("nouveauService ok : %d\n",getpid());
	read(descripteurSocketService, messageRecu, SIZE_MSG);
	printf("Message recu du client %s\n", messageRecu );
}
