/*Fazer um programa que leia dois valores e multiplique-os (utilize uma função)*/
#include <stdio.h>

//Duas funções para testar os tipos de funções que funcionam para mostrar o resultado, sendo que achei a segunda mais eficiente
int multiplicaValor(int v1, int v2, int *result){
  *result = v1 * v2;
  //foi passado o endereço de result, então o ponteiro *result, está apontando para o endereço de result, logo, vai ser trocado seu conteúdo
  //se estivesse result = v1 * v2 sem o asterisco, então, result consideraria que v1*v2 é o seu endereço, além de ter erro de sintaxe por faltar
  //o asterisco e causar warning no programa
  return *result;
}

void multiplicaValorDois(int v1, int v2){ //tanto faz usar void ou int->return 0;
  v1 = v2 * v1;
  printf("\nRESULTADO: %d",v1);
}

int main(){
  int n1,n2;
  int result;
  printf("De o 1o valor: ");
  scanf("%d",&n1);
  printf("De o 2o valor: ");
  scanf("%d",&n2);
  multiplicaValor(n1,n2, &result);
  printf("RESULTADO: %d",result);
  multiplicaValorDois(n1,n2);
  return 0;
}
