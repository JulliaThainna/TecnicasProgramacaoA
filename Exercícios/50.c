#include <stdio.h>
void main (){
  int n;
  int aux;
  int c;
  int i;

  printf("Havera quantos valores na sequencia de decrescentes?: ");
  scanf ("%d",&n);
  int x[n];
  for (i=0;i<n;i++){
    printf ("Informe o %do. valor: ",i+1);
    scanf ("%d",&x[i]);

  }
  for (c=0; c<n; c++){
    for (i=0; i<n; i++){
      if (x[i] < x[i+1]){
        aux = x[i];
        x[i] = x[i+1];
        x[i+1]= aux;
      }
    }
  }
  for (i=0; i<n; i++){
    printf ("%4d",x[i]);
  }
  printf ("\n");
}
