#ifndef TESTSTRUCTURE_H
#define TESTSTRUCTURE_H
Train * trouverTrainLePlusProche(struct Train** listeTrain, int tailleListe,  char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart);
void trouverTrainParTranche(struct Train** listeTrain,int tailleListe , char * villeDepart, char * villeArrivee, char * heureDepartDebut, char * heureDepartFin);
int tempsVersInt(struct Temps* temp);
int charVersInt(char* heure);
#endif
