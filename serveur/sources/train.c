#include "../headers/temps.h"
#include "../headers/train.h"
#include <stdio.h>
#include <string.h>

/**
 * @file train.c
 * @date 5 Dec 2017
 * @brief Fichier contenant les méthodes pour la structure Train
 *
 * @see ../headers/train.h
 * @see ../headers/temps.h
 */

 /**
  * @fn void printTrain(Train* train)
  * @brief Affiche les informations d'un train
  * @param train Le pointeur train pour lequel on souhaite afficher les informations.
  * @TODO ajuster l'affichage de la réduc.
  */
void printTrain(Train* train){
  printf("%s -> %s Départ %d:%d arrivée %d:%d Prix : %f Reduc : %d", train->villeDepart, train->villeArrivee, train->heureDepart.heure, train->heureDepart.minute, train->heureArrivee.heure, train->heureArrivee.heure, train->prix, train->reduc);
}

/**
 * @fn Train* trainFromCSV(char* csv)
 * @brief Crée un train correspondant au info de la chaine csv fournit
 * @param csv Une ligne csv sous la forme : "villeDepart;villeArrivee;heureDepart.heure;heureDepart.minute;heureDepart.heure;heureArrivee.minute;prix;reduc".
 * @return pointeur sur un train
 * Exemple de ligne csv reçu : "Grenoble;Valence;16;55;17;55;17.60;SUPPL"
 */
Train* trainFromCSV(char* csv){

  struct Train* train = malloc(sizeof(Train));
  char *token, *str, *tofree;
  tofree = str = strdup(csv);  // We own str's memory now.
  // villeDepart
  token = strsep(&str, ";");
  train->villeDepart = strdup(token);

  // villeArrivee
  token = strsep(&str, ";");
  train->villeArrivee = strdup(token);

  // heureDepart.heure
  token = strsep(&str, ";");
  train->heureDepart.heure = atoi(token);

  // heureDepart.minute
  token = strsep(&str, ";");
  train->heureDepart.minute = atoi(token);

  // heureArrivee.heure
  token = strsep(&str, ";");
  train->heureArrivee.heure = atoi(token);

  // heureArrivee.minute
  token = strsep(&str, ";");
  train->heureArrivee.minute = atoi(token);

  // prix
  token = strsep(&str, ";");
  train->prix = atof(token);

  // reduc
  token = strsep(&str, ";");
  if(token != NULL){
    if (token == "REDUC")
    {
      train->reduc = 1;
    }
    else if (token == "SUPPL")
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
