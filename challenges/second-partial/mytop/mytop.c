#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>



void clear();
void getData();
int getDir();
void getFirst();

void getValues(char *id){
  char dir[64], tmp[128];
  FILE *file;
  strcpy(dir,"/proc/");
  strcat(dir,id);
  strcat(dir,"/stat");

  unsigned int parent,thread,open,i;
  file=fopen(dir,"r");
  if(file==NULL){
    printf("ERROR IN PATH");
    exit(-1);
  }

  fgets(tmp,128,file);
  char *name, *state, *memo, *line;
  line =strtok(tmp," ");

  while(line!=NULL){
    switch (i) {
      case 1:
        name=line;
        break;
      case 2:
        switch(line[0]){
            case 'S':
                state="Sleeping";
                break;
            case 'T':
                state="Stopped";
                break;
            case 'I':
                state="Idle";
                break;
            default:
                state="Running";
                break;
      }
      break;
    case 3:
      parent=atoi(line);
      break;
    case 19:
      thread=atoi(line);
      break;
    case 22:
      memo=line;
      break;
  }
  line=strtok(NULL," ");
  i+=1;

}
fclose(file);
int fnames=getDir(id);
printf("|%10s |%15d |%40s |%20s |%25s |%10d |%10d |\n",id,parent,name,state,memo,thread,fnames);
}

int getDir(char *id){
    struct dirent *d;
    char dir[32];
    strcpy(dir,"/proc/");
    strcat(dir,id);
    strcat(dir,"/fd");

    DIR *dirInfo=opendir(dir);
    if(dirInfo==NULL){
      perror("error");
      exit(-1);
    }
    int nfiles=0;
    while((d=readdir(dirInfo)) != NULL){
        nfiles+=1;
    }
    closedir(dirInfo);
    return nfiles;
}

void printFirst(){
  struct dirent *d;
  DIR *dirInfo;
    dirInfo = opendir("/proc");
    if(dirInfo==NULL){
      perror("error");
      exit(-1);
    }
    printf("|%10s |%15s |%40s |%20s |%25s |%10s |%10s |\n","PID","PARENT","NAME","STATUS","MEMORY","THREADS","OPEN FILES");
    while ((d = readdir(dirInfo)) != NULL) {
      if(isdigit(*d->d_name)){
        getValues(d->d_name);
      }
    }
    closedir(dirInfo);
}




int main(){
  // Place your magic here
  while(1){
      printFirst();
      sleep(1);
      clear();
  }
}

void clear() {
  printf("\e[1;1H\e[2J");
}
