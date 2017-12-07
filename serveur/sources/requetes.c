#include <stdio.h>
#include <stdlib.h>

#include "../headers/temps.h"
#include "../headers/train.h"
#include "./train.c"
#include "../requetes.h"

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
	struct Train* trainFiltre = malloc(sizeof(Train));
	/*// Concatenation de l'heure et minutes de départ souhaité
	char concatenation[8];
	strcat(concatenation,heureDepart);
	strcat(concatenation,minuteDepart);
	int heureConcat = atoi(concatenation);*/
	heureDepart = heureDepart * 100;
	int heureConcat = heureDepart + minuteDepart;
	//printf("Heure de depart concatené: %d, %s, %s, %s \n", heureConcat, heureDepart, minuteDepart, concatenation);

	// Permet de matcher la ville de départ et la ville d'arrivée souhaitées
	// avec la structure contenant l'ensemble des trains de la base de données
	// Crée un nouveau tableau contenant les structures Trains compatible
	int j = 0;
	for (int i = 0; i < compteLigne; i++) {
		if (strcmp (villeDepart, listeTrain[i]->villeDepart) == 0)
		// Si les villes de départs sont identiques
		{
			if (strcmp (villeArrivee, listeTrain[i]->villeArrivee) == 0)
			// Si les villes d'arrivées sont identiques
			{
				if (heureConcat < tempsVersInt(listeTrain[i]->heureDepart))
				//Si l'heure du train est après l'heure souhaitée
				{
					trainFiltre[j] = *listeTrain[i];
					j++;
				}
			}
		}
	}

	// Fait la différence entre l'heure de départ souhaité et l'heure de
	// départ des trains compatible (heure A - heure B)
	int difference[j][2];
	int compteDifference = 0;
	for (compteDifference; compteDifference < j; compteDifference++)
	{
		// On récupère la valeur absolue de : heureConcat - heure du train
		difference[compteDifference][1] = abs(heureConcat- tempsVersInt(trainFiltre[compteDifference].heureDepart));
		// On associe l'index
		difference[compteDifference][2] = compteDifference;

		//printf("heure de difference %d, array %d\n", difference[compteDifference][1], difference[compteDifference][2]);
		//printf("heure d'entree :%d , heure dans la base :%d\n", atoi(heureDepart), trainFiltre[compteDifference].heureDepart->heure);

	}
	// Recherche du plus petit
	// Considerons comme le premier element comme le plus petit
	int plusPetit = difference[0][1];
	int index = difference[0][2];
	// Comparer chaque ligne au plus petit, remplacer le plus petit
	// si : valeur < plus petit
	for (compteDifference = 0; compteDifference < j; compteDifference++)
	{
		if (difference[compteDifference][1] < plusPetit) {
			plusPetit = difference[compteDifference][1];
			//printf("Arg 1 %d, plus petit que Arg2 %d\n", difference[compteDifference][1], plusPetit );
			index = difference[compteDifference][2];
		}
	}
	//printf("Le plus petit nombre est : %d, son index est : %d\n", plusPetit, index);
	//printf("VIlle de depart %d\n", trainFiltre[index].heureDepart->minute );
	return trainFiltre + index;
}



int tempsVersInt(struct Temps* temp)
{
	int test = temp->heure * 100 + temp->minute;
	return test;
}
