#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

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
	char commandeAEnvoyer[SIZE_MSG];
	strcpy(commandeAEnvoyer, "Quelle commande voulez vous effectuer ? \n 1: Recherche du premier train a partir de l'heure de depart \n 2: Recherche de trains dans une tranche horaire\n 3: Recherche tous les trains pour une ville de depart et d'arrivee\n");
	printf("nouveauService ok : %d\n",getpid());
	write(descripteurSocketService, commandeAEnvoyer, SIZE_MSG);
	// Réception de la fonction a executer
	char commandeChar[SIZE_MSG];
	read(descripteurSocketService,commandeChar, SIZE_MSG);

	//TODO voir en fonction du protocole d'échange
	int commande = atoi(commandeChar);
	printf("La commande que veux effectuer le client est %d", commande);
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
}
