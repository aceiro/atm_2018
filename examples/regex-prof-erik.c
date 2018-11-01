#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

/*
 * Exemplo de uso de RegEx para o problema de filtrar uma linha do arquivo. Exemplo baseado no site [1]
 * 
 * Linha de Exemplo:
 * 
 * ---------------------------------------------------------------------------------------------------------------------------------------------
 * 1333-000/2018 01/10/2018 PANTOJA & CIA. LTDA SECRETARIA DA CAMARA SECRETARIA DA CAMARA AÇÃO LEGISLATIVA Dispensa - Isento Compras e Serviços 798,40 798,40 798,40
 * ---------------------------------------------------------------------------------------------------------------------------------------------
 *
 * RegEx:
 * -------------------------
 * (\d)+\.?(\d)+\d,\d+
 * -------------------------
 * 
 *
 * Faça o teste no site [2]. No site existe um campo para colocar a RegEx e outro para 
 * colocar o texto que se deseja buscar informações (dados). Coloque o conteúdo do arquivo de exemplo
 * ou a linha acima e em seguida troque o motor de expressão regular para PCRE. 
 * 
 * Nesse caso, serão detectadas apenas grupos de sequencias numéricas (Valor Empenhado, Liquido e Pago)
 *
 * Referências
 * [1] https://stackoverflow.com/questions/2577193/how-do-you-capture-a-group-with-regex
 * [2] https://gist.github.com/ianmackinnon/3294587
 *
 * */


int main ()
{
  char * source = "1333-000/2018 01/10/2018 PANTOJA & CIA. LTDA SECRETARIA DA CAMARA SECRETARIA DA CAMARA AÇÃO LEGISLATIVA Dispensa - Isento Compras e Serviços 798,40 898,40 998,40";
  char * regexString = "[0-9]+\\.?[0-9]+[0-9],[0-9]+";
  size_t maxGroups   = 3;
  size_t maxMatches  = 3;
  unsigned int m;
  char * cursor;

  regex_t regexCompiled;
  regmatch_t groupArray[maxGroups];

  if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
      printf("Could not compile regular expression.\n");
      return 1;
    };
  
  
  m = 0;
  cursor = source;

 for (m = 0; m < maxMatches; m ++)
    {
      if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
        break;  // No more matches

      unsigned int g = 0;
      unsigned int offset = 0;
      for (g = 0; g < maxGroups; g++)
        {
          if (groupArray[g].rm_so == (size_t)-1)
            break;  // No more groups

          if (g == 0)
            offset = groupArray[g].rm_eo;

          char cursorCopy[strlen(cursor) + 1];
          strcpy(cursorCopy, cursor);
          cursorCopy[groupArray[g].rm_eo] = 0;
          printf("Match %u, Group %u: [%2u-%2u]: %s\n",
                 m, g, groupArray[g].rm_so, groupArray[g].rm_eo,
                 cursorCopy + groupArray[g].rm_so);
        }
      cursor += offset;
    }


  regfree(&regexCompiled);

  return 0;
}


/*
int main(int argc, char *argv[]){
        regex_t regex;
        int reti;
        char msgbuf[100];


        reti = regcomp(&regex, "^a[[:alnum:]]", 0);
        if( reti ){ fprintf(stderr, "Could not compile regex\n"); return 1; }


        reti = regexec(&regex, "abc", 0, NULL, 0);
        if( !reti ){
                puts("Match");
        }
        else if( reti == REG_NOMATCH ){
                puts("No match");
        }
        else{
                regerror(reti, &regex, msgbuf, sizeof(msgbuf));
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
                return 1;
        }


	regfree(&regex);

        return 0;
}
*/

