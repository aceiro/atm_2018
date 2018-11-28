/*
 * Standard Library created for the Project.
 * All Implemented Global Functions, Constants,
 * and Variable are declared int this Library.
 * 
 */

#ifndef ATM_2S_2018_H_INCLUDED
#define ATM_2S_2018_H_INCLUDED


#define BUFFER_SIZE 1024
#define MATRIX_SIZE_C 3
#define START_OF_LINE 25
#define CLEAN_LINE_FROM "SECRETARIA DA CAMARA"
#define TAG_GO_TO_NEXT "DONE"
#define CLI_INPUT "--entrada"
#define CLI_OUTPUT "--saida"
#define CLI_FILE_TYPE_CSV "--formato-csv"
#define CLI_FILE_TYPE_TXT "--formato-txt"
#define CLI_AVG_ENGAGED "--media-empenhado"
#define CLI_AVG_SETTLED "--media-liquidado"
#define CLI_AVG_PAID "--media-valor-pago"
#define CLI_AVG_OVERALL "--media-geral"
#define CLI_HELP "--ajuda"
#define CLI_AVG_SUPPLIER "--media-fornecedor"
#define VERSION "Sumarizador ATM2s2018"
#define PROGRAM_NAME "./sumarizador"
#define EXAMPLE_PATH_OR_FILE "./Downloads/consolidado_out2018.csv"

void get_values(char filter[], double l_values[]);
double strtodouble(char * str_result[BUFFER_SIZE], int position);
void print_screen_values(int line, int str_line, int column);
void average_overall(int line, int str_line, int column, char option);
void write_to_file_all(double avg_value_engaged, double avg_value_settled, double avg_value_paid, char type_file);
void write_to_file(double avg_value_x, char option, char type_file);
void help_message();
int clean_line(char aux_read_data[BUFFER_SIZE]);
void average_per_supplier(char type_file);
void write_to_file_avg_supplier(int line, int aux_line, int v_column, char type_file);

/* Global Array of Values */
double values[BUFFER_SIZE][MATRIX_SIZE_C];

/* Global Array of Suppliers */
char suppliers[BUFFER_SIZE][BUFFER_SIZE];

/* Global Array to saved suppliers name without repeats */
char aggregate_suppliers[BUFFER_SIZE][BUFFER_SIZE];

/* Global Array to saved values and convert in averages according supplier*/
float aggregate_values[BUFFER_SIZE][MATRIX_SIZE_C];

/* Global Variable to chose averages */
char type_file = '0';

/* Global Variable to store number matrix lines  */
int number_lines = 0;

void get_values(char filter[], double l_values[]) {
  int count = 0;
  char * space = strtok(filter, " ");
  char * str_result[BUFFER_SIZE];
  int aux_count;
  double value_engaged;
  double value_settled;
  double value_paid;

  while (space) {
    str_result[count] = space;
    space = strtok(NULL, " ");
    count++;
  }

  value_engaged = strtodouble(str_result, count - 3);
  value_settled = strtodouble(str_result, count - 2);
  value_paid = strtodouble(str_result, count - 1);

  l_values[0] = value_engaged;
  l_values[1] = value_settled;
  l_values[2] = value_paid;
}

double strtodouble(char * str_result[BUFFER_SIZE], int position) {
  char temp[BUFFER_SIZE];
  int i, pos_temp = 0;

  for (i = 0; str_result[i] != '\0'; ++i) {
    if (str_result[position][i] == ',') { /* If it's comma exchange to dot */
      temp[pos_temp++] = '.';
    } else if (str_result[position][i] != '.') { /* If not dot, put the character */
      temp[pos_temp++] = str_result[position][i];
    }
  }
  temp[pos_temp] = '\0'; /* Add terminator "\0" */

  return atof(temp); /* Return converted "temp" */
}

void print_screen_values(int line, int str_line, int column) {
  int aux_count = 0;
  int str_size = 0;
  system("clear");
  for (line = 0; line < str_line; line++) {
    if ((aux_count == 0) || (aux_count == 40) || (aux_count == 80) || (aux_count == 120))
      printf("\n\t--> Listagem de Valores (R$) - Outubro 2018\n\tIndice\t\tFornecedor\t\t\tValor Empenhado (R$)\tValor Liquidado (R$)\tValor Pago (R$)\n\t---------------------------------------------------------------------------------------------------------------\n");

    printf("\t%d\t", aux_count++);

    str_size = strlen(suppliers[line]);
    printf("%-40s", suppliers[line]);

    for (column = 0; column < MATRIX_SIZE_C; column++) {
      printf("%20.2f", values[line][column]);
    }
    printf("\n");
  }
  printf("\n\n");
}

