#include <stdio.h>
typedef struct{
  int numeroDeParticipantes, numeroDeDesafios, desafiosAcertados;
  float nota;
}Hackathon;

float mostraNota(Hackathon time){
  printf("Numero de desafios: ");
  scanf("%d",&time.numeroDeDesafios);
  printf("Numero de desafios acertados: ");
  scanf("%d",&time.desafiosAcertados);
  time.nota = (float)time.desafiosAcertados/(float)time.numeroDeDesafios;
  return time.nota;
}

int main(){
  Hackathon time;
  printf("%f", mostraNota(time));
  return 0;
}
