//Permet de gérer la création et la gestion des comptes

/*-------------------------------------------------------

1/  -Créer nouveau Compte
    -Se connecter
2/ Une fois connecté:
    -Choix de l'utilisateur avec qui connecter
3/ Affichage de de la conversation et possibilité d'envoie de messages

---------------------------------------------------------*/

#include <stdbool.h>

#ifndef COMPTE_H

    #define COMPTE_H
    

    #define MAX_WORD_LENGHT	29	// Maximum word length à réajuster
    #define NbID 20             // Nombre maximal d'ID 
    #define FileName "Save.txt"

    struct Identifiant
    {
        char username[MAX_WORD_LENGHT];
        char password[65];
    };

    typedef struct 
    {
        int taille;
        struct Identifiant* ID;
    }TABID;


    //void menu(HashTable *hashTab);
    void LoadTabIDFromFile(TABID* TabID, const char* TabIDFileName);
    void insertElementToTabID(TABID* TabID, struct Identifiant* Element);
    void initTabID(TABID *TabID);
    bool checkExistenceElementInTabID(TABID* TabID, struct Identifiant* Element);
    void printTabID(TABID* TabID);
    void SaveTabID(TABID* TabID, const char* TabIDFileName);
    bool SignIn(TABID* TabID);  //S'identifier, renvoie true si l'identification s'est bien passé
    bool SignUp(TABID* TabID);  //Créer un nouveau compte, renvoie true si la création de compte s'est bien passé
    char *CryptPassword(struct Identifiant* Element, char *output);

#endif
