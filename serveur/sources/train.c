#include "../headers/temps.h"
#include "../headers/train.h"
#include <stdio.h>

void printTrain(Train train){
  printf("%s -> %s Départ %d:%d arrivée %d:%d Prix : %f", train.villeDepart, train.villeArrivee, train.heureDepart.heure, train.heureDepart.minute, train.heureArrivee.heure, train.heureArrivee.heure, train.prix);
}