void average_overall(int line, int str_line, int column, char option) {
  double value_engaged = 0;
  double value_settled = 0;
  double value_paid = 0;
  double avg_value_engaged = 0;
  double avg_value_settled = 0;
  double avg_value_paid = 0;

  for (line = 0; line < str_line; line++) {
    for (column = 0; column < MATRIX_SIZE_C; column++) {
      if (column == 0)
        value_engaged = value_engaged + values[line][column];

      if (column == 1)
        value_settled = value_settled + values[line][column];

      if (column == 2)
        value_paid = value_paid + values[line][column];
    }
  }

  avg_value_engaged = (value_engaged / str_line);
  avg_value_settled = (value_settled / str_line);
  avg_value_paid = (value_paid / str_line);

  switch (option) {
  case '1':
    system("clear");
    if ((type_file != '1') && (type_file != '2'))
      printf("\n\n\t+\tMedia - Valor Empenhado\t\tR$ %2.2f\n\n", avg_value_engaged);

    if ((type_file == '1') || (type_file == '2'))
      write_to_file(avg_value_engaged, option, type_file);
    break;

  case '2':
    system("clear");
    if ((type_file != '1') && (type_file != '2'))
      printf("\n\n\t+\tMedia - Valor Liquidado\t\tR$ %2.2f\n\n", avg_value_settled);

    if ((type_file == '1') || (type_file == '2'))
      write_to_file(avg_value_settled, option, type_file);
    break;

  case '3':
    system("clear");
    if ((type_file != '1') && (type_file != '2'))
      printf("\n\n\t+\tMedia - Valor Pago\t\tR$ %2.2f\n\n", avg_value_paid);

    if ((type_file == '1') || (type_file == '2'))
      write_to_file(avg_value_paid, option, type_file);
    break;

  case '4':
    system("clear");
    if ((type_file != '1') && (type_file != '2')) {
      printf("\n");
      printf("\n\t+\tMedia - Valor Empenhado\t\tR$ %2.2f\n", avg_value_engaged);
      printf("\n\t+\tMedia - Valor Liquidado\t\tR$ %2.2f\n", avg_value_settled);
      printf("\n\t+\tMedia - Valor Pago\t\tR$ %2.2f\n", avg_value_paid);
      printf("\n");
    }

    if ((type_file == '1') || (type_file == '2'))
      write_to_file_all(avg_value_engaged, avg_value_settled, avg_value_paid, type_file);
    break;

  default:
    system("clear");
    printf("\n\n\t+\tErro... \n\n");
    break;
  }
}

void write_to_file_all(double avg_value_engaged, double avg_value_settled, double avg_value_paid, char type_file) {
  FILE * fp_w; /* Pointer (File type) */
  char * file_type_name = "\0"; /* Pointer to storage file name and file type */

  /* Checking file type */
  if (type_file == '1')
    file_type_name = "arquivo.csv";

  if (type_file == '2')
    file_type_name = "arquivo.txt";

  /* Create / Open file in w (write) mode */
  if ((fp_w = fopen(file_type_name, "w")) == NULL) {
    /* If file was not cretated */
    printf("\nNao foi possivel criar o Arquivo %s.\n\n", file_type_name);
    exit(EXIT_FAILURE);
  }

  /* Generating file in csv format */
  if (type_file == '1') {
    fprintf(fp_w, "\nMedias Gerais\n");
    fprintf(fp_w, "\n\t,+,\t,Media - Valor Empenhado,\t,\t,R$,%2.2f\n", avg_value_engaged);
    fprintf(fp_w, "\n\t,+,\t,Media - Valor Liquidado,\t,\t,R$,%2.2f\n", avg_value_settled);
    fprintf(fp_w, "\n\t,+,\t,Media - Valor Pago,\t,\t,R$,%2.2f\n", avg_value_paid);
    fprintf(fp_w, "\n");
  }

  /* Generating file in txt format */
  if (type_file == '2') {
    fprintf(fp_w, "\nMedias Gerais\n");
    fprintf(fp_w, "\n\t+\tMedia - Valor Empenhado\t\tR$ %2.2f\n", avg_value_engaged);
    fprintf(fp_w, "\n\t+\tMedia - Valor Liquidado\t\tR$ %2.2f\n", avg_value_settled);
    fprintf(fp_w, "\n\t+\tMedia - Valor Pago\t\tR$ %2.2f\n", avg_value_paid);
    fprintf(fp_w, "\n");
  }

  /* Closing file and saving data */
  fclose(fp_w);

  /* Success message */
  //printf("\n\tArquivo %s criado com Sucesso\n\n", file_type_name);
  printf("\n\tArquivo [ %s ] gerado com sucesso em: ", file_type_name);
  printf("\n");
  system("pwd");
  printf("\n");
}

