#include <stdio.h>

int fat(int n){
  if(n == 1){
    return 1;
  }
  return n * fat(n-1);
}

/*fat(4)
4 * 3 * 2 * 1
ou seja,
5 * 4
4 * 3
3 * 2
2 * 1
*/

int main(){
  int n;
  printf("De um valor: ");
  scanf("%d",&n);
  printf("Fatorial de %d = %d",n,fat(n));
  return 0;
}
