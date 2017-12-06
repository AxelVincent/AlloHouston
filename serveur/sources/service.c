#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../headers/service.h"
#define SIZE_MSG 256

/**
 * @file service.c
 * @date 5 Dec 2017
 * @brief Fichier permettant la création d'un nouveau service
 *
 * @see ../headers/service.h
 */

 /**
  * @fn void nouveauService(int descripteurSocketService)
  * @brief Crée un nouveau service
  * @param descripteurSocketService descripteur de fichier associé au nouveau service, il est créé lorsque le serveur reçoit une nouvelle connexion
  * @TODO créer la communication read write pour effectuer des actions sur le serveur
  */
void nouveauService(int descripteurSocketService)
{
	// Rechercher par :
	// 					- ville de départ
	//					- ville d'arrivée
	//					- horaire de départ (train en question si l'heure est exacte, sinon le suivant)
	//					- tranche horaire (départ, obtention d'une liste)
	char commandeRecu[SIZE_MSG];
	printf("nouveauService ok : %d\n",getpid());
	int sizeRead;
	do{
		sizeRead = read(descripteurSocketService, &commandeRecu, SIZE_MSG);
		printf("Commande reçu du client : %s (taille = %d)\n", commandeRecu, sizeRead);
		//TODO voir en fonction du protocole d'échange
		int commande = atoi(commandeRecu);
		printf("La commande que veux effectuer le client est %d\n", commande);
		switch (commande) {
			case 1:
			//Fonction 1 : Ville de départ + ville d'arrivée +  horaire de départ TODO faire les fonctions par ici
			break;
			case 2:
			//Fonction 2 : ville de départ + ville d'arrivée + tranche horaire pour le départ TODO faire les fonctions par ici
			break;
			case 3:
			//Fonction 3 : Ville de départ + arrivée = renvoi une liste TODO faire les fonctions par ici
			break;
	}
	}while(commandeRecu != "QUIT" && sizeRead != 0); //Si sizeRead == 0 le client n'envoie plus rien, est-il mort ?
	printf("Communication terminé\n");
	//TODO suicider le fils pour éviter qu'il devienne une copie du serveur (en repartant dans le père)
}
