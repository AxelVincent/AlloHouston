#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/temps.h"
#include "../headers/train.h"
#include "../headers/requetes.h"
#include "../headers/outils.h"

/**
* @file requetes.c
* @date 5 Dec 2017
* @brief Traitement des différentes requetes possibles
*
* @see ../headers/requetes.h
*/

/**
* @fn void trouverTrainLePlusProche(struct Train** listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, char * heureDepart, char * minuteDepart)
* @brief Renvoie le train le plus proche
* @param struct Train** listeTrain L'ensemble des trains contenus dans trains.txt
* @param compteLigne le nombre de train contenus dans la base
* @param villeDepart la ville de départ souhaitée
* @param villeArrivee la ville d'arrivée souhaitée
* @param heureDepart l'heure de départ souhaitée
* @return pointeur sur un temps
* Exemple de ligne csv reçu : "16:55"
*/
Train * trouverTrainLePlusProche(struct Train** listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart)
{
	char * VD = villeDepart;
	char * VA = villeArrivee;

	strToUpper(VD);
	strToUpper(VA);

	//printf("Compte ligne : %d, villeDepart : %s, ville arrivee : %s, heure depart : %d, minute depart : %d\n",compteLigne, VD, VA, heureDepart, minuteDepart );
	for (int u = 0; u < compteLigne; u++) {
		//printf("Ville depart : %s, ville arrivee : %s\n", listeTrain[u]->villeDepart, listeTrain[u]->villeDepart);
	}
	struct Train* trainFiltre = malloc(sizeof(Train));
	/*// Concatenation de l'heure et minutes de départ souhaité
	char concatenation[8];
	strcat(concatenation,heureDepart);
	strcat(concatenation,minuteDepart);
	int heureConcat = atoi(concatenation);*/

	heureDepart = heureDepart * 100;
	int heureConcat = heureDepart + minuteDepart;
	////printf("Heure de depart concatené: %d, %s, %s, %s \n", heureConcat, heureDepart, minuteDepart, concatenation);

	// Permet de matcher la ville de départ et la ville d'arrivée souhaitées
	// avec la structure contenant l'ensemble des trains de la base de données
	// Crée un nouveau tableau contenant les structures Trains compatible
//printf("PASSAGE 1\n");
	int nbTrainFiltre = 0;
	for (int increment = 0; increment < compteLigne; increment++) {
		//printf("PASSAGE boucle i \n");
		if (strcmp (VD, listeTrain[increment]->villeDepart) == 0)
		// Si les villes de départs sont identiques
		{
			//printf("PASSAGE strcmp ville depart \n");
			if (strcmp (VA, listeTrain[increment]->villeArrivee) == 0)
			// Si les villes d'arrivées sont identiques
			{
				//printf("PASSAGE strcmp ville arrivee \n");
				if (heureConcat < tempsVersInt(listeTrain[increment]->heureDepart))
				//Si l'heure du train est après l'heure souhaitée
				{
					//printf("PASSAGE heure concat \n");
					trainFiltre[nbTrainFiltre] = *listeTrain[increment];
					nbTrainFiltre++;
				}
			}
		}
	}

	// Fait la différence entre l'heure de départ souhaité et l'heure de
	// départ des trains compatible (heure A - heure B)
	int difference[nbTrainFiltre][2];
	int compteDifference;
	//printf("nbTrainFiltre = %d\n",nbTrainFiltre );
	for (compteDifference = 0; compteDifference < nbTrainFiltre; compteDifference++)
	{
		// On récupère la valeur absolue de : heureConcat - heure du train
		difference[compteDifference][0] = abs(heureConcat- tempsVersInt(trainFiltre[compteDifference].heureDepart));
		// On associe l'index
		difference[compteDifference][1] = compteDifference;
		//printf("PASSAGE 2\n");
		////printf("heure de difference %d, array %d\n", difference[compteDifference][1], difference[compteDifference][2]);
		////printf("heure d'entree :%d , heure dans la base :%d\n", atoi(heureDepart), trainFiltre[compteDifference].heureDepart->heure);

	}
	// Recherche du plus petit
	// Considerons comme le premier element comme le plus petit
	int plusPetit = difference[0][0];
	int index = difference[0][1];
	// Comparer chaque ligne au plus petit, remplacer le plus petit
	// si : valeur < plus petit
	for (compteDifference = 0; compteDifference < nbTrainFiltre; compteDifference++)
	{
		if (difference[compteDifference][0] < plusPetit) {
			plusPetit = difference[compteDifference][0];
			////printf("Arg 1 %d, plus petit que Arg2 %d\n", difference[compteDifference][1], plusPetit );
			index = difference[compteDifference][1];
		}
	}
	//printf("PASSAGE 3\n");
	////printf("Le plus petit nombre est : %d, son index est : %d\n", plusPetit, index);
	////printf("VIlle de depart %d\n", trainFiltre[index].heureDepart->minute );
	//printTrain(trainFiltre + index);
	return trainFiltre + index;
}

Train ** trouverTrainParTranche(struct Train** listeTrain, int* tailleListe , char * villeDepart, char * villeArrivee, int heureDepartDebut, int minuteDepartDebut, int heureDepartFin, int minuteDepartFin)
{
	printf("%d\n",*tailleListe );
	struct Train *listeTrainNouvelle[*tailleListe];
	int nbTrains = 0;
	int foisCent = heureDepartDebut * 100 ;
	int foisCent2 = heureDepartFin * 100;
	int trancheDebut;
	int trancheFin;
	trancheDebut = foisCent + minuteDepartDebut;
	trancheFin = foisCent2  + minuteDepartFin;
	printf("ville depart : %s, %d \n", villeDepart, trancheDebut);
	printf("ville arrivee : %s, %d \n", villeArrivee, trancheFin);
	// Pour chaque train on récupère ceux qui nous intéressent
	fprintf("Le train numero %d est  : villeDepart %s, villeArrivee %d ", 1,listeTrain[1]->villeDepart, listeTrain[1]->villeArrivee);
	for (int trainCourant = 0; trainCourant < *tailleListe; trainCourant++)
	{
		fprintf("Le train numero %d est  : villeDepart %s, villeArrivee %d ", trainCourant,listeTrain[trainCourant]->villeDepart, listeTrain[trainCourant]->villeArrivee);
		// Tri en fonction de la ville de départ et d'arrivée
		if (strcmp(villeDepart, listeTrain[trainCourant]->villeDepart) == 0)
		{
			if(strcmp(villeArrivee, listeTrain[trainCourant]->villeArrivee) == 0)
			{
				// Heure où le train doit partir
				int heureDebut = tempsVersInt(listeTrain[trainCourant]->heureDepart);

				if (heureDebut >= trancheDebut && heureDebut <= trancheFin)
				{
					// On ajoute ce train à la nouvelle liste
					listeTrainNouvelle[nbTrains] = listeTrain[trainCourant];
					printTrain(listeTrainNouvelle[nbTrains]);
				  nbTrains++;
				}
			}
		}
	}
	*tailleListe = nbTrains;
	Train ** listeToReturn = listeTrainNouvelle;
	return listeToReturn;
}

int tempsVersInt(struct Temps* temp)
{
	int test = temp->heure * 100 + temp->minute;
	return test;
}
