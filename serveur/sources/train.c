#include "../headers/temps.h"
#include "../headers/train.h"
#include "../headers/outils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @file train.c
 * @date 5 Dec 2017
 * @brief Fichier contenant les méthodes pour la structure Train
 *
 * @see ../headers/train.h
 * @see ../headers/temps.h
 */

 /**
  * @fn void printfrintTrain(Train* train)
  * @brief Affiche les informations d'un train
  * @param train Le pointeur train pour lequel on souhaite afficher les informations.
  * @TODO ajuster l'affichage de la réduc.
  */
void printTrain(Train* train)
{
  printf("%d : %s -> %s Départ %d:%d arrivée %d:%d Prix : %f Reduc : %d", train->id, train->villeDepart, train->villeArrivee, train->heureDepart->heure, train->heureDepart->minute, train->heureArrivee->heure, train->heureArrivee->minute, train->prix, train->reduc);
}

/**
 * @fn Train* trainFromCSV(char* csv)
 * @brief Crée un train correspondant au info de la chaine csv fournit
 * @param csv Une ligne csv sous la forme : "villeDepart;villeArrivee;heureDepart.heure;heureDepart.minute;heureDepart.heure;heureArrivee.minute;prix;reduc".
 * @return pointeur sur un train
 * Exemple de ligne csv reçu : "Grenoble;Valence;16:55;17:55;17.60;SUPPL"
 */
Train* trainFromCSV(char* csv)
{
  struct Train* train = malloc(sizeof(Train));
  char *token, *str, *tofree;
  tofree = str = strdup(csv);  // We own str's memory now.
  // id
  token = strsep(&str, ";");
  train->id = atoi(token);

  // villeDepart
  token = strsep(&str, ";");
  strToUpper(token); // On met le nom de ville en majuscule
  train->villeDepart = strdup(token);

  // villeArrivee
  token = strsep(&str, ";");
  strToUpper(token); // On met le nom de ville en majuscule
  train->villeArrivee = strdup(token);

  // heureDepart
  token = strsep(&str, ";");
  struct Temps* heureDepart = malloc(sizeof(Temps));
  heureDepart = tempsFromCSV(token);
  train->heureDepart = heureDepart;

  // heureArrivee
  token = strsep(&str, ";");
  struct Temps* heureArrivee = malloc(sizeof(Temps));
  heureArrivee = tempsFromCSV(token);
  train->heureArrivee = heureArrivee;

  // prix
  token = strsep(&str, ";");
  train->prix = atof(token);

  // reduc
  token = strsep(&str, ";");
  if (token != NULL)
  {
    strToUpper(token); // On met la reduc ou supp en majuscule
    int len = strlen(token);
    token[len-1] = '\0';
    if (strcmp(token, "REDUC") == 0)
    {
      train->reduc = 1;
    }
    else if (strcmp(token, "SUPPL") == 0)
    {
      train->reduc = -1;
    }
    else
    {
      train->reduc = 0;
    }
  }
  free(tofree); // We free the str we made
  return train;
}


/**
 * @fn Train ** trainFromFile(char* nomFichier, int* nbTrain)
 * @brief Crée un pointeur sur une liste de train depuis le fichier csv fournit
 * @param nomFichier Nom du fichier csv que l'on souhaite parser en liste de Train.
 * @param nbTrain Pointeur sur int qui contiendra le nombre de train trouvé dans le fichier csv.
 * @return pointeur sur une liste de train
 * @example :
 *   char *nomFichier = "../ressources/Trains.txt";
 *   Train **listeTrain;
 *   int nbTrain;
 *   listeTrain = trainFromFile(nomFichier, &nbTrain); // Récupération de la liste de train
 *
 */
Train ** trainFromFile(char* nomFichier, int* nbTrain){
	Train ** listeToutTrain;
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
		listeToutTrain = listeTrain;
	}
	else
	{
		perror ( nomFichier ); /* why didn't the fichier open? */
	}
  *nbTrain = compteLigne;
	return listeToutTrain;
}
