#include <stdio.h>
int main(){
  int m[2][2], op[2][2] = {0};
  int n[2][2];
  for(int i=0; i < 2; i++){
    for(int j=0; j < 2; j++){
      printf("Elemento matriz A [%d][%d]: ",i,j);
      scanf("%d",&n[i][j]);
      printf("Elemento matriz B [%d][%d]: ",i,j);
      scanf("%d",&m[i][j]);
    }
  }
  for(int i=0; i < 2; i++){
    for(int j=0; j < 2; j++){
      for(int k=0; k < 2; k++){
        //op[i][j] = n[i][0]*m[0][j] + n[i][1]*m[1][j];
        op[i][j] += n[i][k]*m[k][j];
      }
    }
  }
  for(int i=0; i < 2; i++){
    for(int j=0; j < 2; j++){
      printf("%d ",op[i][j]);
    }
    printf("\n");
  }
  return 0;
}
