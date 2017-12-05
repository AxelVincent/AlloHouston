#include <stdio.h>

#include "../headers/temps.h"
#include "../headers/train.h"
#include "./train.c"


int main(int argc, char *argv[])
{
  //INIT TEMPS
  struct Temps heureDepart;
  heureDepart.heure = 6;
  heureDepart.minute = 15;
  struct Temps heureArrivee;
  heureArrivee.heure = 7;
  heureArrivee.minute = 31;

  //INIT TRAIN
  struct Train trainTest;
  trainTest.villeDepart = "Valence";
  trainTest.villeArrivee = "Grenoble";
  trainTest.heureDepart = heureDepart;
  trainTest.heureArrivee = heureArrivee;
  trainTest.prix = 17.60;
  trainTest.reduc = 0;

  printTrain(trainTest);

  return 0;
}
