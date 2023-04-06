#include <stdio.h>
int main (){
  int n;
  int n1 = 1;
  int n2 = 0;
  int c;
      printf ("              SEQUENCIA DE FIBONACCI\n");
      printf("              ......................\n");
      printf ("\nINFORME QUANTOS TERMOS HAVERA NA SEQUENCIA: ");
      scanf ("%d",&n);
      for (c=0;c<=n;c++){
        printf ("\n  %d",n1);
        n1 = n1 + n2;
        n2 = n1 - n2;
      }
    getch ();
    return 0;
}
