#include <stdio.h>
#include <stdlib.h>

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
	char * villeDepart = "Grenoble";
	char * villeArrivee = "Valence";
	char * heureDepart = "14";
	char * minuteDepart = "14";
	char * heureDepartFin = "19:59";

	// Création de la structure en faisant appel au ficher train.txt
	static const char nomFichier[] = "../ressources/Trains.txt";
	FILE *fichier = fopen ( nomFichier, "r" );
	int compteLigne = 0;
	if ( fichier != NULL )
	{
		char ligne [ 256 ]; /* or other suitable maximum ligne size */
		int lineCount = 0;
		while ( fgets ( ligne, sizeof ligne, fichier ) != NULL ) /* read a ligne */
		{
			compteLigne ++;
		}
		printf("%d ligne dans le fichier Trains.txt\n", compteLigne);
		rewind(fichier);
		Train *listeTrain[compteLigne];
		while ( fgets ( ligne, sizeof ligne, fichier ) != NULL ) /* read a ligne */
		{
			listeTrain[lineCount] = trainFromCSV(ligne);
			//printTrain(listeTrain[compteLigne]);
			lineCount ++;
		}
		fclose ( fichier );
		// Une fois la structure établie, il est alors possible de commencer les traitements

		trouverTrainLePlusProche(listeTrain, compteLigne, villeDepart,villeArrivee,heureDepart, minuteDepart);
		trouverTrainParTranche(listeTrain, compteLigne, villeDepart, villeArrivee, heureDepart, heureDepartFin);




	}
	else
	{
		perror ( nomFichier ); /* why didn't the fichier open? */
	}




	return 0;
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
void trouverTrainLePlusProche(struct Train** listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, char * heureDepart, char * minuteDepart)
{
	struct Train* nouvelleListe = malloc(sizeof(Train));

	// Permet de matcher la ville de départ et la ville d'arrivée souhaitées
	// avec la structure contenant l'ensemble des trains de la base de données
	// Crée un nouveau tableau contenant les structures Trains compatible
	int j = 0;
	for (int i = 0; i < compteLigne; i++) {
		if (strcmp (villeDepart, listeTrain[i]->villeDepart) == 0) {
			if (strcmp (villeArrivee, listeTrain[i]->villeArrivee) == 0) {
				nouvelleListe[j] = *listeTrain[i];
				j++;
			}
		}
	}

	// Fait la différence entre l'heure de départ souhaité et l'heure de
	// départ des trains compatible
	int difference[j];
	char concatenation[4];
	strcat(concatenation,heureDepart);
	strcat(concatenation,minuteDepart);
	int heureConcat = atoi(concatenation);
	int compteDifference = 0;
	for (compteDifference; compteDifference < j; compteDifference++) {
		difference[compteDifference] = abs(atoi(heureDepart) - nouvelleListe[compteDifference].heureDepart->heure);
		printf("heure de difference %d\n", difference[compteDifference]);
		printf("heure d'entree :%d , heure dans la base :%d\n", atoi(heureDepart), nouvelleListe[compteDifference].heureDepart->heure);
	}
	printf("Concat : %d\n", heureConcat2);

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
		/*if (strcmp(villeDepart, listeTrain->villeDepart) == 0 && strcmp(villeDepart, listeTrain->villeDepart) == 0)
		{
		listeTrainNouvelle[nombreTrainTries] = listeTrain[trainCourant];
		printTrain(listeTrain[trainCourant]);
		nombreTrainTries++;
	}*/
}
printf("%d\n", nombreTrainTries );
}
