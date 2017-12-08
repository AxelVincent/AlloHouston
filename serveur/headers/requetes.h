#ifndef REQUETES_H
#define REQUETES_H
#include "../headers/train.h"

int trouverTrainLePlusProche(struct Train* listeTrain, int compteLigne,  char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart, char * commandeAEnvoyer);
int trouverTrainParTranche(struct Train* listeTrain, int * compteLigne , char * villeDepart, char * villeArrivee, int heureDepartDebut, int minuteDepartDebut, int heureDepartFin, int minuteDepartFin, char * commandeAEnvoyer);
Train * listeTrainParVille(struct Train * listeTrain, int * compteLigne, char * villeDepart, char * villeArrivee, char * commandeAEnvoyer);
int trajetSelonCritere(struct Train * listeTrain, int compteLigne, int critere, char * commandeAEnvoyer);
int tempsVersInt(struct Temps * temp);

#endif
