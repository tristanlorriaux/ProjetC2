#include "blockchain.h"


int main(void)
{
    int c, n;
    Donnee data;
    init_Data(&data);
    Genesis = NULL;
    printf("1. addBlock \n");
    printf("2. add n random block \n");
    printf("3. alterNthBlock \n");
    printf("4. printAllBlock\n");
    printf("5. verifyChain\n");
    printf("6. hackChain\n");
    printf("7. Quitter\n");
    int start = 1;
    while(start)
    {
        printf("Choice: ");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                printf("Entrer message: \n");
                scanf("%s", data.message);
                strcpy(data.exp, "moi fréro");
                strcpy(data.dest, "toi mon reuf");
                strcpy(data.date, "19/03/2020");
                ajout_block(&data);
                break;
            case 2:
                printf("How many blocks to enter?: ");
                scanf("%d", &n);
                for(int i = 0; i < n; i++)
                {
                    printf("Message à envoyer");
                    scanf("%s", data.message);
                    ajout_block(&data);
                }
                break;
            case 3:
                printf("which block to alter?: \n");
                scanf("%d", &n);
                printf("enter message: ");
                scanf("%s", data.message);
                alterNthBlock(n,&data);
                break;
            case 4:
                printAllBlock();
                break;
            case 5:
                verifyChain();
                break;
            case 6:
                hackChain();
                break;
            case 7:
                start = 0;
                break;
            default : break;
        }

    }
    return 0;
}
