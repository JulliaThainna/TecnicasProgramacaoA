#include <stdio.h>
void main (){
  int a[15], x[15];
  int i;
  int c=0;

  for (i=0;i<15;i++){
    printf ("Informe o %do. valor: ",i+1);
    scanf ("%d",&x[i]);

    if (x[i]%2==0){
      c=c+1;
    }
  }
  printf ("Foi digitado %d numeros pares!",c);
}
