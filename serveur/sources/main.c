#include <stdio.h>

int main(int argc, char *argv[])
{
   if(argc == 2){
     printf("Port : %d", atoi(argv[1]));
   }else{
     printf("Il doit y avoir 1 argument : PORT");
   }
   return 0;

}
