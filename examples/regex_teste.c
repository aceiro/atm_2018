#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAXMATCH 20

int main () {

        char reginald[81];      /* Regular Expresion */
        char millie[81];        /* Strings to match against */
        char tommy[81];         /* String to hold matched elememts */
        regex_t emma;

        regmatch_t matches[MAXMATCH];   /* Array of matches */
        int status;
        int i;
        int numchars;

        /* Read in and compile a regular expression */

        printf("Please give test expression: ");
        fgets(reginald,80,stdin);
        reginald[strlen(reginald)-1] = '\0';

        /* Let's use extended regular expresssions */

        status = regcomp(&emma,reginald,REG_EXTENDED);
        printf("Validity of regex (0 => OK): %d\n",status);

        /* Leave program if regex is faulty */
        /* we could use regerror to decode the error ... */
        if (status) return 1;

        while (1) {

                /* Loop until an empty line id given */

                printf("Please give test string: ");
                fgets(millie,80,stdin);
                millie[strlen(millie)-1] = '\0';
                if (strlen(millie) < 1) break;

                status = regexec(&emma,millie,MAXMATCH,matches,0);
                printf("Matched (0 => Yes):  %d\n",status);
                if (status == 0) {
                        for (i=0; i<MAXMATCH; i++) {
                                if ((int)matches[i].rm_so < 0) break;
                                numchars = (int)matches[i].rm_eo - (int)matches[i].rm_so;
                                strncpy(tommy,millie+matches[i].rm_so,numchars);
                                tommy[numchars] = '\0';
                                printf("From %d to %d (%s)\n",(int)matches[i].rm_so,
                                        (int)matches[i].rm_eo,tommy);
                                }
                        }

                }

        /* Free up memory held within the regex memory */
        regfree(&emma);

        return 0;

        }

/*    Sample output:

wizzard:c graham$ ./reg2
Please give test expression: [A-Z]{1,2}[0-9][0-9A-Z]? +[0-9][A-Z]{2}
Validity of regex (0 => OK): 0
Please give test string: We are at SN12 7NY for this course
Matched (0 => Yes):  0
From 10 to 18 (SN12 7NY)
Please give test string:
wizzard:c graham$

wizzard:c graham$ ./reg2
Please give test expression: ([A-Z]{1,2})[0-9][0-9A-Z]? +[0-9][A-Z]{2}
Validity of regex (0 => OK): 0
Please give test string: We are in Birmingham
Matched (0 => Yes):  1
Please give test string: We are at B12 7HJ
Matched (0 => Yes):  0
From 10 to 17 (B12 7HJ)
From 10 to 11 (B)
Please give test string:
wizzard:c graham$

*/