#include <stdio.h>
#include <string.h>
  int main (){
    int i,j;
    struct times{
      char nome[30];
    };
    struct times time[3];
    for (i=0;i <3;i++){
      printf ("INFORME O %d o. TIME: ",i+1);
      scanf ("%s",time[i].nome);
    }
    for (j=0;j<3;j++){
      for (i=0;i <3;i++){
        if(strcmp(time[j].nome, time[i].nome) != 0){
          printf("%s x %s\n",time[j].nome,time[i].nome );
        }
      }
    }
    return 0;
  }
