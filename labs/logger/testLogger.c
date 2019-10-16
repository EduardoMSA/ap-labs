#include <stdio.h>


int main() {
  int i = 101;
  infof("Información General Número %d \n", i);
  char* w = "ALERTA";
  warnf("%s \n",w);
  char* e = "CRASH";
  errorf("%s \n",e);
  char* p = "¡PANICO!";
  panicf("%s \n", p);


  return 0;
}
