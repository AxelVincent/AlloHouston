#include <stdio.h>
#include <stdlib.h>

#include "../headers/temps.h"
#include "../headers/train.h"
#include "./train.c"

/**
 * @brief Exemple d'usage de la structure train et des fonctions printTrain() et trainFromCSV()
 * @see ./train.c
 * @see ../headers/train.h
 * @see ../headers/temps.h
 */
int main(int argc, char *argv[])
{
  //INIT TRAIN
  struct Train* trainTest = malloc(sizeof(Train));
  trainTest->villeDepart = "Grenoble";
  trainTest->villeArrivee = "Valence";
  trainTest->heureDepart.heure = 6;
  trainTest->heureDepart.minute = 15;
  trainTest->heureArrivee.heure = 7;
  trainTest->heureArrivee.minute = 31;
  trainTest->prix = 17.60;
  trainTest->reduc = 0;

  printTrain(trainTest);
  printf("\n");

  char *csv = "Grenoble;Valence;16;55;17;55;17.60";
  struct Train* testTrainCSV;
  testTrainCSV = trainFromCSV(csv);
  printTrain(testTrainCSV);


  char *csv2 = "LYON;Paris;00;30;23;59;42.66";
  struct Train* testTrainCSV2;
  testTrainCSV2 = trainFromCSV(csv2);
  printf("\n");
  printTrain(testTrainCSV2);
  printf("\n");
  free(trainTest);
  free(testTrainCSV);
  free(testTrainCSV2);

  //LECTURE de train.txt
  static const char filename[] = "../ressources/Trains.txt";
   FILE *file = fopen ( filename, "r" );
   int lineCount = 0;
   if ( file != NULL )
   {
      char line [ 256 ]; /* or other suitable maximum line size */
      int trainCount = 0;
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
        lineCount ++;
      }
      printf("%d ligne dans le fichier Trains.txt\n", lineCount);
      rewind(file); 
      Train *listeTrain[lineCount];
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
        listeTrain[trainCount] = trainFromCSV(line);
        printTrain(listeTrain[trainCount]);
        trainCount ++;
      }
      fclose ( file );
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
   }
  return 0;
}
