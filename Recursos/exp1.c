/* strtok.c */
 
#include <stdio.h>
#include <string.h>
 
int main(void)
{
   char *psRetorno;
   char sFrase[]="1337-000/2018 01/10/2018 KI BARATO MERCEARIA DE DESCONT SECRETARIA DA CAMARA SECRETARIA DA CAMARA AÇÃO LEGISLATIVA Dispensa - Isento Compras e Serviços 343,50 343,50 343,50";
   int cont = 0;
   int aux_cont = 0;
   char *pago;
   //char acum[][];
   //printf("\nFrase = %s", sFrase);
 
   /* Primeira pesquisa por espaço em branco. */
   psRetorno = strtok(sFrase, " ");
 
  // printf("\nRetorno = %s", psRetorno);
  //printf("\nFrase = %s", sFrase);
 
   do
   {
      /* Nas próximas chamadas, deve-se passar um ponteiro “nulo”. 
         Isto “indica” para a função que a pesquisa deve continuar 
         no ponteiro anterior. */
      psRetorno = strtok('\0', " "); //Demais pesquisas por , (vírgula) ou espaço em branco.
 
      /* Um valor nulo (NULL) é considerado sempre falso em comparações 
         booleanas (verdadeiro ou falso). */
      if(psRetorno)
      {
      cont++;
      aux_cont++;
         //if (cont > (cont -3))
         printf(" %s", psRetorno);
      } 
   } while(psRetorno == cont -3);
   printf("\n%d\n", cont);
   
   return 0;
}