#include <stdio.h>

typedef struct{
  char sabor[15];
  float preco, peso;
}Bolinho;

int main(){
  Bolinho bolo[5];
  Bolinho copiaBolo[5];
  FILE* arquivoBolinho = NULL;
  for(int i=0; i < 5; i++){
    printf("Sabor do bolinho: ");
    scanf(" %[^\n]s",bolo[i].sabor);
    printf("\nPreco do bolinho: ");
    scanf("%f",&bolo[i].preco);
    printf("\nPeso do bolinho: ");
    scanf("%f",&bolo[i].peso);
  }
  arquivoBolinho = fopen("arquivo.bin","rb");
  if(arquivoBolinho == NULL){
    printf("O arquivo nao existe\n");
    printf("O arquivo sera criado...\n");
    fclose(arquivoBolinho);
    arquivoBolinho = fopen("arquivo.bin","wb");
    printf("Arquivo criado com sucesso!\n");
  }
  fclose(arquivoBolinho);
  arquivoBolinho = fopen("arquivo.bin","ab");
  for(int i = 0; i < 5; i++){
    fwrite(&bolo[i],sizeof(Bolinho),1,arquivoBolinho);
  }
  fclose(arquivoBolinho);
  arquivoBolinho = fopen("arquivo.bin","rb");
  for(int i = 0; i < 5; i++){
    fread(&copiaBolo[i],sizeof(Bolinho),1,arquivoBolinho);
    printf("BOLINHO %i\n",i);
    printf("SABOR DO BOLINHO: %s\n",copiaBolo[i].sabor);
    printf("PRECO DO BOLINHO: %f\n",copiaBolo[i].preco);
    printf("PESO DO BOLINHO: %f\n",copiaBolo[i].peso);
  }
  fclose(arquivoBolinho);
  return 0;
}
