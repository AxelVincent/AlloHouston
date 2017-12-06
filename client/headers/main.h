#ifndef MAIN_H
#define MAIN_H

int creationClient(char* adresse, int numeroPort);
char* getHostName(char* host_name);
char* lectureEntreeClient(int descripteurSocketClient);
#endif
