/*
 *
 * Empenho Data Emissão Fornecedor Unidade Orcamentária Unidade Executora Programa Modalidade Processo Valor Empenhado Valor Liquidado Valor Pago
 * CÂMARA MUNICIPAL DE RIO CLARO
 * 1461-000/2018 29/10/2018 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char size[] = "1461-000/2018 29/10/2018 ";
    char ch;
    float sum = 0;
    float aux_sum = 0;
    float avg = 0;
    int i;
    int j;

    /* Defining and Attributing Matrix */
    float sales[3][3] = {1, 2, 3, 4, 4, 5, 6, 4, 8};

    /* Reading position by position */
    for(i = 0; i < 3; i++) /* Lines */
    {
        for(j = 0; j < 3; j++) /* Columns */
        {
            printf("\t%2.2f", sales[i][j]); /* Printing Matrix position by position */ 
        }
            printf("\n"); /* Doing go to downline*/
    }

    /* Doing sum position by position */
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            sum = sum + sales[i][j];
        }
        
    }

    /* Doing sum only first line */
    for(j = 0; j < 3; j++)
    {
        aux_sum = aux_sum + sales[0][j];
    }
    
    
    avg = sum/9;
    printf("\nAverage is %f\n ", avg);
    printf("\n%f", aux_sum);



    /* Testing Array */
/*
    for (i = 0; i < strlen(size); i++)
    {
        ch = size[i];
        printf("%c", ch);
    }
    printf("\n\t%ld\n", strlen(size));
*/

    return 0;
}
