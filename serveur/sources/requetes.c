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

// REQUETE 1
/**
* @fn void trouverTrainLePlusProche(struct Train* listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, char * heureDepart, char * minuteDepart, char* commandeAEnvoyer)
* @brief Renvoie le train le plus proche
* @param ListeTrain L'ensemble des trains contenus dans trains.txt
* @param compteLigne Nombre de trains contenus dans la base
* @param villeDepart Ville de départ souhaitée
* @param villeArrivee Ville d'arrivée souhaitée
* @param heureDepart Heure de départ souhaitée
* @param minuteDepart Minute de départ souhaitée
* @param commandeAEnvoyer Pointeur pour indiquer le message à envoyer au serveur
* @return 1 si reussite, 0 sinon
*/
int trouverTrainLePlusProche(struct Train* listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart, char* commandeAEnvoyer)
{
	//printf("Compte ligne : %d, villeDepart : %s, ville arrivee : %s, heure depart : %d, minute depart : %d\n",compteLigne, VD, VA, heureDepart, minuteDepart );
	/*for (int u = 0; u < compteLigne; u++) {
	printf("Ville depart : %s, ville arrivee : %s\n", (listeTrain+u)->villeDepart, (listeTrain+u)->villeDepart);
}*/
struct Train* trainFiltre;
/*// Concatenation de l'heure et minutes de départ souhaité
char concatenation[8];
strcat(concatenation,heureDepart);
strcat(concatenation,minuteDepart);
int heureConcat = atoi(concatenation);*/

heureDepart = heureDepart * 100;
int heureConcat = heureDepart + minuteDepart;
// Permet de matcher la ville de départ et la ville d'arrivée souhaitées
// avec la structure contenant l'ensemble des trains de la base de données
// Crée un nouveau tableau contenant les structures Trains compatible
//printf("PASSAGE 1\n");
int nbTrainFiltre = 0;
for (int index = 0; index < compteLigne; index++) {
	//printf("PASSAGE boucle i \n");
	if (strcmp (villeDepart, (listeTrain + index)->villeDepart) == 0)
	// Si les villes de départs sont identiques
	{
		//printf("PASSAGE strcmp ville depart \n");
		if (strcmp (villeArrivee, (listeTrain + index)->villeArrivee) == 0)
		// Si les villes d'arrivées sont identiques
		{
			//printf("PASSAGE strcmp ville arrivee \n");
			if (heureConcat < tempsVersInt((listeTrain + index)->heureDepart))
			//Si l'heure du train est après l'heure souhaitée
			{
				//printf("PASSAGE heure concat \n");
				*(trainFiltre + nbTrainFiltre) = *(listeTrain + index);
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
	difference[compteDifference][0] = abs(heureConcat- ( ((trainFiltre + compteDifference)->heureDepart->heure*100) + ((trainFiltre + compteDifference)->heureDepart->minute)));
	printf("Temps concat diff %d\n", difference[compteDifference][0]);
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
		index = difference[compteDifference][1];
	}
}
//printf("PASSAGE 3\n");
printf("Le plus petit nombre est : %d, son index est : %d\n", plusPetit, index);
printf("VIlle de depart %d\n", trainFiltre[index].heureDepart->minute );
printTrain(trainFiltre + index);
trainFiltre = trainFiltre + index;
if(nbTrainFiltre > 0)
{
	snprintf(commandeAEnvoyer, SIZE_MSG, "noread;%sVoici le train correspondant a votre recherche :%s\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix : %.2f Reduc : %d\n\n", MAG, RESET, trainFiltre->id, trainFiltre->villeDepart, trainFiltre->villeArrivee, trainFiltre->heureDepart->heure, trainFiltre->heureDepart->minute, trainFiltre->heureArrivee->heure, trainFiltre->heureArrivee->minute, trainFiltre->prix, trainFiltre->reduc);
	return 1;
}
else
{
	printf("Aucun train ne correspond à ces critères\n");
	snprintf(commandeAEnvoyer, SIZE_MSG,"noread;%sAucun train ne correspond à ces critères.%s\n", MAG, RESET);
	return 0;
}
}

// REQUETE 2
int trouverTrainParTranche(struct Train * listeTrain, int * compteLigne , char * villeDepart, char * villeArrivee, int heureDepartDebut, int minuteDepartDebut, int heureDepartFin, int minuteDepartFin, char * commandeAEnvoyer)
{
	Train * trainFiltre;
	int trancheDebut = heureDepartDebut * 100  + minuteDepartDebut;
	int trancheFin = heureDepartFin * 100  + minuteDepartFin;
	int nbTrainFiltre = 0;
	for (int index = 0; index < *compteLigne; index++)
	{
		// Tri en fonction de la ville de départ et d'arrivée
		if (strcmp(villeDepart, (listeTrain + index)->villeDepart) == 0)
		{
			if(strcmp(villeArrivee, (listeTrain + index)->villeArrivee) == 0)
			{
				// Heure où le train doit partir
				int heureDebut = tempsVersInt((listeTrain + index)->heureDepart);
				printf("heureDebut : %d\n",heureDebut );
				if (heureDebut >= trancheDebut && heureDebut <= trancheFin)
				{
					printf("P\n");
					// On ajoute ce train à la nouvelle liste
					*(trainFiltre + nbTrainFiltre) = *(listeTrain + index);
					nbTrainFiltre++;
				}
			}
		}
	}

	*compteLigne = nbTrainFiltre;

	if (nbTrainFiltre > 0)
	{
		char * test;

		snprintf(commandeAEnvoyer, SIZE_MSG,"noread;%sVoici le(s) train(s) correspondant a votre recherche%s :\n", MAG, RESET);
		fprintf(stderr, "AALLA\n");
		for (int i=0; i< nbTrainFiltre; i++)
		{
			printf("%d\n", nbTrainFiltre);

			snprintf(commandeAEnvoyer, SIZE_MSG, "%d : %s -> %s Départ %d:%d arrivée %d:%d Prix : %.2f Reduc : %d\n", (trainFiltre+i)->id, (trainFiltre+i)->villeDepart, (trainFiltre+i)->villeArrivee, (trainFiltre+i)->heureDepart->heure, (trainFiltre+i)->heureDepart->minute, (trainFiltre+i)->heureArrivee->heure, (trainFiltre+i)->heureArrivee->minute, (trainFiltre+i)->prix, (trainFiltre+i)->reduc);
		}

		//snprintf(commandeAEnvoyer, "\n");

		return 1;
	}
	else
	{
		printf("Aucun train ne correspond à ces critères\n");
		snprintf(commandeAEnvoyer, SIZE_MSG,"noread;%sAucun train ne correspond à ces critères.%s\n", MAG, RESET);
		return 0;
	}
}
// REQUETE 3
/**
* @fn Train * listeTrainParVille(struct Train * listeTrain, int * compteLigne, char * villeDepart, char * villeArrivee, char* commandeAEnvoyer)
* @brief Crée la liste des trains selon les critères ville de depart et ville d'arrivee
* @param ListeTrain L'ensemble des trains contenus dans trains.txt
* @param compteLigne Nombre de trains contenus dans la base
* @param villeDepart Ville de départ souhaitée
* @param villeArrivee Ville d'arrivée souhaitée
* @param commandeAEnvoyer Pointeur pour indiquer le message à envoyer au serveur
* @return Train * Pointeur sur la liste de trains répondants aux critères
*/
Train * listeTrainParVille(struct Train * listeTrain, int * compteLigne, char * villeDepart, char * villeArrivee, char* commandeAEnvoyer)
{
	int tableauProvisoire[*compteLigne];
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
				tableauProvisoire[nbTrainFiltre] = index;
				nbTrainFiltre++;
			}
		}
	}

	if(nbTrainFiltre > 0)
	{
		Train * trainFiltre = malloc(sizeof(Train)*nbTrainFiltre);
		/*char * commande;
		snprintf(commande, SIZE_MSG,"noread;%sVoici le(s) train(s) correspondant a votre recherche%s : ", MAG, RESET);*/
		for (int inc = 0; inc < nbTrainFiltre; inc++) {
			trainFiltre[inc] = listeTrain[tableauProvisoire[inc]];

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

// REQUETE 3 BIS
/**
* @fn int trajetSelonCritere(struct Train* listeTrain, int compteLigne, int critere, char * commandeAEnvoyer)
* @brief Renvoie le train ayant le plus court trajet ou bien le train le moins cher
* @param ListeTrain L'ensemble des trains contenus dans trains.txt
* @param compteLigne Nombre de trains contenus dans la base
* @param critere :	- 1 pour le trajet le moins cher
*					- 2 pour le trajet le plus court
* @param commandeAEnvoyer Pointeur pour indiquer le message à envoyer au serveur
* @return 1 si reussite, 0 sinon
*/
int trajetSelonCritere(struct Train* listeTrain, int compteLigne, int critere, char * commandeAEnvoyer)
{

	struct Train* trainFiltre;
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
				tableauProvisoire[incrementTableau][1] = (listeTrain+incrementTableau)->prix;
			}
			if (listeTrain[incrementTableau].reduc == 1)
			{
				tableauProvisoire[incrementTableau][1] = (listeTrain+incrementTableau)->prix * 0.8;
			}
			if (listeTrain[incrementTableau].reduc == -1)
			{
				tableauProvisoire[incrementTableau][1] = (listeTrain+incrementTableau)->prix * 1.1;
			}

			// Calcul de la difference de temps pour trouver le trajet le plus court
			int heureDepart = (listeTrain + incrementTableau)->heureDepart->heure * 100;
			int heureArrivee = (listeTrain + incrementTableau)->heureArrivee->heure * 100;
			int minuteDepart = (listeTrain + incrementTableau)->heureDepart->minute;
			int minuteArrivee = (listeTrain + incrementTableau)->heureArrivee->minute;
			int horaireDepart = heureDepart + minuteDepart;

			int horaireArrivee = heureArrivee + minuteArrivee;

			tableauProvisoire[incrementTableau][2] = (horaireArrivee - horaireDepart);


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

			struct Train* trainFiltre;
			trainFiltre = listeTrain + index;
			snprintf(commandeAEnvoyer, SIZE_MSG, "noread;%sVoici le train correspondant a votre recherche :%s\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix d'origine : %.2f Reduc : %d Prix final : %.2f\n\n", MAG, RESET, trainFiltre->id, trainFiltre->villeDepart, trainFiltre->villeArrivee, trainFiltre->heureDepart->heure, trainFiltre->heureDepart->minute, trainFiltre->heureArrivee->heure, trainFiltre->heureArrivee->minute, trainFiltre->prix, trainFiltre->reduc, tableauProvisoire[index][1]);
			/*printf("Départ %s: \n", trainFiltre->villeDepart);
			printf("Arrivee %s: \n", trainFiltre->villeArrivee);
			printf("heureDepart %d: \n", trainFiltre->heureDepart->heure);
			printf("minuteDepart %d: \n", trainFiltre->heureDepart->minute);
			printf("heureArrivee %d: \n", trainFiltre->heureArrivee->heure);
			printf("minuteArrivee %d: \n", trainFiltre->heureArrivee->minute);
			printf("prix %f: \n", trainFiltre->prix);
			printf("reduc %d: \n", trainFiltre->reduc);
			printf("prix final %f: \n", plusPetit);*/
			return 1;
		}
		else if (critere == 2) {
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
			struct Train* trainFiltre;
			trainFiltre = listeTrain + index;
			snprintf(commandeAEnvoyer, SIZE_MSG, "noread;%sVoici le train correspondant a votre recherche :%s\n%d : %s -> %s Départ %d:%d arrivée %d:%d Prix d'origine : %.2f Reduc : %d Prix final : %.2f\n\n", MAG, RESET, trainFiltre->id, trainFiltre->villeDepart, trainFiltre->villeArrivee, trainFiltre->heureDepart->heure, trainFiltre->heureDepart->minute, trainFiltre->heureArrivee->heure, trainFiltre->heureArrivee->minute, trainFiltre->prix, trainFiltre->reduc, tableauProvisoire[index][1]);
			return 1;
		}
		else
		{
			return 0;
		}

	}
	else
	{
		return 0;
	}
}


int tempsVersInt(struct Temps* temp)
{
	int test = temp->heure * 100 + temp->minute;
	return test;
}
