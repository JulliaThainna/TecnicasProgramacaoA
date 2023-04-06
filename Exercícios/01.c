#include <stdio.h>
#include <math.h>
int main(){
  int n;
  printf("De um valor: \n");
  scanf("%d",&n);
  if(n <= 0){
    printf("ERRO");
  }
  else if(n >= 1){
    printf("1 1 1\n");
    printf("1 2 2\n");
  }
  if(n > 1){
    for(int i=1; i < n; i++){
      printf("%g ",pow(i+1,1));
      printf("%g ",pow(i+1,2));
      printf("%g\n",pow(i+1,3));
      printf("%g ",pow(i+1,1));
      printf("%g ",pow(i+1,2)+1);
      printf("%g\n",pow(i+1,3)+1);
  }
}
  return 0;
}
