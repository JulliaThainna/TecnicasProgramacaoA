#include <stdio.h>
#include <string.h>

typedef struct{
  char nome[20];
  int pontos;
}Pontos;

void bubbleSorting(Pontos jogadores[], int n){
  Pontos aux;
  for(int i=0; i < n; i++){
    for(int j=i; j < n; j++){
      if(jogadores[j].pontos > jogadores[i].pontos){
        aux = jogadores[i];
        jogadores[i] = jogadores[j];
        jogadores[j] = aux;
      }
    }
  }
}

int main(){
  Pontos jogadores[10];
  Pontos jogador;
  printf("Nome player: ");
  scanf(" %[^\n]s",jogador.nome);
  printf("Pontuacao: ");
  scanf("%d",&jogador.pontos);
  FILE* blocoDeNotasPontos = NULL;
  blocoDeNotasPontos = fopen("score.txt","r");
  for(int i=0; i < 10; i++){
    fscanf(blocoDeNotasPontos,"%s - %d\n",jogadores[i].nome,&jogadores[i].pontos);
  }
  fclose(blocoDeNotasPontos);
  if(jogadores[9].pontos < jogador.pontos){
    strcpy(jogadores[9].nome, jogador.nome);
    jogadores[9].pontos = jogador.pontos;
  }
  bubbleSorting(jogadores,10);
  blocoDeNotasPontos = fopen("score.txt","w");
  for(int i=0; i < 10; i++){
    fprintf(blocoDeNotasPontos,"%s - %d\n",jogadores[i].nome,jogadores[i].pontos);
  }
  fclose(blocoDeNotasPontos);
  return 0;
}