void write_to_file(double avg_value_x, char option, char type_file) {
  FILE * fp_w; /* Pointer (File type) */
  char * file_type_name = "\0"; /* Pointer to storage file name and file type */
  char * file_type_option = "\0"; /* Pointer to storage type option */
  char * a_path = "\0"; /* Pointer to storage file path */

  /* Checking file type */
  if (type_file == '1')
    file_type_name = "arquivo.csv";

  if (type_file == '2')
    file_type_name = "arquivo.txt";

  /* Checking option type */
  if (option == '1')
    file_type_option = "Media - Valor Empenhado";

  if (option == '2')
    file_type_option = "Media - Valor Liquidado";

  if (option == '3')
    file_type_option = "Media - Valor Pago";

  /* Create / Open file in w (write) mode */
  if ((fp_w = fopen(file_type_name, "w")) == NULL) {
    /* If file was not cretated */
    printf("\nNao foi possivel criar o Arquivo %s.\n\n", file_type_name);
    exit(EXIT_FAILURE);
  }

  /* Generating file in csv format */
  if (type_file == '1') {
    fprintf(fp_w, "\n%s\n", file_type_option);
    fprintf(fp_w, "\n\t,+,\t,%s,\t,\t,R$,%2.2f\n", file_type_option, avg_value_x);
    fprintf(fp_w, "\n");
  }

  /* Generating file in txt format */
  if (type_file == '2') {
    fprintf(fp_w, "\n%s\n", file_type_option);
    fprintf(fp_w, "\n\t+\t%s\t\tR$ %2.2f\n", file_type_option, avg_value_x);
    fprintf(fp_w, "\n");
  }

  /* Closing file and saving data */
  fclose(fp_w);

  /* Success message */
  //printf("\n\tArquivo %s criado com Sucesso em \n\n", file_type_name);
  printf("\n\tArquivo [ %s ] gerado com sucesso em: ", file_type_name);
  printf("\n");
  system("pwd");
  printf("\n");
}

