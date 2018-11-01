#include <stdio.h>
#include <stdlib.h>
#include "func_basica.h" /* Header que chamas funcoes nos arquivos externos (*.c) */

int main()
{
    int a, b;
    float resultado;
    
    system("clear");
    printf("\n\n\tProgarma MAIN que chama Funcoes Externas");
    printf("\n\tAs Funcoes Externas executam as 4 Operacoes Basicas da Matematica");
    printf("\n\tExiste uma Funcao Somar, Subtrair, Multiplicar e Dividir");
    printf("\n\tAs Operacoes serao realizadas entre [a] e [b], onde estes devem ser Inteiros");

    printf("\n\n\tEntre com Numero [a]: ");
    scanf("%d", &a);
    printf("\n\tEntre com Numero [b]: ");
    scanf("%d", &b);

    resultado = somar(a, b);
    printf("\n\t\tResultado: a(%d) + b(%d) = (%4.2f)", a, b, resultado);
    resultado = subtrair(a, b);
    printf("\n\t\tResultado: a(%d) - b(%d) = (%4.2f)", a, b, resultado);
    resultado = multiplicar(a, b);
    printf("\n\t\tResultado: a(%d) * b(%d) = (%4.2f)", a, b, resultado);
    resultado = dividir(a, b);
    printf("\n\t\tResultado: a(%d) / b(%d) = (%4.2f)", a, b, resultado);

    printf("\n\n");

    return 0;
}

