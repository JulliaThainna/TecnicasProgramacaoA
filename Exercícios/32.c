#include<stdio.h>
void main ()
{

int x[30];
int a[30];
int b[30];
int i;

for (i=0; i<5; i++)
{
  printf ("De um numero: ");
  scanf ("%d",&x[i]);
}
  for (i=0; i<5; i++)
  {
    if (x[i]%2==0)
    {
      printf("Os numeros pares sao: %d\n",x[i]);
    }
    else
    {
      printf("Os numeros impares sao %d\n",x[i]);
    }
  }
}
