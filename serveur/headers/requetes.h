#ifndef REQUETES_H
#define REQUETES_H

Train * trouverTrainLePlusProche(struct Train** listeTrain, int tailleListe,  char * villeDepart, char * villeArrivee, int heureDepart, int minuteDepart);
int tempsVersInt(struct Temps* temp);
#endif
