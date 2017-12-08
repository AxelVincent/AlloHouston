# AlloHouston

---
## Installation
Pour compiler le client et le serveur, utiliser la commande "make".

---
## Utilisation
Le serveur est à lancer avant le client, sinon le client attendra le serveur jusqu'au timeout et renverra une erreur.
### Serveur
On exectute le serveur à l'aide de la commande suivante dans le dossier AlloHouston (la racine du projet).
>./serveur/bin/AlloHoustonServeur `PORT`
### Client
On exectute le client à l'aide de la commande suivante dans le dossier AlloHouston (la racine du projet).
>./client/bin/AlloHoustonClient `ADDRESSE` `PORT`

Après le lancement, le client guide l'utilisateur dans l'utilisation de l'application.
Différentes requêtes sont disponibles :
1. Recherche du premier train a partir de l'heure de départ 
2. Recherche de trains dans une tranche horaire
3. Recherche tous les trains pour une ville de départ et d'arrivée
4. Connexion en administrateur

---
## Convention de nommages

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
int petiteFonction() // Le nom des fonctions commence par une premiere lettre en minuscule puis le mot suivant par une majuscule
{
   return 42;
}
```
