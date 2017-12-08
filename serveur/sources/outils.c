#include <ctype.h>
#include "../headers/outils.h"

/**
 * @file outils.c
 * @date 6 Dec 2017
 * @brief Fichier contenant les méthodes utiles à toutes les parties du programme
 * et non spécifique à une structure
 *
 */

 /**
  * @fn void strToUpper(char * temp)
  * @brief Modifie la chaine à l'adresse temp et la transforme en majuscule
  * @param temp Pointeur de la chaine à modifier
  */
void strToUpper(char * temp)
{
  // Converti en majuscule
  char *s = temp;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }

}

/**
 * @fn void trimwhitespace(char * s)
 * @brief Retire les whitespace de la chaine fournit
 * @param temp Pointeur de la chaine à modifier
 */
void trimwhitespace(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}
