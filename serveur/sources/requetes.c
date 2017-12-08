#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/temps.h"
#include "../headers/train.h"
#include "../headers/requetes.h"
#include "../headers/outils.h"
#include "../headers/color.h"

#define SIZE_MSG 1024

/**
* @file requetes.c
* @date 5 Dec 2017
* @brief Traitement des différentes requetes possibles
*
* @see ../headers/requetes.h
*/

/**
* @fn void trouverTrainLePlusProche(struct Train* listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, char * heureDepart, char * minuteDepart, char* commandeAEnvoyer)
* @brief Renvoie le train le plus proche
* @param ListeTrain L'ensemble des trains contenus dans trains.txt
* @param compteLigne Nombre de train contenus dans la base
* @param villeDepart Ville de départ souhaitée
* @param villeArrivee Ville d'arrivée souhaitée
* @param heureDepart Heure de départ souhaitée
* @param minuteDepart Minute de départ souhaitée
* @param commandeAEnvoyer Pointeur pour indiquer le message à envoyer au serveur
* @return Train * Pointeur sur le Train le plus proche des paramètres fournit par le client
*/
Train * trouverTrainLePlusProche(struct Train* listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart, char* commandeAEnvoyer)
{
	//printf("Compte ligne : %d, villeDepart : %s, ville arrivee : %s, heure depart : %d, minute depart : %d\n",compteLigne, VD, VA, heureDepart, minuteDepart );
	for (int u = 0; u < compteLigne; u++) {
		//printf("Ville depart : %s, ville arrivee : %s\n", (listeTrain+u)->villeDepart, (listeTrain+u)->villeDepart);
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
		if (strcmp (villeDepart, (listeTrain + increment)->villeDepart) == 0)
		// Si les villes de départs sont identiques
		{
			//printf("PASSAGE strcmp ville depart \n");
			if (strcmp (villeArrivee, (listeTrain + increment)->villeArrivee) == 0)
			// Si les villes d'arrivées sont identiques
			{
				//printf("PASSAGE strcmp ville arrivee \n");
				if (heureConcat < tempsVersInt((listeTrain + increment)->heureDepart))
				//Si l'heure du train est après l'heure souhaitée
				{
					//printf("PASSAGE heure concat \n");
					trainFiltre[nbTrainFiltre] = *(listeTrain + increment);
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
	trainFiltre = trainFiltre + index;
	if(nbTrainFiltre > 0)
	{

		snprintf(commandeAEnvoyer, SIZE_MSG, "noread;%sVoici le train correspondant a votre recherche :%s\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix : %f Reduc : %d\n\n", MAG, RESET, trainFiltre->id, trainFiltre->villeDepart, trainFiltre->villeArrivee, trainFiltre->heureDepart->heure, trainFiltre->heureDepart->minute, trainFiltre->heureArrivee->heure, trainFiltre->heureArrivee->minute, trainFiltre->prix, trainFiltre->reduc);
		return trainFiltre;
	}
	else
	{

		printf("Aucun train ne correspond à ces critères\n");
		snprintf(commandeAEnvoyer, SIZE_MSG,"noread;%sAucun train ne correspond à ces critères.%s\n", MAG, RESET);
		return NULL;
	}


}

Train * trouverTrainParTranche(struct Train* listeTrain, int* tailleListe , char * villeDepart, char * villeArrivee, int heureDepartDebut, int minuteDepartDebut, int heureDepartFin, int minuteDepartFin, char* commandeAEnvoyer)
{
	strToUpper(villeDepart);
	strToUpper(villeArrivee);
	printf("%d\n",*tailleListe );
	int tab[*tailleListe];
	int nbTrains = 0;
	//struct Train *listeTrainNouvelle[*tailleListe];
	int trancheDebut = heureDepartDebut * 100  + minuteDepartDebut;
	int trancheFin = heureDepartFin * 100  + minuteDepartFin;

	for (int trainCourant = 0; trainCourant < *tailleListe; trainCourant++)
	{
		//printf("train courant ville depart : %s, %s \n", listeTrain[trainCourant].villeDepart, listeTrain[trainCourant].villeArrivee);
		// Tri en fonction de la ville de départ et d'arrivée
		if (strcmp(villeDepart, listeTrain[trainCourant].villeDepart) == 0)
		{
			if(strcmp(villeArrivee, listeTrain[trainCourant].villeArrivee) == 0)
			{
				// Heure où le train doit partir
				int heureDebut = tempsVersInt(listeTrain[trainCourant].heureDepart);

				if (heureDebut >= trancheDebut && heureDebut <= trancheFin)
				{
					// On ajoute ce train à la nouvelle liste
					tab[nbTrains] = trainCourant;
					nbTrains++;
				}
			}
		}
	}
	Train * trainFiltre = malloc(sizeof(Train) * nbTrains);
	for(int inc=0; inc< nbTrains; inc++)
	{
		trainFiltre[inc] = listeTrain[tab[inc]];
	}

	*tailleListe = nbTrains;
	if (nbTrains > 0)
	{
		char * commande;
		snprintf(commande, SIZE_MSG,"noread;%sVoici le(s) train(s) correspondant a votre recherche%s : ", MAG, RESET);
		for (int i=0; i< nbTrains; i++)
		{
			char * trainString;
			snprintf(trainString, SIZE_MSG, "\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix : %f Reduc : %d\n\n", (trainFiltre+i)->id, (trainFiltre+i)->villeDepart, (trainFiltre+i)->villeArrivee, (trainFiltre+i)->heureDepart->heure, (trainFiltre+i)->heureDepart->minute, (trainFiltre+i)->heureArrivee->heure, (trainFiltre+i)->heureArrivee->minute, (trainFiltre+i)->prix, (trainFiltre+i)->reduc);
			strcat(commande, trainString);
		}
		return trainFiltre;
	}
	else
	{
		printf("Aucun train ne correspond à ces critères\n");
		snprintf(commandeAEnvoyer, SIZE_MSG,"noread;%sAucun train ne correspond à ces critères.%s\n", MAG, RESET);
		return NULL;
	}
}

Train * listeTrainParVille(struct Train* listeTrain, int* compteLigne, char * villeDepart, char * villeArrivee, char* commandeAEnvoyer)
{
	int tab[*compteLigne];
	// Permet de matcher la ville de départ et la ville d'arrivée souhaitées
	// avec la structure contenant l'ensemble des trains de la base de données
	// Crée un nouveau tableau contenant les structures Trains compatible
	int nbTrainFiltre = 0;
	for (int index = 0; index < *compteLigne; index++) {
		if (strcmp (villeDepart, (listeTrain + index)->villeDepart) == 0)
		// Si les villes de départs sont identiques
		{
			if (strcmp (villeArrivee, (listeTrain + index)->villeArrivee) == 0)
			// Si les villes d'arrivées sont identiques
			{
				tab[nbTrainFiltre] = index;
				nbTrainFiltre++;
			}
		}
	}


	/*Train * trainFiltre = malloc(sizeof(Train)*nbTrainFiltre);
	for (int inc = 0; inc < nbTrainFiltre; inc++) {
	trainFiltre[inc] = listeTrain[tab[inc]];}*/

	if(nbTrainFiltre > 0)
	{
		Train * trainFiltre = malloc(sizeof(Train)*nbTrainFiltre);
		/*char * commande;
		snprintf(commande, SIZE_MSG,"noread;%sVoici le(s) train(s) correspondant a votre recherche%s : ", MAG, RESET);*/
		for (int inc = 0; inc < nbTrainFiltre; inc++) {
			trainFiltre[inc] = listeTrain[tab[inc]];

			char * trainString;
			/*snprintf(trainString, SIZE_MSG, "noread;%sVoici le train correspondant a votre recherche :%s\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix : %f Reduc : %d\n\n", MAG, RESET, trainFiltre[inc].id, trainFiltre[inc].villeDepart, trainFiltre[inc].villeArrivee, trainFiltre[inc].heureDepart->heure, trainFiltre[inc].heureDepart->minute, trainFiltre[inc].heureArrivee->heure, trainFiltre[inc].heureArrivee->minute, trainFiltre[inc].prix, trainFiltre[inc].reduc);
			strcat(commande, trainString);*/
		}

		*compteLigne = nbTrainFiltre;
		return trainFiltre;

	}
	else
	{

		printf("Aucun train ne correspond à ces critères\n");
		snprintf(commandeAEnvoyer, SIZE_MSG,"noread;%sAucun train ne correspond à ces critères.%s\n", MAG, RESET);

		*compteLigne = nbTrainFiltre;
		return NULL;
	}

}

Train * trajetSelonCritere(struct Train* listeTrain, int compteLigne, int critere, char * commandeAEnvoyer)
{

	struct Train* trainFiltre = malloc(sizeof(Train));
	printf("Compte ligne : %d, critere : %d\n",compteLigne,critere );
	printf("villeDepart : %s\n",(listeTrain + 0)->villeDepart );
	if (compteLigne > 0) {
		double tableauProvisoire[compteLigne][4];
		int incrementTableau;
		for (incrementTableau = 0; incrementTableau < compteLigne; incrementTableau++) {
			/* creation d'un tableau provisoire qui contient le prix, le prix avec reduc, la difference de temps et l'index afin de pouvoir trouver le plus petit */
			tableauProvisoire[incrementTableau][0] = listeTrain[incrementTableau].prix;
			// Prise en compte de la reduction pour trouver le prix le plus faible
			if (listeTrain[incrementTableau].reduc == 0)
			{
				tableauProvisoire[incrementTableau][1] = listeTrain[incrementTableau].prix;
			}
			if (listeTrain[incrementTableau].reduc == 1)
			{
				tableauProvisoire[incrementTableau][1] = (listeTrain[incrementTableau].prix * 0.8);
			}
			if (listeTrain[incrementTableau].reduc == -1)
			{
				tableauProvisoire[incrementTableau][1] = (listeTrain[incrementTableau].prix * 1.1);
			}

			// Calcul de la difference de temps pour trouver le trajet le plus court
			double heureDepart = listeTrain[incrementTableau].heureDepart->heure * 100;			double heureArrivee = listeTrain[incrementTableau].heureArrivee->heure * 100;
			double minuteDepart = listeTrain[incrementTableau].heureDepart->minute;
			double minuteArrivee = listeTrain[incrementTableau].heureArrivee->minute;
			double horaireDepart = heureDepart + minuteDepart;
			printf("Horaire depart : %f\n", horaireDepart);
			double horaireArrivee = heureArrivee + minuteArrivee;
			printf("Horaire arrivee : %f\n", horaireArrivee);
			tableauProvisoire[incrementTableau][2] = (horaireArrivee - horaireDepart);
			printf("difference d'heure : %f\n", tableauProvisoire[incrementTableau][2]);

			// index
			tableauProvisoire[incrementTableau][3] = incrementTableau;

		}

		if (critere == 1) {
			double plusPetit = tableauProvisoire[0][1];
			int index = tableauProvisoire[0][3];
			// Comparer chaque ligne au plus petit, remplacer le plus petit
			// si : valeur < plus petit
			for (incrementTableau = 0; incrementTableau < compteLigne; incrementTableau++)
			{
				if (tableauProvisoire[incrementTableau][1] < plusPetit) {
					plusPetit = tableauProvisoire[incrementTableau][1];
					index = tableauProvisoire[incrementTableau][3];
				}
			}

			struct Train* trainFiltre = malloc(sizeof(Train));
			trainFiltre = listeTrain + index;
			snprintf(commandeAEnvoyer, SIZE_MSG, "noread;%sVoici le train correspondant a votre recherche :%s\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix d'origine : %f Reduc : %d Prix final : %f\n\n", MAG, RESET, trainFiltre->id, trainFiltre->villeDepart, trainFiltre->villeArrivee, trainFiltre->heureDepart->heure, trainFiltre->heureDepart->minute, trainFiltre->heureArrivee->heure, trainFiltre->heureArrivee->minute, trainFiltre->prix, trainFiltre->reduc, plusPetit);
			/*printf("Départ %s: \n", trainFiltre->villeDepart);
			printf("Arrivee %s: \n", trainFiltre->villeArrivee);
			printf("heureDepart %d: \n", trainFiltre->heureDepart->heure);
			printf("minuteDepart %d: \n", trainFiltre->heureDepart->minute);
			printf("heureArrivee %d: \n", trainFiltre->heureArrivee->heure);
			printf("minuteArrivee %d: \n", trainFiltre->heureArrivee->minute);
			printf("prix %f: \n", trainFiltre->prix);
			printf("reduc %d: \n", trainFiltre->reduc);
			printf("prix final %f: \n", plusPetit);*/
			return trainFiltre;
		}
		if (critere == 2) {
			/* trajet de durée optimum */
			double plusPetit = tableauProvisoire[0][2];
			int index = tableauProvisoire[0][3];
			// Comparer chaque ligne au plus petit, remplacer le plus petit
			// si : valeur < plus petit
			for (incrementTableau = 0; incrementTableau < compteLigne; incrementTableau++)
			{
				if (tableauProvisoire[incrementTableau][2] < plusPetit) {
					plusPetit = tableauProvisoire[incrementTableau][2];
					index = tableauProvisoire[incrementTableau][3];
				}
			}
			printf("index : %d\n", index);
			struct Train* trainFiltre = malloc(sizeof(Train));
			trainFiltre = listeTrain + index;
			snprintf(commandeAEnvoyer, SIZE_MSG, "noread;%sVoici le train correspondant a votre recherche :%s\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix d'origine : %f Reduc : %d Prix final : %f\n\n", MAG, RESET, trainFiltre->id, trainFiltre->villeDepart, trainFiltre->villeArrivee, trainFiltre->heureDepart->heure, trainFiltre->heureDepart->minute, trainFiltre->heureArrivee->heure, trainFiltre->heureArrivee->minute, trainFiltre->prix, trainFiltre->reduc, plusPetit);
			return trainFiltre;
		}

	}
}


int tempsVersInt(struct Temps* temp)
{
	int test = temp->heure * 100 + temp->minute;
	return test;
}
