#ifndef TRAIN_H
#define TRAIN_H
#include "./temps.h"

typedef struct Train Train;
struct Train
{
    int id; //4 octets
    char* villeDepart;
    char* villeArrivee;
    Temps* heureDepart;
    Temps* heureArrivee;
    double prix; //4 octets
    int reduc; //Si 1 reduc, si -1 suppl, si 0 prix normal; 4 octets
};

void PrintfrintTrain(Train* train);
Train* TrainFromCSV(char* csv);

#endif
