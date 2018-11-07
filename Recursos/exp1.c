/* strtok.c */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 500

double strtodouble (char *array[MAX_LINE], int position){
    double num;
    char *ptr;

    ptr = strpbrk(array[position], ","); //retorna um ponteiro para a posição da string "," 
    if(ptr != NULL)   *ptr = '.';          //faz a substituição da ',' por '.'  
    num = atof(array[position]);       //converte string para float printf("num = %f", num);

    return num;

}

int main(void)
{

    char sFrase[]="1337-000/2018 01/10/2018 KI BARATO MERCEARIA DE DESCONT SECRETARIA DA CAMARA SECRETARIA DA CAMARA AÇÃO LEGISLATIVA Dispensa - Isento Compras e Serviços 343,50 343,40 343,30";
    int count = 0;
    char *p = strtok(sFrase, " ");
    char *array[500];
    //float valor = atof(*array);
    char *ptr;
    double num1, num2, num3;

    while (p)
    {
      array[count] = p;

      p = strtok (NULL, " ");

      count++;
    }

    //printf("%s\n", array[cont-1]);
    //printf("%s\n", array[cont-2]);
    //printf("%s\n", array[cont-3]);   

    //array[cont-3] = 343,50
    //ptr=array[cont-3][3]

    num1 = strtodouble(array, count-3);
    printf("\nESTE É O VALOR EMPENHADO --> %2.2f", num1 );

    num2 = strtodouble(array, count-2);
    printf("\nESTE É O VALOR LiQUIDADO --> %2.2f", num2 );

    num3 = strtodouble(array, count-3);
    printf("\nESTE É O VALOR PAGO --> %2.2f\n", num3 );
   
   return 0;
}



