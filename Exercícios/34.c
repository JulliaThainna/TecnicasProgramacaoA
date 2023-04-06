#include<stdio.h>
void main ()
{
  int x[20];
  int i;
  int soma;

  for (i=0; i<20; i++)
  {
    printf ("Informe um valor: ");
    scanf ("%d",&x[i]);
    soma=x[i]+soma;
  }
  printf("%d\n",soma);
}
