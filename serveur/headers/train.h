#ifndef TRAIN_H
#define TRAIN_H
#include "./temps.h"

typedef struct Train Train;
struct Train
{
    int id;
    char* villeDepart;
    char* villeArrivee;
    Temps heureDepart;
    Temps heureArrivee;
    double prix;
    int reduc; //Si 1 reduc, si -1 suppl, si 0 prix normal;
};

void printTrain(Train* train);
Train* trainFromCSV(char* csv);

#endif
