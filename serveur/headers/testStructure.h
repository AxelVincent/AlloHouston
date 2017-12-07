#ifndef TESTSTRUCTURE_H
#define TESTSTRUCTURE_H
Train * trouverTrainLePlusProche(struct Train** listeTrain, int tailleListe,  char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart);
Train ** trouverTrainParTranche(struct Train** listeTrain, int* tailleListe , char * villeDepart, char * villeArrivee, int heureDepartDebut, int minuteDepartDebut, int heureDepartFin, int minuteDepartFin);
Train ** fonctionTri(struct Train** trains, int nbTrains);
int tempsVersInt(struct Temps* temp);
int charVersInt(char* heure);
#endif
