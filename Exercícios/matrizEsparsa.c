#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  int num;
  int coluna;
  struct elemento* prox;
}No;

typedef No* Pointer;

typedef struct{
  Pointer *A;
  int linhas;
  int colunas;
}MEsparsa;


//Registros
int iniciaMatriz(MEsparsa* m, int l, int c);
int adicionaElemento(MEsparsa* m, int l, int c, int valor);
int buscaElemento(MEsparsa* m, int l, int c);
void mostraMatriz(MEsparsa* m);
void deletaMatriz(MEsparsa* m);


int main(){
  MEsparsa matriz;
  int linha, coluna, op;
  printf("Insira a linha: ");
  scanf("%d",&linha);
  printf("\nInsira a coluna: ");
  scanf("%d",&coluna);
  iniciaMatriz(&matriz,linha,coluna);
  while(1){
    printf("\n\tMenu\t\n");
    printf("1 - Adionar elemento na matriz\n");
    printf("2 - Buscar elemento na matriz\n");
    printf("3 - Mostrar a matriz\n");
    printf("4 - Deletar a matriz\n");
    printf("5 - Sair\n");
    printf("OPCAO: ");
    scanf("%d",&op);
    int v;
    switch(op){
      case 1:
        printf("Linha da matriz: ");
        scanf("%d",&linha);
        printf("\nColuna da matriz: ");
        scanf("%d",&coluna);
        printf("\nElemento que deseja adicionar a matriz: ");
        scanf("%d",&v);
        adicionaElemento(&matriz,linha,coluna,v);
        break;
      case 2:
        printf("Linha da matriz: ");
        scanf("%d",&linha);
        printf("Coluna da matriz: ");
        scanf("%d",&coluna);
        int resultado = buscaElemento(&matriz, linha, coluna);
        printf("Elemento encontrado: %d",resultado);
        break;
      case 3:
        mostraMatriz(&matriz);
        break;
      case 4:
        deletaMatriz(&matriz);
        break;
      default:
        return 0;
    }
  }
  return 0;
}

int iniciaMatriz(MEsparsa* m, int l, int c){
  int i;
  m->linhas = l;
  m->colunas = c;
  if(l <= 0 || c <= 0){
    return 0;
  }
  m->A = (Pointer*) malloc(sizeof(Pointer) * l);
  for(i=0;i<l;i++) m->A[i] = NULL;
  return 1;
}
int adicionaElemento(MEsparsa* m, int l, int c, int valor){
  if(l < 0 || l >= m->linhas || c < 0 ||c >= m->colunas){
    return 0;
  }
  Pointer ant = NULL;
  Pointer aux = m->A[l];
  while(aux != NULL && aux->coluna < c){
    ant = aux;
    aux = aux->prox;
  }
  if(aux != NULL && aux->coluna == c){
    if(valor == 0){
      if(ant == NULL){
        m->A[l] = aux->prox;
      }
      else ant->prox = aux->prox;
      free(aux);
    }
    else aux->num = valor;
  }
  else if(valor != 0){
    Pointer aux2 = (Pointer) malloc(sizeof(No));
    aux2 ->coluna = c;
    aux2->num = valor;
    aux2->prox = aux;
    if(ant == NULL){
      m->A[l] = aux2;
    }
    else ant->prox = aux2;
  }
  return 1;
}
int buscaElemento(MEsparsa* m, int l, int c){
  if(l < 0 || l >= m->linhas || c < 0 ||c >= m->colunas){
    return 0;
  }
  Pointer aux = m->A[l];
  while(aux != NULL && aux->coluna < c){
    aux = aux->prox;
  }
  if(aux != NULL && aux->coluna == c){
    return aux->num;
  }
  return 0;
}
void mostraMatriz(MEsparsa* m){
  for(int i = 0; i < m->linhas; i++){
    for(int j = 0; j < m->colunas; j++){
      printf("%d ", buscaElemento(m, i, j));
    }
    printf("\n");
  }
}
void deletaMatriz(MEsparsa* m){
  Pointer aux;
  Pointer ant;
  for(int i = 0; i < m->linhas; i++){
    aux = m->A[i];
    while(aux != NULL){
      ant = aux;
      aux = aux->prox;
      free(ant);
    }
    free(m->A[i]);
  }
  free(m->A);
  printf("Matriz deletada!");
}
