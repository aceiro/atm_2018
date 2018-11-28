#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> /* Enable use of the strdup */
#include "atm_2s_2018.h"

int main(int argc, char * argv[]) {
  FILE * fp;
  char buffer[BUFFER_SIZE];
  char * read_data[BUFFER_SIZE];
  char aux_read_data[BUFFER_SIZE];
  int read_size = 0;
  int line = 0;
  int index = 0;
  int t_index = 0;
  double l_values[MATRIX_SIZE_C];
  char option = 0;
  char filter[BUFFER_SIZE][BUFFER_SIZE];
  char ch;
  int column = 0;
  int t_column = 0;
  int str_size = 0;
  int str_line = 0;
  int str_column = 0;
  int aux_line = 0;
  int aux_column = 0;

  while (argc == 1) {
    fprintf(stderr, "\n\tFaca assim: %s --parametro [caminho/arquivo] ou %s %s\n\n", argv[0], argv[0], CLI_HELP);
    return 1;
  }

  if ((strcmp(argv[1], CLI_HELP) != 0) && (strcmp(argv[1], CLI_INPUT) != 0)) {
    fprintf(stderr, "\n\tFaca assim: %s --parametro [caminho/arquivo] ou %s %s\n\n", argv[0], argv[0], CLI_HELP);
    return 1;
  }

  if ((strcmp(argv[1], CLI_HELP) == 0)) {
    help_message();
    return 1;
  }

  if ((strcmp(argv[1], CLI_INPUT) == 0)) { /* Start: Data manipulation routines */

    /* Condition: if file or path exists, will be open in read-mode "r" */
    if ((fp = fopen(argv[2], "r")) == NULL) {
      printf("\n\t[caminho/arquivo]: Caminho (diretorio) ou Arquivo nao encontrados ou omitidos\n\n");
      return 1;
    }

    /* Loop: getting line by line, and inserting into a array and after copied to another array */
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      read_size = strlen(buffer);
      /* "strdup" from <strings.h> doing copy of pointer to pointer */
      read_data[index] = strdup(buffer);
      index++;
      line++;
    }
    /* Building suppliers name matrix */
    t_index = 0;
    for (index = 0; index < line; index++) {
      str_column = strlen(read_data[index]);
      if (read_data[index][0] == '1') {
        /* Routine to find string patterns that are after the supplier name */
        aux_column = clean_line(read_data[index]);
        t_column = 0;
        for (column = START_OF_LINE; column < (str_column - aux_column); column++) {
          ch = read_data[index][column];
          /* Populating data in matrix */
          suppliers[t_index][t_column] = ch;
          t_column++;
        }
        t_index++;
      }
    }
    t_index = 0;

    /* Creating and applying filter for an matrix of values */
    for (index = 0; index < line; index++) {
      str_column = strlen(read_data[index]);
      if (read_data[index][str_column - 31] == 'C')
        read_data[index][str_column - 31] = '\0';

      if (read_data[index][0] == '1') {
        for (column = 0; column < str_column; column++) {
          ch = read_data[index][column];
          filter[t_index][column] = ch;
        }
        str_line++;
        t_index++;
      }
    }

    for (t_index = 0; t_index < str_line; t_index++) {
      str_column = strlen(filter[t_index]);

      get_values(filter[t_index], l_values);
      for (column = 0; column < MATRIX_SIZE_C; column++) {
        values[t_index][column] = l_values[column];
      }
    }
  } /* End: Data manipulation routines */
  number_lines = str_line;

  if (argc <= 3) {
    print_screen_values(line, str_line, column);
    return 1;
  } else {
    while (argc > 3) { /* Start: choice of averages */

      /* Average for Engaged Values */
      if ((strcmp(argv[3], CLI_AVG_ENGAGED) == 0)) {
        option = '1';

        if (argc == 5) {
          if ((strcmp(argv[4], CLI_OUTPUT) != 0)) {
            fprintf(stderr, "\n\tParametro desconhecido ou nao digitado, use %s ou %s %s\n\n", CLI_OUTPUT, argv[0], CLI_HELP);
            return 1;
          }

          if ((strcmp(argv[4], CLI_OUTPUT) == 0) && (argc >= 5)) {
            fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
            return 1;
          }
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_CSV) == 0)) {
          type_file = '1';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) == 0)) {
          type_file = '2';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && ((strcmp(argv[5], CLI_FILE_TYPE_CSV) != 0) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) != 0))) {
          fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
          return 1;
        }

        average_overall(line, str_line, column, option);
        return 1;
      }

      /* Average for Settled Values */
      if ((strcmp(argv[3], CLI_AVG_SETTLED) == 0)) {
        option = '2';

        if (argc == 5) {
          if ((strcmp(argv[4], CLI_OUTPUT) != 0)) {
            fprintf(stderr, "\n\tParametro desconhecido ou nao digitado, use %s ou %s %s\n\n", CLI_OUTPUT, argv[0], CLI_HELP);
            return 1;
          }

          if ((strcmp(argv[4], CLI_OUTPUT) == 0) && (argc >= 5)) {
            fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
            return 1;
          }
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_CSV) == 0)) {
          type_file = '1';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) == 0)) {
          type_file = '2';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && ((strcmp(argv[5], CLI_FILE_TYPE_CSV) != 0) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) != 0))) {
          fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
          return 1;
        }

        average_overall(line, str_line, column, option);
        return 1;
      }

      /* Average for Paid Values */
      if ((strcmp(argv[3], CLI_AVG_PAID) == 0)) {
        option = '3';

        if (argc == 5) {
          if ((strcmp(argv[4], CLI_OUTPUT) != 0)) {
            fprintf(stderr, "\n\tParametro desconhecido ou nao digitado, use %s ou %s %s\n\n", CLI_OUTPUT, argv[0], CLI_HELP);
            return 1;
          }

          if ((strcmp(argv[4], CLI_OUTPUT) == 0) && (argc >= 5)) {
            fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
            return 1;
          }
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_CSV) == 0)) {
          type_file = '1';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) == 0)) {
          type_file = '2';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && ((strcmp(argv[5], CLI_FILE_TYPE_CSV) != 0) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) != 0))) {
          fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
          return 1;
        }

        average_overall(line, str_line, column, option);
        return 1;
      }

      /* Average Overall */
      if ((strcmp(argv[3], CLI_AVG_OVERALL) == 0)) {
        option = '4';

        if (argc == 5) {
          if ((strcmp(argv[4], CLI_OUTPUT) != 0)) {
            fprintf(stderr, "\n\tParametro desconhecido ou nao digitado, use %s ou %s %s\n\n", CLI_OUTPUT, argv[0], CLI_HELP);
            return 1;
          }

          if ((strcmp(argv[4], CLI_OUTPUT) == 0) && (argc >= 5)) {
            fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
            return 1;
          }
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_CSV) == 0)) {
          type_file = '1';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) == 0)) {
          type_file = '2';
          average_overall(line, str_line, column, option);
          return 1;
        }

        if ((argc == 6) && ((strcmp(argv[5], CLI_FILE_TYPE_CSV) != 0) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) != 0))) {
          fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
          return 1;
        }

        average_overall(line, str_line, column, option);
        return 1;
      }

      /* Average per Suppliers */
      if ((strcmp(argv[3], CLI_AVG_SUPPLIER) == 0)) {
        option = '5';

        if (argc == 5) {
          if ((strcmp(argv[4], CLI_OUTPUT) != 0)) {
            fprintf(stderr, "\n\tParametro desconhecido ou nao digitado, use %s ou %s %s\n\n", CLI_OUTPUT, argv[0], CLI_HELP);
            return 1;
          }

          if ((strcmp(argv[4], CLI_OUTPUT) == 0) && (argc >= 5)) {
            fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
            return 1;
          }
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_CSV) == 0)) {
          type_file = '1';
          average_per_supplier(type_file);
          return 1;
        }

        if ((argc == 6) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) == 0)) {
          type_file = '2';
          average_per_supplier(type_file);
          return 1;
        }

        if ((argc == 6) && ((strcmp(argv[5], CLI_FILE_TYPE_CSV) != 0) && (strcmp(argv[5], CLI_FILE_TYPE_TXT) != 0))) {
          fprintf(stderr, "\n\tObrigatoriamente necessario apos %s, o uso de %s ou %s.\n\tEm caso de duvidas, %s %s\n\n", CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT, argv[0], CLI_HELP);
          return 1;
        }

        type_file = option;
        average_per_supplier(type_file);
        return 1;
      }

      if ((strcmp(argv[3], CLI_AVG_ENGAGED) != 0) || (strcmp(argv[3], CLI_AVG_SETTLED) != 0) || (strcmp(argv[3], CLI_AVG_PAID) != 0) || (strcmp(argv[3], CLI_AVG_OVERALL) != 0) || (strcmp(argv[3], CLI_AVG_SUPPLIER) != 0)) {
        fprintf(stderr, "\n\tObrigatoriamente use %s, %s, %s, %s ou %s.\n\tEm caso de duvidas, use %s %s\n\n", CLI_AVG_ENGAGED, CLI_AVG_SETTLED, CLI_AVG_PAID, CLI_AVG_OVERALL, CLI_AVG_SUPPLIER, argv[0], CLI_HELP);
        return 1;
      }

    } /* End: choice of averages */
    return 1;
  }

  fclose(fp);
  return 0;
}