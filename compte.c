#include "compte.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "blockchain.h"



void initTabID(TABID *TabID)
{
    TabID->taille = 0;
    TabID->ID = (struct Identifiant*)malloc(NbID*sizeof(struct Identifiant));
}

void LoadTabIDFromFile(TABID* TabID, const char* TabIDFileName)
{
    FILE* file = fopen(TabIDFileName, "r");
    int i = 0;
    
    while(fscanf(file, "%s %s", TabID->ID[i].username, TabID->ID[i].password) == 2 && i<NbID)
    {
        i++;
    }
        
    TabID->taille = i;

    fclose(file);
}

void SaveTabID(TABID* TabID,const char* TabIDFileName)
{
    FILE* file = fopen(TabIDFileName, "w");
    int taille = TabID->taille;
    
    for(int i = 0; i<taille; i++)
    {
        fprintf(file, "%s %s\n", TabID->ID[i].username, TabID->ID[i].password);
    }

    fclose(file);
}

void insertElementToTabID(TABID* TabID, struct Identifiant* Element)
{
    int taille = TabID->taille;
    strcpy(TabID->ID[taille].username, Element->username);
    strcpy(TabID->ID[taille].password, Element->password);
    TabID->taille++;
}

char *CryptPassword(struct Identifiant* Element, char output[HASH_HEX_SIZE])
{
    struct bloc *Bloc = (struct bloc *)malloc(sizeof(struct bloc));
    Bloc->donnee = (donnee*)malloc(sizeof(donnee));    
    init_Data(Bloc->donnee);    
    Bloc->index = 0;
    strcpy(Bloc->precHash, Element->password);
    Bloc->nonce = 0;
    Hex_Hash(Bloc, output);
    return output;
}

bool checkExistenceElementInTabID(TABID* TabID, struct Identifiant* Element)
{
    int taille = TabID->taille;
    char mdp_crypt[HASH_HEX_SIZE];
    CryptPassword(Element, mdp_crypt);

    for(int i = 0; i<taille; i++)
    {
        if(strcmp(TabID->ID[i].username, Element->username) == 0 && strcmp(TabID->ID[i].password, mdp_crypt) == 0)
        {
            return true;
        }
    }

    return false;
}

void printTabID(TABID* TabID)
{
    int taille = TabID->taille;
    printf("TabID : \n");
    for(int i = 0; i<taille; i++)
    {
        printf("Username : %s , Password : %s\n", TabID->ID[i].username, TabID->ID[i].password);
    }
}

bool SignUp(TABID* TabID)   //Créer un nouveau compte
{
    struct Identifiant Element;
    printf("Username : ");
    scanf("%s", Element.username);
    while(strlen(Element.username)> MAX_WORD_LENGHT) //On test la taille
    {
        printf("Username trop grand\n");
        printf("Username : ");
        scanf("%s", Element.username);
    }
    printf("Password : ");
    scanf("%s", Element.password);
    while(strlen(Element.password)>65)              //On test la taille
    {
        printf("Password trop grand\n");
        printf("Password : ");
        scanf("%s", Element.password);
    }
    char mdp_crypt[HASH_HEX_SIZE];
    CryptPassword(&Element, mdp_crypt);
    strcpy(Element.password, mdp_crypt);

    if(!checkExistenceElementInTabID(TabID, &Element))  //On test si les identifiants existent déjà
    {
        insertElementToTabID(TabID, &Element);
        printf("Nouveau compte créé\n");
        SaveTabID(TabID, FileName);                     //On enregistre les nouveaux identifiants 
        return true;
    }
    else
    {
        printf("Identifiants déjà existant\n");
        return false;
    }  
    
}

bool SignIn(TABID* TabID)   //S'identifier
{
    struct Identifiant Element;
    printf("Identifiez-vous \n");
    printf("Username : ");
    scanf("%s", Element.username);
    while(strlen(Element.username)> MAX_WORD_LENGHT) //On test la taille
    {
        printf("Username trop grand\n");
        printf("Username : ");
        scanf("%s", Element.username);
    }
    printf("Password : ");
    scanf("%s", Element.password);
    while(strlen(Element.password)>65)              //On test la taille
    {
        printf("Password trop grand\n");
        printf("Password : ");
        scanf("%s", Element.password);
    }
    if(checkExistenceElementInTabID(TabID, &Element))
    {
        printf("Vous vous êtes bien identifié\n");
        return true;
    }
    else
    {
        printf("Username ou password incorrect\n");
        return false;
    }
       
}
