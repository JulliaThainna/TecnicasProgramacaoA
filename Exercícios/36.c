#include <stdio.h>
void main (){
  int x[50];
  int i;
  int aux;
  int c;

  for (i=0; i<50; i++){
    printf("Informe 50 valores: ");
    scanf ("%d",&x[i]);
  }
  for (c=0; c<50; c++){
    for (i=0; i<50; i++){
      if (x[i] < x[i+1]){
        aux = x[i];
        x[i] = x[i+1];
        x[i+1]= aux;
      }
    }
  }
  for (i=0; i <50; i++){
    printf ("%4d ",x[i]);
  }
  printf ("\n");
}
