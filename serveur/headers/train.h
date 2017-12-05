#ifndef TRAIN_H
#define TRAIN_H
#include "./temps.h"

typedef struct Train Train;
struct Train
{
    char* villeDepart;
    char* villeArrivee;
    Temps heureDepart;
    Temps heureArrivee;
    double prix;
    int reduc;
};

#endif
