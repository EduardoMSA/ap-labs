#include <stdio.h>

int main(){
    // Place your magic here
   char word[100];
   printf("Enter your name: ");
   /*fgets(word, 100, stdin);
   printf("Your Name is: %s",word);
   */

   /*
   while(scanf("%[^\n]s",word) != EOF){
     printf("Your Name is: %s",word);
   }*/

   while(fgets(word, 100, stdin)!=EOF){
     printf("Your Name is: %s",word);
     printf("Enter your name: ");
     word = NULL;
   }
   return 0;
}
