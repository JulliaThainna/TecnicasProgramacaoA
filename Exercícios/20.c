#include <stdio.h>
#include <math.h>
void main (){
  int a;
  int b;
  int c;
  int delta;
  int x1;
  int x2;

  printf ("BHASKARA");
  printf ("\nInforme um numero: ");
  scanf ("%d",&a);
  printf ("\nInforme um numero: ");
  scanf ("%d",&b);
  printf ("\nInforme um numero: ");
  scanf ("%d",&c);

  delta = (pow(b,2)-4)*a*c;

  if (delta>=0){
    delta = sqrt (delta);
    x1= (-b + delta)/(2*a);
    x2= (-b + delta)/(2*a);
    printf("\nResultado: x1 = %d, x2 = %d",x1,x2);
  }
  else
      if (delta < 0){
        printf ("NAO HA RAIZES DE VALORES NEGATIVOS!");
      }
  }
