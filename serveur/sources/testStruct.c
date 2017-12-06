#include <stdio.h>
#include <stdlib.h>

#include "../headers/temps.h"
#include "../headers/train.h"
#include "../headers/testStructure.h"
#include "./train.c"

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
	char * villeDepart = "Valence";
	char * villeArrivee = "Montelimar";
	char * heureDepart = "14;14";

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

		trouverTrain(listeTrain,lineCount,villeDepart,villeArrivee,heureDepart);





	}
	else
	{
		perror ( nomFichier ); /* why didn't the fichier open? */
	}




	return 0;
}



void trouverTrain(struct Train** listeTrain, int compteLigne, char * villeDepart, char * villeArrivee, char * heureDepart)
{
	struct Train* nouvelleListe = malloc(sizeof(Train));
	int j = 0;
	for (int i = 0; i < compteLigne; i++) {
		if (strcmp (villeDepart, listeTrain[i]->villeDepart) == 0) {
			if (strcmp (villeArrivee, listeTrain[i]->villeArrivee) == 0) {
				nouvelleListe[j] = *listeTrain[i];
				j++;
			}
		}
	}

	




	printf("%s\n", listeTrain[20]->villeDepart);
	printf("%s\n", listeTrain[1]->villeArrivee);

	printf("ville depart : %s \n", villeDepart);
	printf("ville arrivee : %s \n", villeArrivee);
	printf("heure depart : %s \n", heureDepart);
	printTrain(listeTrain[2]);
}
