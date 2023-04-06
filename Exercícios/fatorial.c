#include <stdio.h>
void main ()
{
  int n;
  int f=1;

  printf ("   FATORIAL   ");
  printf ("\nInforme um valor: ");
  scanf ("%d",&n);
  if (n==0)
    printf("\n0");
  else
    while (n >= 1)
    {
      if (n==1)
        printf("%d",n );
      else
        printf ("%d x ",n);
        f=f*n;
        n=n-1;
    }
    printf("= %d\n",f);
}
