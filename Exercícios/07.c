#include <stdio.h>

int umaDiag(int m[4][4]){
  int soma = 0;
  for(int i=0; i < 4; i++){
    for(int j=0; j < 4; j++){
      if(i < j){
        soma += m[i][j];
      }
    }
  }
  return soma;
}

int duasDiag(int m[4][4]){
  int soma = 0;
  for(int i=0; i < 4; i++){
    for(int j=0; j < 4; j++){
      if(i < j && j < 3-i){
        soma += m[i][j];
      }
    }
  }
  return soma;
}

int main(){
  int m[4][4];
  for(int i=0; i < 4; i++){
    for(int j=0; j < 4; j++){
      printf("De o valor [%d][%d]: ",i,j);
      scanf("%d",&m[i][j]);
    }
  }
  printf("SOMA: %d", umaDiag(m));
  printf("\n\nSOMA: %d", duasDiag(m));
  return 0;
}
//como pegar endereco do vetor em outra posicao?
