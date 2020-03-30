
#include "saisi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void vider_stdin(void)
{
    scanf("%*[^\n]");
    getchar();
}
 
char* Saisi(char* output)
{
    char *pc;
    char s_buffer[200] = {0};
    int saisie_OK = 0;
 
    while (saisie_OK == 0)
    {
        fflush(stdout);
 
        fgets(s_buffer, sizeof s_buffer, stdin);
        if ((pc = strchr(s_buffer, '\n')) != NULL)
        {
            *pc = '\0';
            saisie_OK = 1;
        }
        else
        {
            /* saisie trop longue */
            fprintf(stderr, "La saisie est trop longue!\n");
            vider_stdin();
        }
    }
 
    strcpy(output, s_buffer);
 
    return output;
}