# AlloHouston

## Convetion de nommages

```c
/**
 * @file main.c
 * @date 4 Dec 2017
 * @brief Fichier exemple des conventions
 *
 * @see ../headers/train.h
 */

 /**
  * @fn int main(int argc, char *argv[])
  * @brief Point d'entrée du programme
  * @param argc Le nombre d'argument de argv.
  * @param argv Tableau d'argument fournit au programme
  * @return int Resultat de l'éxécution
  * @TODO Expliquer à quoi sert un TODO.
  */
int main(int argc, char *argv[])
{ // Les accolades sont toujours à la ligne
   if (2 == 6) // Après un if/else/while, un espace avant la condition. Dans la condition entre chaque élément un espace
   {
    int monChat = oui; // Variable premiere lettre en minuscule puis le mot suivant commence par une majuscule
   }
   return 0;
}


 /**
  * @fn int PetiteFonction()
  * @brief Fonction qui renvoie 42
  * @return int Renvoie le sens de la vie
  * @TODO Trouver le sens de la vie
  */
int PetiteFonction() // Le nom des fonctions commence par une majuscule
{
   return 42;
}
```
