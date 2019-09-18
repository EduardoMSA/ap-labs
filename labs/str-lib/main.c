#include <stdio.h>

int main(int argc, char **argv) {

    char * origin = (char*)malloc(100);
    char * addition = (char*)malloc(100);

    origin = argv[1];
    addition = argv[2];


    printf("Initial Lenght       : %d\n", mystrlen(origin));
    mystradd(origin,addition);
    printf("New String           : %s\n", origin);

    if(mystrfind(origin,argv[3])){
      printf("SubString was found  : yes\n");
    } else{
      printf("SubString was found  : no\n");
    }



    return 0;
}
