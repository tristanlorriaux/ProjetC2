#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compte.h"
#include "sdl.h"

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
    /*
    TABID TabID;
    Genesis = (struct genesis*)malloc(sizeof(struct genesis));
    initGenesis();
    initTabID(&TabID);
    LoadTabIDFromFile(&TabID, FileNameID);
    LoadBlockChainFromFile(FileNameBC);
    int start = 1;
    while(start)
    {
        printf("\n1/ S'dentifier\n");
        printf("2/ Créer un nouveau compte\n");
        printf("3/ Quitter\n");
        printf("Choix : ");
        int choix;
        int connect = 0;            //Variable pour savoir si on est connecté
        char exp[MAX_WORD_LENGHT];  //string contenant le nom de l'expéditeur
        scanf("%d", &choix);
        switch(choix)
        {
            case 1:                
                while(!SignIn(&TabID, exp));
                connect = 1;
                break;
            case 2:
                while(!SignUp(&TabID));
                break;
            case 3:
                start = 0;
                break;
        }
        if(connect)
        {
            char choice[MAX_WORD_LENGHT];
            char *dest = DisplayUsers(&TabID, choice);
            if(Genesis->premier != NULL)
                DisplayMessages(dest, exp);
            SendMessage(dest,exp);
            printAllBlock();
        }
          
                
    }
    SaveBlockChain(FileNameBC);*/
    Data *Bottle = (Data*)malloc(sizeof(Data));
    init_global(Bottle);

    /*-------------------------Affichage d'une texture-------------------------*/
    
    /*-------------------------------------------------------------------------*/
    int m = 1;
    int x = 0; //Position de la souris
    int y = 0;
    while(m != 0)
    {
        SDL_RenderCopy(Bottle->Main_Renderer, Bottle->menu_Texture, NULL, NULL);
        SDL_RenderPresent(Bottle->Main_Renderer);
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    m = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    if(x > 600 && x < 960 && y > 285 && y<335)  //Se connecter
                    {
                        m = Display_Connecter(Bottle);
                    }
                    if(x > 600 && x < 1290 && y>425 && y<462)   //Créer un compte
                    {
                        printf("mdr\n");
                    }
                    continue;
            }
        }
    }   
    

    SDL_Quit();

    return 0;
}
