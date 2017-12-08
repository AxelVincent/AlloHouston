#ifndef SERVICE_H
#define SERVICE_H

void nouveauService(int descripteurSocketService);
void recevoirMessage(int descripteurSocketService, char *commandeRecu);
void envoyerMessage(int descripteurSocketService, char *commandeAEnvoyer);
void choixHoraire(int descripteurSocketService, char *commandeRecu, char *commandeAEnvoyer, int *h, int *m, int pid);
void demanderVille(int descripteurSocketService, char *commandeRecu, char *commandeAEnvoyer, char **villeDepart, char **villeArrivee, int pid, int nbTrain,char **listeVilleDepart, char **listeVilleArrive);

#endif
