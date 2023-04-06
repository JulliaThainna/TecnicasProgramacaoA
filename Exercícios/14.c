#include <stdio.h>
void main ()
{

  int n;
  int t1=1;
  int t2=1;
  int c=1;

  printf ("   SEQUENCIA DE FIBONACCI   ");
  printf("\nInforme quantos termos havera na sequencia: ");
  scanf("%d",&n);

  if (n==1)
    printf("%d",t1);
  else
    if (n==0)
      printf("INDETERMINADO!");
    else
      if (n>1){
        n=n-1;
        printf("%d,",t1);
        while (c<=n){
          printf ("%d",t1);
          t1=t2+t1;
          t2=t1-t2;
          c=c+1;
          if (c<=n)
            printf (",");
        }
      }
}
