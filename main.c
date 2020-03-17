#include "blockchain.h"


void main(void)
{
    int c, n, r;
    Donnee *data;
    printf("1. Ajouter un bloc \n");
    printf("2. Ajouter n nouveaux blocs \n");
    printf("3. Modifier le n-ième bloc \n");
    printf("4. Imprimer tous les blocs\n");
    printf("5. Vérifier la chaîne\n");
    printf("6. hackChain\n");
    while(1)
    {
        printf("Choice: ");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                printf("Entrer message: \n");
                scanf("%s", &data->message);
                printf("Entrer expediteur: \n");
                scanf("%s", &data->exp);
                printf("Entrer destinataire: \n");
                scanf("%s", &data->dest);
                ajout_bloc(data);
                break;
            case 2:
                printf("Combien de nouveaux blocs à ajouter?: ");
                scanf("%d", &n);
                for(int i = 0; i < n; i++)
                {
                    printf("Entrer message: \n");
                    scanf("%s", &data->message);
                    printf("Entrer expediteur: \n");
                    scanf("%s", &data->exp);
                    printf("Entrer destinataire: \n");
                    scanf("%s", &data->dest);
                    ajout_bloc(data);
                }
                break;
            case 3:
                printf("Quel bloc à modifier \n");
                scanf("%d", &n);
                printf("Entrer message: \n");
                scanf("%s", &data->message);
                printf("Entrer expediteur: \n");
                scanf("%s", &data->exp);
                printf("Entrer destinataire: \n");
                scanf("%s", &data->dest);
                alterNthbloc(n,data);
                break;
            case 4:
                printAllblocs();
                break;
            case 5:
                verifyChain();
                break;
            case 6:
                hackChain();
                break;
            default : break;
        }

    }
}
