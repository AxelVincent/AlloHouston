#ifndef MAIN_H
#define MAIN_H

int creationClient(char* adresse, int numeroPort);
char* getHostName(char* host_name);
void interactionServeur(int descripteurSocketClient);
char* receptionMessageServeur(int descripteurSocketClient);
#endif
