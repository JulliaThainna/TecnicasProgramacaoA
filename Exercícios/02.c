#include <stdio.h>
#include <windows.h>
#include <string.h>

typedef struct{
  float peso;
  float preco;
  char recheio[30];
  char cobertura[30];
  char sabor[30];
}Bolo;

int adicionaBolo(Bolo bolo[5]){
  char resp, senhaAdm[14];
  int i=0;
  printf("DIGITE A SENHA: ");
  scanf(" %[^\n]s",senhaAdm);
  if(strcmp (senhaAdm, "bolinhogostoso") != 0){
    printf("\nAqui e a area de funcionarios! \nSenha Incorreta!\n");
  }
  else{
    printf("\nCONFEITARIA BOLO-BOLINHO\n");
    printf("--------------------------\n");
    printf("Sistema de Administracao\n\n");
    printf(" Adicionar Bolinhos :)\n\n");
    do{
        printf("\nSABOR: ");
        scanf(" %[^\n]s",bolo[i].sabor);
        printf("RECHEIO: ");
        scanf(" %[^\n]s",bolo[i].recheio);
        printf("COBERTURA: ");
        scanf(" %[^\n]s",bolo[i].cobertura);
        printf("PESO: ");
        scanf(" %f",&bolo[i].peso);
        printf("PRECO: ");
        scanf(" %f",&bolo[i].preco);
        i++;
        if(i < 4){
          printf("\nDeseja continuar adicionando bolinhos?[Y/N]: ");
          scanf(" %c",&resp);
        }
    }while((resp == 'Y') && (i < 4));
  }
  return 0;
}

int procuraBolo(Bolo bolo[5]){
  int op;
  char tipoC[30];
  float tipoN;
  printf(" CONFEITARIA BOLO-BOLINHO\n");
  printf("--------------------------\n");
  printf("Area do cliente\n BEM-VINDO(A)!\n");
  printf("Procurar Bolinhos :)\n\n");
  printf("CATEGORIAS DE PROCURA: ");
  printf("\n1 - SABOR");
  printf("\n2 - RECHEIO");
  printf("\n3 - COBERTURA");
  printf("\n4 - PESO");
  printf("\n5 - PRECO");
  printf("\nOPCAO: ");
  scanf("%d",&op);
  system("cls");
  switch(op){
    case 1:
      printf("SABOR: ");
      scanf(" %[^\n]s",tipoC);
      for(int i=0; i < 5; i++){
        if(strcmp(tipoC, bolo[i].sabor) == 0){
          printf("%s %s %s %f %f\n\n",bolo[i].sabor,bolo[i].recheio,bolo[i].cobertura,bolo[i].peso,bolo[i].preco);
        }
      }
      break;
    case 2:
      printf("RECHEIO: ");
      scanf(" %[^\n]s",tipoC);
      break;
    case 3:
      printf("COBERTURA: ");
      scanf(" %[^\n]s",tipoC);
      break;
    case 4:
      printf("PESO: ");
      scanf("%f",&tipoN);
      break;
    case 5:
      printf("PRECO: ");
      scanf("%f",&tipoN);
      break;
  }
  return 0;
}

int menu(Bolo bolo[5]){
  int op;
  printf("\t    MENU\n");
  printf("\t-----------\n\n");
  printf("1 - Visualizar os bolos disponiveis\n");
  printf("2 - Adiministracao\n");
  printf("OPCAO: ");
  scanf("%d",&op);
  if(op == 1){
    system("cls");
    procuraBolo(bolo);

  }
  else if(op == 2){
    system("cls");
    adicionaBolo(bolo);
  }
  return 0;
}


int main(){
  Bolo bolo[5];
  while(1){
    menu(bolo);
  }

  return 0;
}
