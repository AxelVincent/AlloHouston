#ifndef REQUETES_H
#define REQUETES_H
#include "../headers/train.h"
Train * trouverTrainLePlusProche(struct Train* listeTrain, int tailleListe,  char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart, char* commandeAEnvoyer);
Train * trouverTrainParTranche(struct Train* listeTrain, int* tailleListe , char * villeDepart, char * villeArrivee, int heureDepartDebut, int minuteDepartDebut, int heureDepartFin, int minuteDepartFin);
Train * listeTrainParVille(struct Train* listeTrain, int* compteLigne, char * villeDepart, char * villeArrivee);
int tempsVersInt(struct Temps* temp);
#endif
