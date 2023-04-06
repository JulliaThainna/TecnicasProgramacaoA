#include <stdio.h>


//base^expoente = base * base^expoente-1


/*
2^6 = 2 * 2 * 2 * 2 * 2 * 2 * 1
2^5 = 2 * 2 * 2 * 2 * 2 * 1
2^4 = 2 * 2 * 2 * 2 * 1
2^3 = 2 * 2 * 2 * 1
2^2 = 2 * 2 * 1
2^1 = 2 * 1
2^0 = 1
*/

/*
5*5 = 5 + 5*4
5*4 = 5 + 5*3
5*3 = 5 + 5*2
5*2 = 5 + 5*1
5*1 = 5 + 5*0
5*0 = 0
*/

/*
fib(n) = fib(n-1) + fib(n-2)
fib(0) = 1
fib(1) = 1
*/

int potencia(int base, int expoente){
  if(expoente == 0){
    return 1;
  }
  return base * potencia(base,expoente-1);
}

int multiplicacao(int multiplicando, int multiplicador){
  if(multiplicador == 0){
    return 0;
  }
  return multiplicando + multiplicacao(multiplicando, multiplicador-1);
}

int fib(int n){
  if(n == 1 || n == 0){
    return 1;
  }
  return fib(n-1) + fib(n-2);
}


int main(){
  int a,b;
  printf("Multiplicando: ");
  scanf("%d",&a);
  printf("Multiplicador: ");
  scanf("%d",&b);
  printf("\nRESULTADO: %d x %d = %d",a,b,multiplicacao(a,b));
  printf("\n\n %d",fib(a));
  return 0;
}
