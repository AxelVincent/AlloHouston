#ifndef TEMPS_H
#define TEMPS_H

typedef struct Temps Temps;
struct Temps
{
    int heure;
    int minute;
};

Temps* tempsFromCSV(char* csv);

#endif
