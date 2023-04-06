#include <stdio.h>
#include <string.h>

typedef struct{
  char reino[15], filo[15],
  classe[15], ordem[15], familia[15],
  genero[15], especie[15];
}Animais;

int adicionaAnimal(Animais *a1, Animais *a2){
  printf(" Adicionar animaizinhos :)\n");
  printf("---------------------------\n");
  printf("ANIMAL 1\n\n");
  printf("REINO: ");
  scanf(" %[^\n]s",a1->reino);
  printf("FILO: ");
  scanf(" %[^\n]s",a1->filo);
  printf("CLASSE: ");
  scanf(" %[^\n]s",a1->classe);
  printf("ORDEM: ");
  scanf(" %[^\n]s",a1->ordem);
  printf("FAMILIA: ");
  scanf(" %[^\n]s",a1->familia);
  printf("GENERO: ");
  scanf(" %[^\n]s",a1->genero);
  printf("ESPECIE: ");
  scanf(" %[^\n]s",a1->especie);

  printf("\n\n\nANIMAL 2\n\n");
  printf("REINO: ");
  scanf(" %[^\n]s",a2->reino);
  printf("FILO: ");
  scanf(" %[^\n]s",a2->filo);
  printf("CLASSE: ");
  scanf(" %[^\n]s",a2->classe);
  printf("ORDEM: ");
  scanf(" %[^\n]s",a2->ordem);
  printf("FAMILIA: ");
  scanf(" %[^\n]s",a2->familia);
  printf("GENERO: ");
  scanf(" %[^\n]s",a2->genero);
  printf("ESPECIE: ");
  scanf(" %[^\n]s",a2->especie);
  return 0;
}

int comparaAnimal(Animais *a1, Animais *a2){
  if(strcmp(a1->reino,a2->reino)==0){
    printf("REINO: %s",a1->reino);
  }
  if(strcmp(a1->filo,a2->filo)==0){
    printf("\nFILO: %s",a1->filo);
  }
  if(strcmp(a1->classe,a2->classe)==0){
    printf("\nCLASSE: %s",a1->classe);
  }
  if(strcmp(a1->ordem,a2->ordem)==0){
    printf("\nORDEM: %s",a1->ordem);
  }
  if(strcmp(a1->familia,a2->familia)==0){
    printf("\nFAMILIA: %s",a1->familia);
  }
  if(strcmp(a1->genero,a2->genero)==0){
    printf("\nGENERO: %s",a1->genero);
  }
  if(strcmp(a1->especie,a2->especie)==0){
    printf("\nESPECIE: %s",a1->especie);
  }
  if(strcmp(a1->reino,a2->reino)==0 && strcmp(a1->filo,a2->filo)==0 && strcmp(a1->classe,a2->classe)==0 && strcmp(a1->ordem,a2->ordem)==0
  && strcmp(a1->familia,a2->familia)==0 && strcmp(a1->genero,a2->genero)==0 && strcmp(a1->especie,a2->especie)==0){
    printf("\nOs dois sao identicos");
  }
  else{
    printf("\nSao dois animais MUITO distintos");
  }
  return 0;
}

int main(){
  Animais animal1, animal2;
  adicionaAnimal(&animal1, &animal2);
  comparaAnimal(&animal1, &animal2);
  return 0;
}
