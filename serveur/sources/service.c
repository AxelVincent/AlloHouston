#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include "../headers/service.h"
#include "../headers/color.h"
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
	char commandeAEnvoyer[SIZE_MSG];
	int pid = getpid();
	printf("nouveauService ok : %d\n",pid);
	int sizeRead;
	do{
		printf("%d "MAG"MENU"RESET"\n", pid);
		strcpy(commandeAEnvoyer, "\n --- "CYN"MENU"RESET" ---\n 1: Recherche du premier train a partir de l'heure de depart \n 2: Recherche de trains dans une tranche horaire\n 3: Recherche tous les trains pour une ville de depart et d'arrivee\n Choix : ");
		envoyerMessage(descripteurSocketService, commandeAEnvoyer);
		recevoirMessage(descripteurSocketService, commandeRecu);

		//TODO voir en fonction du protocole d'échange
		int commande = atoi(commandeRecu);
		printf("La commande que veux effectuer le client est %d\n", commande);

		switch (commande) {
			case 1:
			//Fonction 1 : Ville de départ + ville d'arrivée +  horaire de départ TODO faire les fonctions par ici
				printf("%d "MAG"CHOIX DEPART"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville de de depart : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir de : %s (taille = %d)\n", commandeRecu, sizeRead);

				printf("%d "MAG"CHOIX ARRIVEE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville d'arrivee : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut aller a : %s (taille = %d)\n", commandeRecu, sizeRead);

				printf("%d "MAG"CHOIX HORAIRE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer l'heure de depart (HH:MN) : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir a partir de : %s (taille = %d)\n", commandeRecu, sizeRead);

				break;
			case 2:
			//Fonction 2 : ville de départ + ville d'arrivée + tranche horaire pour le départ TODO faire les fonctions par ici
				printf("%d "MAG"CHOIX DEPART"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville de de depart : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir de : %s (taille = %d)\n", commandeRecu, sizeRead);

				printf("%d "MAG"CHOIX ARRIVEE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville d'arrivee : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut aller a : %s (taille = %d)\n", commandeRecu, sizeRead);

				printf("%d "MAG"CHOIX HORAIRE 1/2"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer l'heure de debut (HH:MN) : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir a partir de : %s (taille = %d)\n", commandeRecu, sizeRead);

				printf("%d "MAG"CHOIX HORAIRE 2/2"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer l'heure de fin (HH:MN) : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir a partir de : %s (taille = %d)\n", commandeRecu, sizeRead);

			break;
			case 3:
			//Fonction 3 : Ville de départ + arrivée = renvoi une liste TODO faire les fonctions par ici
				printf("%d "MAG"CHOIX DEPART"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville de de depart : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir de : %s (taille = %d)\n", commandeRecu, sizeRead);

				printf("%d "MAG"CHOIX ARRIVEE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville d'arrivee : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut aller a : %s (taille = %d)\n", commandeRecu, sizeRead);
			break;
			default:
				printf("%d "RED"MAUVAIS ENTREE UTILISATEUR"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "noread;\n"RED"Mauvais choix dans le menu, veuillez reessayer"RESET"\n");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
	}
}while(strcmp(commandeRecu,"stop") != 0 && sizeRead != 0); //Si sizeRead == 0 le client n'envoie plus rien, est-il mort ?
	printf("Communication terminé\n");
	exit(-1);
}

void envoyerMessage(int descripteurSocketService, char *commandeAEnvoyer)
{
	write(descripteurSocketService, commandeAEnvoyer, SIZE_MSG);
}

void recevoirMessage(int descripteurSocketService, char *commandeRecu)
{
	int sizeRead;
	sizeRead = read(descripteurSocketService, commandeRecu, SIZE_MSG);
	printf("Commande reçu du client : %s (taille = %d)\n", commandeRecu, sizeRead);
}
