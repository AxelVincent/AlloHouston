#ifndef TESTSTRUCTURE_H
#define TESTSTRUCTURE_H
Train * trouverTrainLePlusProche(struct Train** listeTrain, int tailleListe,  char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart);
Train * listeTrainParVille(struct Train* listeTrain, int* compteLigne, char * villeDepart, char * villeArrivee);
int tempsVersInt(struct Temps* temp);
/*Train ** trouverTrainParTranche(struct Train** listeTrain, int* tailleListe , char * villeDepart, char * villeArrivee, int heureDepartDebut, int minuteDepartDebut, int heureDepartFin, int minuteDepartFin);
Train ** fonctionTri(struct Train** trains, int nbTrains);
int charVersInt(char* heure);*/
#endif
