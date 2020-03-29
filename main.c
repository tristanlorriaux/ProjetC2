#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compte.h"

int main(void)
{
    /*int c, n;
    
    
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
        Donnee *data = (Donnee*)malloc(sizeof(Donnee)); ;
        init_Data(data);
        switch(c)
        {
            case 1:
                
                printf("Entrer message: \n");
                scanf("%s", data->message);
                strcpy(data->exp, "moi frero");
                strcpy(data->dest, "toi mon reuf");
                strcpy(data->date, "19/03/2020");
                ajout_block(data);
                break;
            case 2:
                printf("How many blocks to enter?: ");
                scanf("%d", &n);
                for(int i = 0; i < n; i++)
                {
                    printf("Message à envoyer");
                    scanf("%s", data->message);
                    ajout_block(data);
                }
                break;
            case 3:
                printf("which block to alter?: \n");
                scanf("%d", &n);
                printf("enter message: ");
                scanf("%s", data->message);
                
                break;
            case 4:
                printAllBlock();
                break;
            case 5:
               
                break;
            case 6:
                //hackChain();
                break;
            case 7:
                start = 0;
                break;
            default : break;
        }

    }*/
    TABID TabID;
    initTabID(&TabID);
    LoadTabIDFromFile(&TabID, FileName);
    int start = 1;
    while(start)
    {
        printf("1/ S'dentifier\n");
        printf("2/ Créer un nouveau compte\n");
        printf("3/ Quitter\n");
        printf("Choix : ");
        int choix;
        scanf("%d", &choix);
        switch(choix)
        {
            case 1:
                while(!SignIn(&TabID));
                
                break;
            case 2:
                while(!SignUp(&TabID));
                break;
            case 3:
                start = 0;
                break;
        }
            
                
    }
        

    return 0;
}