void help_message() {
  system("clear");
  printf("\n\tArea de Ajuda - Programa %s.\n", VERSION);

  printf("\n\tLista de Opcoes:");
  printf("\n\t\t%s\t\t\t\tImprime na tela mensagem de ajuda.", CLI_HELP);
  printf("\n\t\t%s\t\t\tOpcao obrigatoria para receber [caminho/arquivo].", CLI_INPUT);
  printf("\n\t\t%s\t\tImprime na tela Media Empenhada.", CLI_AVG_ENGAGED);
  printf("\n\t\t%s\t\tImprime na tela Media Liquidado.", CLI_AVG_SETTLED);
  printf("\n\t\t%s\t\tImprime na tela Media Empenhada.", CLI_AVG_ENGAGED);
  printf("\n\t\t%s\t\tImprime na tela Media Valor Pago.", CLI_AVG_PAID);
  printf("\n\t\t%s\t\t\tImprime na tela Media Geral.", CLI_AVG_OVERALL);
  printf("\n\t\t%s\t\tImprime na tela Media por Fornecedor.", CLI_AVG_SUPPLIER);
  printf("\n\t\t%s\t\t\t\tOpcao obrigatoria para imprimir as Medias em Arquivo.", CLI_OUTPUT);
  printf("\n\t\t%s\t\t\tImprime em Arquivo (arquivo.csv) a media repassada.", CLI_FILE_TYPE_CSV);
  printf("\n\t\t%s\t\t\tImprime em Arquivo (arquivo.txt) a media repassada.", CLI_FILE_TYPE_TXT);
  printf("\n");

  printf("\n\tExemplos de uso: ");
  printf("\n\t\t%s %s %s", PROGRAM_NAME, CLI_INPUT, EXAMPLE_PATH_OR_FILE);
  printf("\n\t\t%s %s %s %s", PROGRAM_NAME, CLI_INPUT, EXAMPLE_PATH_OR_FILE, CLI_AVG_OVERALL);
  printf("\n\t\t%s %s %s %s %s %s", PROGRAM_NAME, CLI_INPUT, EXAMPLE_PATH_OR_FILE, CLI_AVG_PAID, CLI_OUTPUT, CLI_FILE_TYPE_CSV);
  printf("\n\t\t%s %s", PROGRAM_NAME, CLI_HELP);
  printf("\n");

  printf("\n\tUso: %s %s", PROGRAM_NAME, CLI_HELP);
  printf("\n\t\tImprime mensagem de Ajuda na tela. Nao requer outro opcao.");
  printf("\n\n\tUso: %s %s [caminho/arquivo]", PROGRAM_NAME, CLI_INPUT);
  printf("\n\t\tAbre arquivo e imprime valores na tela. Uso obrigatório da opcao [%s] antes do arquivo a ser lido.", CLI_INPUT);
  printf("\n\n\tUso: %s %s [caminho/arquivo] %s ou %s ou %s \n\tou %s ou %s", PROGRAM_NAME, CLI_INPUT, CLI_AVG_ENGAGED, CLI_AVG_SETTLED, CLI_AVG_PAID, CLI_AVG_OVERALL, CLI_AVG_SUPPLIER);
  printf("\n\t\tImprime a Media na tela (correspondente a opcao solicitada / tipo de media)");
  printf("\n\n\tUso: %s %s [caminho/arquivo] [alguma opcao de media] %s %s ou %s", PROGRAM_NAME, CLI_INPUT, CLI_OUTPUT, CLI_FILE_TYPE_CSV, CLI_FILE_TYPE_TXT);
  printf("\n\t\tImprime a Media em um arquivo na pasta local (correspondente a opcao solicitada / tipo de arquivo)");
  printf("\n");

  printf("\n\n\tPressione qualquer tecla para sair");
  getchar();
  system("clear");
}

int clean_line(char aux_read_data[BUFFER_SIZE]) {
  char * string_verify;
  int size_to_remove = 0;

  /* Pointer to find String start (strstr function) */
  string_verify = strstr(aux_read_data, CLEAN_LINE_FROM);

  /* getting the string size to subtract in line size */
  size_to_remove = strlen(string_verify);

  return size_to_remove;
}

void average_per_supplier(char type_file) {
  double value_engaged = 0;
  double value_settled = 0;
  double value_paid = 0;
  int count_match = 0;
  int line = 0;
  int t_line = 0;
  int aux_line = 0;
  int s_column = 0; /* Index to position of the characters of string */
  int v_column = 0; /* Index to position of the float numbers */
  int str_column = 0; /* Saved string size line by line */
  char temporary_data[BUFFER_SIZE][BUFFER_SIZE]; /* Swap area (supliers[][] clone) */
  char temporay_string[BUFFER_SIZE]; /* Swap area (temporary array) */

  /* Cloning supplier data */
  for (line = 0; line < number_lines; line++) {
    str_column = strlen(suppliers[line]);
    for (s_column = 0; s_column < str_column; s_column++) {
      temporary_data[line][s_column] = suppliers[line][s_column];
    }
  }

  /* Working with two "FOR" to read a row, store, and position it as "DONE" to aggregate supplier and values */
  for (line = 0; line < number_lines; line++) {
    /* Supplier to be verified and saved */
    strcpy(temporay_string, temporary_data[line]);

    for (t_line = 0; t_line < number_lines; t_line++) {
      /* Condition to accumulating or not registering */
      if (((strcmp(temporay_string, TAG_GO_TO_NEXT)) != 0) && (strcmp(temporay_string, temporary_data[t_line])) == 0) {
        /* Routine to store amount of frequency and line values, and set the line to "DONE" */
        count_match++;

        value_engaged = value_engaged + values[t_line][0];
        value_settled = value_settled + values[t_line][1];
        value_paid = value_paid + values[t_line][2];

        strcpy(temporary_data[t_line], TAG_GO_TO_NEXT);
      }
    }

    /* Condition to store consolidadted data */
    if ((strcmp(temporay_string, TAG_GO_TO_NEXT)) != 0) {
      /* Routine to store consolidadted data */
      strcpy(aggregate_suppliers[aux_line], temporay_string);

      aggregate_values[aux_line][0] = (value_engaged / count_match);
      aggregate_values[aux_line][1] = (value_settled / count_match);
      aggregate_values[aux_line][2] = (value_paid / count_match);

      /* Reset registers*/
      count_match = 0;
      value_engaged = 0;
      value_settled = 0;
      value_paid = 0;

      aux_line++;
    }
  }

  if (type_file == '5') {
    /* Printing on the screen */
    system("clear");
    for (line = 0; line < aux_line; line++) {
      if ((line == 0) || (line == 40) || (line == 80) || (line == 120))
        printf("\n\t--> Listagem da Media de Valores (R$) por Fornecedor - Outubro 2018\n\tIndice\t\tFornecedor\t\t\tMedia Empenhado (R$)\tMedia Liquidado (R$)\tMedia Pago (R$)\n\t---------------------------------------------------------------------------------------------------------------\n");

      printf("\t%d\t%-40s", line, aggregate_suppliers[line]);

      for (v_column = 0; v_column < MATRIX_SIZE_C; v_column++) {
        printf("%20.2f", aggregate_values[line][v_column]);
      }
      printf("\n");
    }
    printf("\n");
  } else
    write_to_file_avg_supplier(line, aux_line, v_column, type_file);
}

