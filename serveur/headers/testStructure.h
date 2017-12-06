#ifndef TESTSTRUCTURE_H
#define TESTSTRUCTURE_H
void trouverTrain(struct Train** listeTrain, int tailleListe,  char * villeDepart, char * villeArrivee, char * heureDepart);
void trouverTrainParTranche(struct Train** listeTrain,int tailleListe , char * villeDepart, char * villeArrivee, char * heureDepartDebut, char * heureDepartFin);
int tempsVersInt(struct Temps* temp);
#endif
