#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void trimwhitespace(char * s);

int main() {
   char testChar[] = "Alors oui           ";
   //fgets(testChar, 256, stdin);
   printf("Message envoye : %s ", testChar);
   int resultAvant = strcmp(testChar, "Alors oui");
   printf("==  %d\n", resultAvant);
   trimwhitespace(testChar);
   printf("Message trimmé : %s ", testChar);
   int resultApres = strcmp(testChar, "Alors oui");
   printf("==  %d\n", resultApres);

}

// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
void trimwhitespace(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}
