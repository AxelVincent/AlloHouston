#include "../headers/temps.h"
#include "../headers/train.h"
#include <stdio.h>

/**
 * @file train.c
 * @date 5 Dec 2017
 * @brief Fichier contenant les méthodes pour la structure Train
 *
 * @see ../headers/train.h
 * @see ../headers/temps.h
 */

 /**
  * @fn void printTrain(Train train)
  * @brief Affiche les informations d'un train
  * @param train Le train pour lequel on souhaite afficher les informations.
  * @TODO ajouter l'affichage de la réduc.
  */
void printTrain(Train train){
  printf("%s -> %s Départ %d:%d arrivée %d:%d Prix : %f", train.villeDepart, train.villeArrivee, train.heureDepart.heure, train.heureDepart.minute, train.heureArrivee.heure, train.heureArrivee.heure, train.prix);
}

/**
 * @fn Train trainFromCSV(char* csv)
 * @brief Affiche les informations d'un train
 * @param csv Une ligne csv sous la forme : "villeDepart;villeArrivee;heureDepart;heureArrivee;prix;reduc".
 * Exemple de ligne csv reçu : "Grenoble;Valence;16:55;17:55;17.60;SUPPL"
 */
Train trainFromCSV(char* csv){
  // @TODO
}
