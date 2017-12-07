#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include "../headers/temps.h"
#include "../headers/service.h"
#include "../headers/color.h"
#include "../headers/requetes.h"
#include "../headers/train.h"
#include "../headers/outils.h"

#define SIZE_MSG 1024

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
	// PID du process courant
	int pid = getpid();
	printf("nouveauService ok : %d\n",pid);
	int sizeRead;

	//Recuépration du fichier Trains.txt a chaque client
	//Cela permet que chaque client ets le dernier fichier bien a jour

	char *nomFichier = "./ressources/Trains.txt";
	Train *listeTrain;
	int nbTrain;
	listeTrain = trainFromFile(nomFichier, &nbTrain); // Récupération de la liste de train
	fprintf(stderr, "ON EST LA	\n");
	Train *ptrListeTrain[nbTrain];

	for (int i=0;  i <nbTrain; i++) {
		ptrListeTrain[i] = (listeTrain + i);
		/*
		printf("\n");
		printTrain(ptrListeTrain[i]);
		printf("\n");*/
	}

	//Affichage d'un petit train et envoie du message au client
	strcpy(commandeAEnvoyer, "noread;___________________________________________________________________\n       /\\                    /\\															 \n   ____\\/____============____\\/___    ___==========================\n /__|     OOOOOOOOOOOOO    [_]   |    |  |[]|  [_]    [_]    [_] \n/             S N C F            |    |  |  |										 \n\\________________________________|_ii_|__|__|______________________\n   ()==()    === ++++ ===  ()==()       ()==()     +++   ++++++++\n===================================================================\n\n");
	envoyerMessage(descripteurSocketService, commandeAEnvoyer);
	do{
		printf("%d "MAG"MENU"RESET"\n", pid);
		// Envoie du menu au client
		strcpy(commandeAEnvoyer,"---"CYN"MENU"RESET" ---\n 1: Recherche du premier train a partir de l'heure de depart \n 2: Recherche de trains dans une tranche horaire\n 3: Recherche tous les trains pour une ville de depart et d'arrivee\n Choix : ");
		envoyerMessage(descripteurSocketService, commandeAEnvoyer);
		recevoirMessage(descripteurSocketService, commandeRecu);

		// Lecture de la commande reçu et gestion des differents cas
		int commande = atoi(commandeRecu);
		printf("La commande que veux effectuer le client est %d\n", commande);
		int h,m, h2,m2;
		switch (commande) {
			case 1:
				//Fonction 1 : Ville de départ + ville d'arrivée +  horaire de départ
				// Envoie et reception des informations a propos de la ville de depart
				printf("%d "MAG"CHOIX DEPART"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville de de depart : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir de : %s (taille = %d)\n", commandeRecu, sizeRead);
				char* villeDepart = strdup(commandeRecu);

				// Envoie et reception des informations a propos de la ville d'arrivee
				printf("%d "MAG"CHOIX ARRIVEE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville d'arrivee : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut aller a : %s (taille = %d)\n", commandeRecu, sizeRead);
				char* villeArrivee = strdup(commandeRecu);

				// Envoie et reception des informations a propos de l'horaire
				printf("%d "MAG"CHOIX HORAIRE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer l'heure de depart (HH:MN) : ");
				choixHoraire(descripteurSocketService, commandeRecu, commandeAEnvoyer, &h,&m, pid);
				printf("Le client veut partir a partir de : %d:%d\n", h,m);

				Train *t = malloc(sizeof(Train));
				t = trouverTrainLePlusProche(ptrListeTrain, nbTrain, villeDepart, villeArrivee, h, m);
				printTrain(t);
				free(t);
				break;
			case 2:
			//Fonction 2 : ville de départ + ville d'arrivée + tranche horaire pour le départ
			// Envoie et reception des informations a propos de la ville de depart
				printf("%d "MAG"CHOIX DEPART"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville de de depart : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir de : %s (taille = %d)\n", commandeRecu, sizeRead);
				villeDepart = strdup(commandeRecu);
				// Envoie et reception des informations a propos de la ville d'arrivee
				printf("%d "MAG"CHOIX ARRIVEE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville d'arrivee : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut aller a : %s (taille = %d)\n", commandeRecu, sizeRead);
				villeArrivee = strdup(commandeRecu);

				// Envoie et reception des informations a propos de l'horaire de debut
				printf("%d "MAG"CHOIX HORAIRE 1/2"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer l'heure de debut (HH:MN) : ");
				choixHoraire(descripteurSocketService, commandeRecu, commandeAEnvoyer, &h,&m, pid);
				printf("Le client veut partir a partir de : %d:%d\n", h,m);

				// Envoie et reception des informations a propos de l'horaire de fin
				printf("%d "MAG"CHOIX HORAIRE 2/2"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer l'heure de fin (HH:MN) : ");
				choixHoraire(descripteurSocketService, commandeRecu, commandeAEnvoyer, &h2,&m2, pid);
				printf("Le client veut partir a partir de : %d:%d\n", h2,m2);

				printf("Taille de la liste : %d \n", nbTrain);
				Train** trainsLol = trouverTrainParTranche(listeTrain, &nbTrain, villeDepart, villeArrivee, h, m, h2, m2);

				for(int i=0; i<nbTrain; i++)
				{
					printTrain(trainsLol[i]);
				}

			break;
			case 3:
			//Fonction 3 : Ville de départ + arrivée = renvoi une liste
			// Envoie et reception des informations a propos de la ville de depart
				printf("%d "MAG"CHOIX DEPART"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville de de depart : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut partir de : %s (taille = %d)\n", commandeRecu, sizeRead);
				// Envoie et reception des informations a propos de la ville d'arrivee
				printf("%d "MAG"CHOIX ARRIVEE"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "\nVeuillez entrer la ville d'arrivee : ");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
				recevoirMessage(descripteurSocketService, commandeRecu);
				printf("Le client veut aller a : %s (taille = %d)\n", commandeRecu, sizeRead);


			break;
			default:
				//Erreur dans une entree client, on retourne au menu
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

void choixHoraire(int descripteurSocketService, char *commandeRecu, char *commandeAEnvoyer, int *h,int *m,int pid)
{
	char *cmdAEnvoyer;
	cmdAEnvoyer = strdup(commandeAEnvoyer);

	int valide = 0;
	do
	{

		//Envoie er reception des messages
		envoyerMessage(descripteurSocketService, cmdAEnvoyer);
		recevoirMessage(descripteurSocketService, commandeRecu);

		//Declarations des pointeurs
		char *token1, *token2, *texte1, *texte2;
		char *str = commandeRecu;

		//Split de la reponse
		token1 = strsep(&str, ":");
		token2 = strsep(&str, ":");


		//Test du format de la repopnse (HH:MM)
		if(token2 != NULL)
		{

			// Transformation en int des entrees client
			*h = (int) strtol(token1, &texte1, 10);
			*m = (int) strtol(token2, &texte2, 10);
			printf("%d:%d\n",*h,*m);
			printf("%s\n",texte1);
			if(strcmp(texte1,"") == 0 && strcmp(texte2,"") == 0 && *h>=0 && *h<24 && *m>=0 && *m<60){
				//Tout c'est bien passe, sortie de la boucle
				valide =1;
			}
			else
			{
				//Mauvais entree utilisateur, on redemande l'horaire
				printf("%d "RED"MAUVAIS ENTREE UTILISATEUR"RESET"\n", pid);
				strcpy(commandeAEnvoyer, "noread;"RED"Mauvais choix des horaires : ex : 10:10"RESET"\n");
				envoyerMessage(descripteurSocketService, commandeAEnvoyer);
			}
		}
		else
		{
			//Mauvais entree utilisateur, on redemande l'horaire
			printf("%d "RED"MAUVAIS ENTREE UTILISATEUR"RESET"\n", pid);
			strcpy(commandeAEnvoyer, "noread;"RED"Mauvais choix des horaires : ex : 10:10"RESET"\n");
			envoyerMessage(descripteurSocketService, commandeAEnvoyer);
		}

	}
	while(valide == 0);

}
