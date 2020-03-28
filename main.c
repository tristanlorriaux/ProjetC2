#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int c, n;

    Genesis = NULL;
    printf("1. INITIALISER LA CHAÎNE ET AJOUTER UN PREMIER BLOCK \n");
    printf("2. IMPRIMER LA BLOCKCHAIN\n");
    printf("3. QUITTER\n");
    int start = 1;
    while(start)
    {
        printf("CHOIX: ");
        scanf("%d",&c);
        Donnee *data = (Donnee*)malloc(sizeof(Donnee)); ;
        init_Data(data);
        switch(c)
        {
            case 1:
                printf("Entrer message: \n");
                scanf("%s", data->message);
                printf("Entrer expéditeur: \n");
                scanf("%s", data->exp);
                printf("Entrer destinataire: \n");
                scanf("%s", data->dest);
                printf("Entrer date: \n");
                scanf("%s", data->date);
                ajout_block(data);
                break;
            case 2:
                printAllBlock();
                break;
            case 3:
                start = 0;
                break;
            default : break;
        }
    }
    return 0;
}
