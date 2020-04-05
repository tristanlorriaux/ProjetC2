#include "compte.h"
#include "saisi.h"
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
    SaveTabID(TabID, FileNameID);
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

void SignUp(TABID* TabID, struct Identifiant* Element)   //Créer un nouveau compte
{
    char mdp_crypt[HASH_HEX_SIZE];
    CryptPassword(Element, mdp_crypt);
    strcpy(Element->password, mdp_crypt);
    insertElementToTabID(TabID, Element);    
}

bool SignIn(TABID* TabID, char* exp)   //S'identifier
{
    struct Identifiant Element;
    printf("Identifiez-vous \n");
    printf("Username : ");
    scanf("%s", Element.username);
    while(strlen(Element.username)> MAX_WORD_LENGHT)    //On test la taille
    {
        printf("Username trop grand\n");
        printf("Username : ");
        scanf("%s", Element.username);
    }
    printf("Password : ");
    scanf("%s", Element.password);
    while(strlen(Element.password)>MAX_WORD_LENGHT)     //On test la taille
    {
        printf("Password trop grand\n");
        printf("Password : ");
        scanf("%s", Element.password);
    }
    if(checkExistenceElementInTabID(TabID, &Element))
    {
        printf("Vous vous êtes bien identifié\n");
        strcpy(exp, Element.username);                  //ON met à jour la variable exp qui contient le nom de l'expéditeur
        return true;
    }
    else
    {
        printf("Username ou password incorrect\n");
        return false;
    }
       
}



void SendMessage(char* dest, char* exp)     //Problème : les messages de plusieurs mots ne sont pas entièrement lu par scanf, il lit juste le premier
{
    donnee *Message = (donnee*)malloc(sizeof(donnee));
    strcpy(Message->dest, dest);
    strcpy(Message->exp, exp);
    strcpy(Message->date, "29/03/2020");
    

    
    vider_stdin();              //On vide le buffer pour éviter les problèmes
    printf("Entrez le message : ");
    Saisi(Message->message);    //On saisi la phrase
    
    ajout_block(Message);       //On ajoute le nouveau message à la blockchain

}

