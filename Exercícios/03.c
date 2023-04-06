#include <stdio.h>
#include <windows.h>

typedef struct{
    char nomeCandidato[30];
    char cargoPretendido[30];
    char nomePresidenteAtual[30];
    int anoEleicao;
}CargoIEEE;

int cadastraCandidato(CargoIEEE pessoa[5]){
  for(int i=0; i < 5; i++){
    printf("\n CADASTRO CANDIDATO %d\n",i+1);
    printf("----------------------");
    printf("\nNOME DO CANDIDATO: ");
    scanf(" %[^\n]s",&pessoa[i].nomeCandidato);
    printf("\nCARGO PRETENDIDO: ");
    scanf(" %[^\n]s",&pessoa[i].cargoPretendido);
    printf("\nPRESIDENTE ATUAL: ");
    scanf(" %[^\n]s",&pessoa[i].nomePresidenteAtual);
    printf("\nANO DA ELEICAO: ");
    scanf(" %d",&pessoa[i].anoEleicao);
  }
  return 0;
}

int mostraCandidato(CargoIEEE pessoa[5]){
  for(int i=0; i < 5; i++){
    printf("\n FICHA CANDIDATO %d\n",i+1);
    printf("-------------------\n");
    printf("NOME: %s\n", pessoa[i].nomeCandidato);
    printf("CARGO: %s\n",pessoa[i].cargoPretendido);
    printf("ANO DA ELEICAO: %d \n\n",pessoa[i].anoEleicao);
  }
  return 0;
}

int main(){
  CargoIEEE pessoa[5];
  cadastraCandidato(pessoa);
  system("cls");
  mostraCandidato(pessoa);
  return 0;
}
