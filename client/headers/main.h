#ifndef MAIN_H
#define MAIN_H

int creationClient(char* adresse, int numeroPort);
char* getHostName(char* host_name);
<<<<<<< HEAD
char* lectureEntreeClient(int descripteurSocketClient);
=======
void interactionServeur(int descripteurSocketClient);
char* receptionMessageServeur(int descripteurSocketClient);
>>>>>>> 5ad80d4b0d751f0ae539fa268beafd5f48b6fb74
#endif
