#ifndef SERVICE_H
#define SERVICE_H

void nouveauService(int descripteurSocketService);
void recevoirMessage(int descripteurSocketService, char *commandeRecu);
void envoyerMessage(int descripteurSocketService, char *commandeAEnvoyer);
#endif
