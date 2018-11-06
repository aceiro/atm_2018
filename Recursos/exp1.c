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
    //float valor = atof(*array);
    char *ptr;
    float num, media;

    while (p)
    {
      array[cont] = p;

      p = strtok (NULL, " ");

      cont++;
    }

    //printf("%s\n", array[cont-1]);
    //printf("%s\n", array[cont-2]);
    //printf("%s\n", array[cont-3]);

    ptr = strpbrk(array[cont-3], ","); //retorna um ponteiro para a posição da string "," 
    if(ptr != NULL)   *ptr = '.';          //faz a substituição da ',' por '.'  
    num = atof(array[cont-3]);       //converte string para float printf("num = %f", num);

    printf("\nESTE É O VALOR EMPENHADO --> %s", array[cont-3] );

    ptr = strpbrk(array[cont-2], ","); //retorna um ponteiro para a posição da string "," 
    if(ptr != NULL)   *ptr = '.';          //faz a substituição da ',' por '.'  
    num = atof(array[cont-2]);       //converte string para float printf("num = %f", num);

    printf("\nESTE É O VALOR LiQUIDADO --> %s", array[cont-2] );

    ptr = strpbrk(array[cont-1], ","); //retorna um ponteiro para a posição da string "," 
    if(ptr != NULL)   *ptr = '.';          //faz a substituição da ',' por '.'  
    num = atof(array[cont-1]);       //converte string para float printf("num = %f", num);

    printf("\nESTE É O VALOR PAGO --> %s\n", array[cont-1] );
   
   return 0;
}



