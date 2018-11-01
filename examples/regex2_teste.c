/*
 * match2.c
 *
 * mostra quantas vezes a ER casou, quais partes da string
 * de entrada ela acasou...
 * 
 * argv[1] = expressão regular
 * argv[2] = entrada 
 *
 * ex: ./match2 '^er' 'string de entrada' 
 */

/* headers necessários */
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

/* mostra uma mensagem do erro usando regerror */
int er_error(int i, regex_t reg)
{
	size_t length;
	char *buffer=NULL;

	/* pega o tamanho da mensagen de erro */
	length = regerror (i, &reg, NULL, 0);

	/* aloca espaço para a mensagem de erro */
	if ((buffer = (char *)malloc (length)) == NULL) {
		fprintf(stderr, "error: malloc buffer\n");
		exit(1);
	}
	
	/* coloca em buffer a mensagem de erro */
	regerror (i, &reg, buffer, length);
	
	fprintf(stderr,"Erro: %s\n",buffer);
	free(buffer);
	exit(1);
}


/* tenta casar uma ER com o input */
void er_match(char *argv[])
{
	int i, start;
	int error;
	/* aloca espaço para a estrutura do tipo regmatch_t */
	regmatch_t match;
	/* aloca espaço para a estrutura do tipo regex_t */
	regex_t reg;

	/* compila a ER passada em argv[1]
	 * em caso de erro, a função retorna diferente de zero */
	if ((i=regcomp(&reg , argv[1], REG_EXTENDED)) != 0)
		/* imprime uma string do erro */
		er_error(i,reg);	

	printf("********** string original **********\n%s\n\n",argv[2]);
	i = start = 0;
	/* casa a ER com o input argv[2] 
	 * ^ marca início de linha */
	error = regexec(&reg, argv[2], 1, &match, 0);
	/* tenta casar a ER mais vezes na string */
	while(error == 0) {
		printf("início da string de pesquisa atual no caractere %d\n",start);
		printf("string de pesquisa = \"%s\"\n",argv[2]+start);
		printf("casou do caractere = %d ao %d\n\n",match.rm_so,match.rm_eo);
		start +=match.rm_eo; /* atualize início de string */
		i++;
		/* casa a ER com o input argv[2].  ^ não casa mais início de linha */
		error = regexec(&reg, argv[2]+start, 1, &match, REG_NOTBOL);
	}
	if (start !=0) printf("Número total de casamentos = %d\n",i);
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr,"Uso: match2 <ER> <input>\n");
		exit(1);
	}
	er_match(argv);
	exit(0);
}
