#ifndef MAIN_H
#define MAIN_H

int creationClient(char* adresse, int numeroPort);
char* getHostName(char* host_name);
void lectureEntreeClient(int descripteurSocketClient, char * messageAEnvoyer);
void receptionMessageServeur(int descripteurSocketClient,char *commandeRecu);
#endif
