#include <stdio.h>
#include <string.h>

int main(){
  char resultado[30] = " ";
  FILE *informacao = NULL;
  char nome[30];
  float  altura, peso, imc;
  printf("Informe seu nome: ");
  scanf(" %[^\n]s",nome);
  printf("Informe sua altura: ");
  scanf("%f",&altura);
  printf("Informe seu peso: ");
  scanf("%f",&peso);
  imc = peso/(altura*altura);
  informacao = fopen("imc.txt","r");
  if(informacao == NULL){
    printf("O arquivo nao existe");
    printf("\nO arquivo sera criado...\n");
    fclose(informacao);
    informacao = fopen("imc.txt","w");
    printf("Arquivo criado com sucesso\n");
  }
  fclose(informacao);
  informacao = fopen("imc.txt","a");
  fprintf(informacao,"%s - %f - ",nome,imc);
  printf("\nInformacao guardada com sucesso");
  if(imc < 17){
    fprintf(informacao,"Muito abaixo do peso\n");
  }
  else if(imc >= 17 && imc < 18){
    fprintf(informacao,"Abaixo do peso\n");
  }
  else if(imc >= 18.5 && imc < 24.99){
    fprintf(informacao,"Peso normal\n");
  }
  else if(imc >= 25 && imc < 29.99){
    fprintf(informacao,"Acima do peso\n");
  }
  else if(imc >= 30 && imc < 34.99){
    fprintf(informacao,"Obesidade I\n");
  }
  else if(imc >= 35 && imc < 39.99){
    fprintf(informacao, "Obesidade II (severa)\n");
  }
  else{
    fprintf(informacao,"Obesidade III (morbida)\n");

  }
  fclose(informacao);
  informacao = fopen("imc.txt","r");
  fscanf(informacao,"%s - %f - %[^\n]s\n",nome, &imc, resultado);
  printf("Nome: %s - IMC: %f - Resultado: %s",nome,imc,resultado);
  char cursor;
  do{
    cursor = getc(informacao);
    printf("%c",cursor);
  }while(cursor != EOF);
  fclose(informacao);
return 0;
}
