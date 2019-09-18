#include <stdlib.h>

int mystrlen(char *str){
    int i, len = 0;
    for (i = 0; str[i] != '\0'; i++){
      len++;
    }

    return len;
}

void mystradd(char * origin, char * addition){

  int i, j;
  i =mystrlen(origin);
  for (j=0;addition[j]!='\0';j++){
    i = i +j;
    origin[i]=addition[j];
  }
  //origin[mystrlen(origin)-1]='\0';

}

int mystrfind(char *origin, char *substr){

  int i, j, lenO, lenS;

  lenO = mystrlen(origin);
  lenS = mystrlen(substr);

  for (i = 0; i<lenO; i++){
    for (j = 0; j<lenS; j++){
      if(origin[i+j]!=substr[j]){
        break;
      }
      if(j==lenS-1){
        return 1;
      }
    }
  }

    return 0;
}
