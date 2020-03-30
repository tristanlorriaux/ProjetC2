#ifndef SDL_H
    #include <SDL2/SDL.h>
    #define SDL_H

    #define Long_WINDOW
    #define Large WINDOW

    typedef struct {
    SDL_Renderer* Main_Renderer;
    SDL_Window* Main_Window;

    SDL_Texture* menu_Texture;
    SDL_Texture* compte_Texture;
    SDL_Texture* connexion_Texture;
    SDL_Texture* messagerie_Texture;

    SDL_Surface* Loading_Surf; 
    SDL_Rect SrcR;
    SDL_Rect DestR;
    char image[30];
    int posX;
    int posY;
    } Data;


    void init_global(Data* Bottle);

    SDL_Texture* init_texture(Data* Bottle, SDL_Texture* texture);
    void SDL_Dest(Data *Bottle);
    int Display_Connecter(Data* Bottle);    //Affiche la partie Se connecter et renvoie 0 si l'on a appuyé sur le croix pour quitter



#endif