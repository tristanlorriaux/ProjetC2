#include <SDL2/SDL.h> //apt-get install libsdl1.2-dev
#include "compte.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdl.h"
#include <SDL2/SDL_ttf.h>   //apt-get install libsdl2-ttf-dev
#include <SDL2/SDL_image.h> //apt-get install libsdl2-image-dev


void init_global(Data* Bottle)
{
    SDL_Init(SDL_INIT_VIDEO);
    Bottle->Main_Window = SDL_CreateWindow("Bottle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1374, 775, 0);
    Bottle->Main_Renderer = SDL_CreateRenderer(Bottle->Main_Window, -1, SDL_RENDERER_ACCELERATED);

    strcpy(Bottle->image,"images/menu.bmp");
    Bottle->menu_Texture = init_texture(Bottle, Bottle->menu_Texture);
    
    strcpy(Bottle->image,"images/compte.bmp");
    Bottle->compte_Texture = init_texture(Bottle, Bottle->compte_Texture);

    strcpy(Bottle->image,"images/connexion.bmp");
    Bottle->connexion_Texture = init_texture(Bottle, Bottle->connexion_Texture);

    strcpy(Bottle->image,"images/messagerie.bmp");
    Bottle->messagerie_Texture = init_texture(Bottle, Bottle->messagerie_Texture);
    
}


SDL_Texture* init_texture(Data* Bottle, SDL_Texture* texture)
{

    Bottle->Loading_Surf = SDL_LoadBMP(Bottle->image);
    texture = SDL_CreateTextureFromSurface(Bottle->Main_Renderer, Bottle->Loading_Surf);
    SDL_FreeSurface(Bottle->Loading_Surf); /* we got the texture now -> free surface */
    return texture;
}


int Display_Connecter(Data* Bottle)
{
    SDL_RenderCopy(Bottle->Main_Renderer, Bottle->connexion_Texture, NULL, NULL);
    SDL_RenderPresent(Bottle->Main_Renderer);
    int m = 1;
    int x = 0; //Position de la souris
    int y = 0;
    int r = 1;  //Quitter
    while(m != 0)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    m = 0;
                    r = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    if(y > 305 && y<355  )  //Se connecter&& x > 765 && x < 1300
                    {
                        printf("haha\n");
                    }
                    if(x > 600 && x < 1290 && y>425 && y<462)   //Créer un compte
                    {
                        printf("hihi\n");
                    }
                    continue;
            }
        }
        
    }
    return r;
}






void SDL_Dest(Data *donnee)//Détruit les texture le rendu et la fenêtre
{
    SDL_DestroyTexture(donnee->menu_Texture);
    SDL_DestroyRenderer(donnee->Main_Renderer);
    //SDL_DestroyWindow(donnee->Main_Window); 
    SDL_RenderPresent(donnee->Main_Renderer);
}