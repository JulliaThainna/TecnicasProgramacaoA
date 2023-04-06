#include <stdio.h>
int main(){
  char vet[10];
  printf("%p",vet);
  printf("\n%d",vet);
  printf("\n%p",&vet[1]);
  //o nome "vet" aponta para &v[0], se for usado %p ou %d para ver o endereço de vet[1], é possível
  //visualizar que é sequencial

  int n=15;
  int *p = &n;
  printf("\n %d",p); //endereço que p guarda, ou seja, o endereço de n
  printf("\n %d", *p); //conteúdo para onde p está apontando, ou seja, se p está apontando para o endereço de n e n guarda um int==15, então será printado 15.

  //funciona com vetores tambem, mas, não precisa do & pois vet já um vetor (guarda endereço)
  char *testeVet = vet;
  printf("\n %d",testeVet);
  printf("\n %d",*testeVet);
  return 0;
}

/*
#include <stdio.h>

void multiplicaValor(int valor1, int valor2, int *result){
  *result = valor1 * valor2;
}

int main(){
  int v1,v2,result;
  printf("valor 1: ");
  scanf("%d",&v1);
  printf("valor 2: ");
  scanf("%d",&v2);
  multiplicaValor(v1,v2,&result);
  printf("%d",result);
  return 0;
}
*/
