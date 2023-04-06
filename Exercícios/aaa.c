#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  int info;
  struct elemento *prox;
}No;

No *adicionaElemento(No *inicio, int n);
No *imprimeLista(No *inicio);


int main(){
  No *inicio;
  inicio = NULL;
  inicio = adicionaElemento(inicio,4);
  inicio = adicionaElemento(inicio,5);
  inicio = imprimeLista(inicio);
  return 0;
}

No *adicionaElemento(No *inicio, int n){
  No *node = (No*)malloc(sizeof(No));
  node->info = n; //node->info = n //node->info = n
  if(inicio == NULL){
    inicio = node;
    node->prox = NULL;
    printf("adc");
    return inicio;
  }
  No *aux;
  aux = inicio;
  while(aux->prox != NULL){
    aux = aux->prox;
  }
  aux->prox = node;
  node->prox = NULL;
  printf("adc");
  return inicio;
}

No *imprimeLista(No *inicio){
  No *aux;
  aux = inicio;
  while(aux != NULL){
    printf("%d ",aux->info);
    aux = aux->prox;
  }
  return inicio;
}
