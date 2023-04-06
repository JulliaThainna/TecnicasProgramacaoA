#include <stdio.h>
void main (){

 int num, i, resultado = 0;

 for (i = 100; i <= 110 / 2; i++) {
    if (num % i == 0) {

       resultado++;
       if (resultado == 0)
          printf("%d e um numero primo\n", num);
    }
 }
}
