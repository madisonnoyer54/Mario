/**
 * \file fonctions_SDL.c
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des fonctions SDL (en-tête).
 */


#include "fonctions_SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>



SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer){
       
        // Charger une image
        SDL_Surface* surface = SDL_LoadBMP(nomfichier);
        // Convertir la surface de l’image au format texture avant de l’appliquer
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); 
        //Libérer la surface
        SDL_FreeSurface(surface);
   
        return texture; 
}


SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
	/*SDL_Surface* surface = SDL_LoadBMP(nomfichier);
	Uint32 key = SDL_MapRGB(surface->format, r,  g, b);
	SDL_SetColorKey(surface, SDL_TRUE, key);*/
	SDL_Surface* surface = IMG_Load(nomfichier);
	SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return image;
}


SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color){

        // Écrire le texte sur une surface SDL
        SDL_Surface * surface = TTF_RenderText_Solid(font, message , color) ;
        // Convertir la surface de l’image au format texture avant de l’appliquer
        SDL_Texture* texte = SDL_CreateTextureFromSurface(renderer, surface); 
        //Libérer la surface
        SDL_FreeSurface(surface);

        return texte;


}


