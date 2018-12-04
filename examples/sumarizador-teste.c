#include <stdio.h>
#include "sumarizador.h"

int main(){
  /* http://www.icosaedro.it/c-modules.html */	 


  printf("T E S T -- calcula_media() -- \n");
  float result   = calcula_media(10.0, 10.0);
  float expected = 10.0;

  /* verifica se o resultado é igual ao esperado */
  if( result == expected ) {
	printf("SUCCESS -- RESULTADOS SÃO IGUAIS");
  }else{
	printf("FAIL! -- OS RESULTADOS SÃO DIFERENTES\n");
	printf("%f != %f", result, expected); 
  }

  return 0;


}
