#include <stdio.h>

void mudaValorPorCopia(int a, int b){
  a = 4;
  b = 5;
  printf("VALORES NA FUNCAO");
  printf("\n%d",a);
  printf("\n%d",b);
}

void mudaValorOriginal(int *c, int *d){
  *c = 10;
  *d = 20;
  printf("\n\nVALORES NA FUNCAO");
  printf("\n%d",*c);
  printf("\n%d",*d);
}

int main(){
  int a=2,b=3;
  int c=5,d=6;

  mudaValorPorCopia(a,b);
  printf("\n\nVALORES NA MAIN");
  printf("\n%d",a);
  printf("\n%d",b);

  mudaValorOriginal(&c,&d);
  printf("\n\nVALORES NA MAIN");
  printf("\n%d",c);
  printf("\n%d",d);
  return 0;
}
