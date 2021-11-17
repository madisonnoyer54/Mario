/**
 * \file main.c
 * \author Juliette Schilling / Madison Noyer
 * \brief Programme principal
 */

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"


/** 
*   \brief programme principal qui implémente la boucle de jeu
*//*
int main(){
	SDL_Window* fenetre;  // Déclaration de la fenêtre
	SDL_Event evenements; // Événements liés à la fenêtre
	bool terminer = false;

	// Variable de déplacement pour Mario 
	world->mario.y =470;
	world->mario.x =0;
	
	

	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
	{
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	// Créer la fenêtre
	fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_RESIZABLE);

	if(fenetre == NULL) // En cas d’erreur
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	// Mettre en place un contexte de rendu de l’écran
	SDL_Renderer* ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	// Charger l’image
	SDL_Texture* fond = charger_image("ressources/fond.bmp", ecran );



    // tableau de sprite 
    Uint8 r = 0, g = 0, b = 0;
    SDL_Texture* sprite = charger_image_transparente("ressources/marioplage.bmp", ecran,r,g,b);
    int tailleW, tailleH;
    SDL_QueryTexture(sprite, NULL, NULL, &tailleW, &tailleH);
    SDL_Rect SrcR_sprite[72] ;
	SDL_Rect DestR_sprite[72];

    for(int i = 0; i < 72; i++) {
        SrcR_sprite[i].x = tailleW /9 * (i%9) ;
        SrcR_sprite[i].y = i < 9 ? 0 : tailleH / 8;
        SrcR_sprite[i].w = tailleW/9; // Largeur de l’objet en pixels 
        SrcR_sprite[i].h = tailleH/8 ; // Hauteur de l’objet en pixels 

        DestR_sprite[i].x = x;
		DestR_sprite[i].y = y;
		DestR_sprite[i].w = tailleW/9  ; // Largeur du sprite
		DestR_sprite[i].h = tailleH/8 ; // Hauteur du sprite
	}

	

	// Boucle principale
	while(!terminer){
		SDL_RenderClear(ecran);
		SDL_RenderCopy(ecran, fond, NULL, NULL);
		SDL_RenderCopy(ecran, sprite, &SrcR_sprite[1], &DestR_sprite[1]);
	
		SDL_PollEvent( &evenements );

			switch(evenements.type){
			case SDL_QUIT:terminer = true; 
			break;
			
			case SDL_KEYDOWN:
				switch(evenements.key.keysym.sym)
				{
					case SDLK_ESCAPE:

                    case SDLK_q:
                    terminer = true;
                    break;
                  
					case SDLK_SPACE : 
						
					break;
            
                    case SDLK_LEFT:
                    x--;
                    break;
                    case SDLK_RIGHT:
                    x++;
                    break;
				}
                
                DestR_sprite[1].x = x;
                DestR_sprite[1].y = y;
                
		}

		SDL_RenderPresent(ecran);
	}

	SDL_DestroyTexture(fond);
	SDL_DestroyRenderer(ecran);
	// Quitter SDLSDL_DestroyWindow(fenetre);
	SDL_Quit();
	
	return 0;
}

*/



int main(){
	world_t world;
	ressources_t r;
	world.gameover = 0;
	

	// Variable de déplacement pour Mario 
	world.mario.y =470;
	world.mario.x =0;

	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	initialisation(&r);
	tableau_mario(&r,&world);

	// Boucle principale
	while(world.gameover != 1 ){
		affichage(&r);
		evenement(&r,&world);
		SDL_RenderPresent(r.ecran);
	}

	Destroy(r);
	// Quitter SDL
	SDL_Quit();

	return 0;
}

