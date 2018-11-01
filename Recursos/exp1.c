/* strtok.c */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 
int main(void)
{

    char sFrase[]="1337-000/2018 01/10/2018 KI BARATO MERCEARIA DE DESCONT SECRETARIA DA CAMARA SECRETARIA DA CAMARA AÇÃO LEGISLATIVA Dispensa - Isento Compras e Serviços 343,50 343,40 343,30";
    int cont = 0;
    char *p = strtok(sFrase, " ");
    char *array[500];

    while (p)
    {
      array[cont] = p;

      p = strtok (NULL, " ");

      cont++;
    }

    printf("%s\n", array[cont-1]);
    printf("%s\n", array[cont-2]);
    printf("%s\n", array[cont-3]); 
   
   return 0;
}