#include <stdio.h>
#include <stdlib.h>
int main (){
  int n;
  int c;

  printf ("Digite um numero: ");
  scanf ("%d",&n);
  for (c=n;c<=1;n--){
    printf ("%d",n);
  }
    for (c=1;c<=n;c++){
      printf ("%d",c);
    }


  return 0;
}