void write_to_file_avg_supplier(int line, int aux_line, int v_column, char type_file) {
  FILE * fp_w; /* Pointer (File type) */
  char * file_type_name = "\0"; /* Pointer to storage file name and file type */

  /* Checking file type */
  if (type_file == '1')
    file_type_name = "arquivo.csv";

  if (type_file == '2')
    file_type_name = "arquivo.txt";

  /* Create / Open file in w (write) mode */
  if ((fp_w = fopen(file_type_name, "w")) == NULL) {
    /* If file was not cretated */
    printf("\nNao foi possivel criar o Arquivo %s.\n\n", file_type_name);
    exit(EXIT_FAILURE);
  }

  /* Generating file in csv format */
  if (type_file == '1') {
    system("clear");
    for (line = 0; line < aux_line; line++) {
      if ((line == 0) || (line == 40) || (line == 80) || (line == 120))
        fprintf(fp_w, "\n\t,--> Listagem da Media de Valores (R$) por Fornecedor - Outubro 2018\n\t,Indice,\t,\t,Fornecedor,\t,\t,\t,Media Empenhado (R$),\t,Media Liquidado (R$),\t,Media Pago (R$),\n\t,---------------------------------------------------------------------------------------------------------------\n");

      fprintf(fp_w, "\t,%d,\t,%-40s,", line, aggregate_suppliers[line]);

      for (v_column = 0; v_column < MATRIX_SIZE_C; v_column++) {
        fprintf(fp_w, "%20.2f, ", aggregate_values[line][v_column]);
      }
      fprintf(fp_w, "\n");
    }
    fprintf(fp_w, "\n");
  }

  /* Generating file in txt format */
  if (type_file == '2') {
    system("clear");
    for (line = 0; line < aux_line; line++) {
      if ((line == 0) || (line == 40) || (line == 80) || (line == 120))
        fprintf(fp_w, "\n\t--> Listagem da Media de Valores (R$) por Fornecedor - Outubro 2018\n\tIndice\t\tFornecedor\t\t\tMedia Empenhado (R$)\tMedia Liquidado (R$)\tMedia Pago (R$)\n\t---------------------------------------------------------------------------------------------------------------\n");

      fprintf(fp_w, "\t%d\t%-40s", line, aggregate_suppliers[line]);

      for (v_column = 0; v_column < MATRIX_SIZE_C; v_column++) {
        fprintf(fp_w, "%20.2f", aggregate_values[line][v_column]);
      }
      fprintf(fp_w, "\n");
    }
    fprintf(fp_w, "\n");
  }

  /* Closing file and saving data */
  fclose(fp_w);

  /* Success message */
  printf("\n\tArquivo [ %s ] gerado com sucesso em: ", file_type_name);
  printf("\n");
  system("pwd");
  printf("\n");
}

#endif