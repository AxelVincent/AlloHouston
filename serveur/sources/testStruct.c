#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/temps.h"
#include "../headers/train.h"
#include "../headers/testStructure.h"
#include "./train.c"
#include "./temps.c"

/**
* @brief Exemple d'usage de la structure train et des fonctions printTrain() et trainFromCSV()
* @see ./train.c
* @see ../headers/train.h
* @see ../headers/temps.h
*/
int main(int argc, char *argv[])
{
	//INIT TRAIN
	struct Train* trainTest = malloc(sizeof(Train));
	/*trainTest->villeDepart = "Grenoble";
	trainTest->villeArrivee = "Valence";
	trainTest->heureDepart.heure = 6;
	trainTest->heureDepart.minute = 15;
	trainTest->heureArrivee.heure = 7;
	trainTest->heureArrivee.minute = 31;
	trainTest->prix = 17.60;
	trainTest->reduc = 0;

	printTrain(trainTest);
	printf("\n");

	char *csv = "Grenoble;Valence;16;55;17;55;17.60";
	struct Train* testTrainCSV;
	testTrainCSV = trainFromCSV(csv);
	printTrain(testTrainCSV);


	char *csv2 = "LYON;Paris;00;30;23;59;42.66";
	struct Train* testTrainCSV2;
	testTrainCSV2 = trainFromCSV(csv2);
	printf("\n");
	printTrain(testTrainCSV2);
	printf("\n");
	free(trainTest);
	free(testTrainCSV);
	free(testTrainCSV2);*/

	// Test des requetes
	char * villeDepart = "GRENOBLE";
	char * villeArrivee = "VALENCE";
	char * heureDepart = "16";
	char * minuteDepart = "35";
	char * heureDepartFin = "19:59";
	//int idxToDel = 2;
	//	memmove(&heureDepart[idxToDel], &heureDepart[idxToDel + 1], strlen(heureDepart) - idxToDel);
	// Création de la structure en faisant appel au ficher train.txt
	static const char nomFichier[] = "../ressources/Trains.txt";
	FILE *fichier = fopen ( nomFichier, "r" );
	int compteLigne = 0;
	if (fichier != NULL)
	{
		char ligne [ 256 ]; /* or other suitable maximum ligne size */
		int lineCount = 0;
		while (fgets(ligne, sizeof ligne, fichier) != NULL) /* read a ligne */
		{
			compteLigne ++;
		}
		printf("%d ligne dans le fichier Trains.txt\n", compteLigne);
		rewind(fichier);
		Train *listeTrain[compteLigne];
		while (fgets ( ligne, sizeof ligne, fichier ) != NULL) /* read a ligne */
		{
			listeTrain[lineCount] = trainFromCSV(ligne);
			//printTrain(listeTrain[lineCount]);
			lineCount ++;
		}
		fclose (fichier);
		// Une fois la structure établie, il est alors possible de commencer les traitements
		struct Train* tchoutchou = malloc(sizeof(Train));
		tchoutchou = trouverTrainLePlusProche(listeTrain, compteLigne, villeDepart,villeArrivee,heureDepart, minuteDepart);
    //fprintf(stderr, "tchoutchou%f\n", tchoutchou->prix);
		printTrain(tchoutchou);



		trouverTrainParTranche(listeTrain, compteLigne, villeDepart, villeArrivee, heureDepart, heureDepartFin);

	}
	else
	{
		perror ( nomFichier ); /* why didn't the fichier open? */
	}
	return 0;
}

int charVersInt(char *heure)
{
	int result;
	char *token, *str, *tofree;
	tofree = str = strdup(heure);
	//heureDepart
	token = strsep(&str, ":");
	int heures = atoi(token);
	//minutes
	token = strsep(&str, ":");
	int minutes = atoi(token);
	result = heures*100 + minutes;
	free(tofree);
	return result;
}


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
Train * trouverTrainLePlusProche(struct Train** listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, char * heureDepart, char * minuteDepart)
{
	struct Train* trainFiltre = malloc(sizeof(Train));
	// Concatenation de l'heure et minutes de départ souhaité
	char concatenation[8];
	strcat(concatenation,heureDepart);
	strcat(concatenation,minuteDepart);
	int heureConcat = atoi(concatenation);
	printf("Heure de depart concatené: %d, %s, %s, %s \n", heureConcat, heureDepart, minuteDepart, concatenation);

	// Permet de matcher la ville de départ et la ville d'arrivée souhaitées
	// avec la structure contenant l'ensemble des trains de la base de données
	// Crée un nouveau tableau contenant les structures Trains compatible
	printf("Ville : %s\n", villeDepart);
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

		printf("heure de difference %d, array %d\n", difference[compteDifference][1], difference[compteDifference][2]);
		printf("heure d'entree :%d , heure dans la base :%d\n", atoi(heureDepart), trainFiltre[compteDifference].heureDepart->heure);

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
			printf("Arg 1 %d, plus petit que Arg2 %d\n", difference[compteDifference][1], plusPetit );
			index = difference[compteDifference][2];
		}
	}
	printf("Le plus petit nombre est : %d, son index est : %d\n", plusPetit, index);
	printf("VIlle de depart %d\n", trainFiltre[index].heureDepart->minute );
	return trainFiltre + index;
}

void trouverTrainParTranche(struct Train** listeTrain,int tailleListe , char * villeDepart, char * villeArrivee, char * heureDepartDebut, char * heureDepartFin)
{
	Train *listeTrainNouvelle[tailleListe];
	int nombreTrainTries = 0;
	printf("ville depart : %s \n", villeDepart);
	printf("ville arrivee : %s \n", villeArrivee);

	for (int trainCourant = 0; trainCourant < tailleListe; trainCourant++)
	{
		//printf("ville de depart courant : %s\n arrivee : %s \n", listeTrain[trainCourant]->villeDepart, listeTrain[trainCourant]->villeArrivee );
		if (strcmp(villeDepart, listeTrain[trainCourant]->villeDepart) == 0 && strcmp(villeDepart, listeTrain[trainCourant]->villeDepart) == 0)
		{
			listeTrainNouvelle[nombreTrainTries] = listeTrain[trainCourant];
			//printTrain(listeTrain[trainCourant]);
			nombreTrainTries++;
		}
	}
	printf("%d\n", nombreTrainTries );
}



int tempsVersInt(struct Temps* temp)
{
	int test = temp->heure * 100 + temp->minute;
	return test;
}
