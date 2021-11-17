/**
 * \file graphique.c
 * \author Juliette Schilling / Madison Noyer.
 * \brief Module de gestion de l'affichage graphique.
 */
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include <SDL2/SDL.h>


void initialisation(ressources_t *ressources){
	
	// Créer la fenêtre
	ressources->fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_RESIZABLE);

	// En cas d’erreur
	if(ressources->fenetre == NULL)
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
	}
	
	// Mettre en place un contexte de rendu de l’écran
	ressources->ecran = SDL_CreateRenderer(ressources->fenetre, -1, SDL_RENDERER_ACCELERATED);
	// Charger l’image
	ressources->fond = charger_image("ressources/fond.bmp", ressources->ecran );
}


void tableau_mario(ressources_t *ressources,world_t *world){
	int tailleW, tailleH;

	 // tableau de sprite 
    Uint8 r = 0, g = 0, b = 0;
    ressources->mario = charger_image_transparente("ressources/marioplage.bmp", ressources->ecran,r,g,b);
    
    SDL_QueryTexture(ressources->mario, NULL, NULL, &tailleW, &tailleH);
 

    for(int i = 0; i < 72; i++) {
        ressources->SrcR_mario[i].x = tailleW /9 * (i%9) ;
        ressources->SrcR_mario[i].y = i < 9 ? 0 : tailleH / 8;
        ressources->SrcR_mario[i].w = tailleW/9; // Largeur de l’objet en pixels 
        ressources->SrcR_mario[i].h = tailleH/8 ; // Hauteur de l’objet en pixels 

        ressources->DestR_mario[i].x = world->mario.x;
		ressources->DestR_mario[i].y = world->mario.y;
		ressources->DestR_mario[i].w = tailleW/9  ; // Largeur du sprite
		ressources->DestR_mario[i].h = tailleH/8 ; // Hauteur du sprite
	}

}


void affichage(ressources_t *ressources){
	

	SDL_RenderClear(ressources->ecran);
	SDL_RenderCopy(ressources->ecran, ressources->fond, NULL, NULL);
	SDL_RenderCopy(ressources->ecran, ressources->mario, &ressources->SrcR_mario[1], &ressources->DestR_mario[1]);
	
	
}


void evenement(ressources_t *ressources,world_t *world){
	SDL_Event evenements;

	SDL_PollEvent(&evenements);

	switch(evenements.type){
		case SDL_QUIT:world->gameover = 1; 
		break;
			
		case SDL_KEYDOWN:
		switch(evenements.key.keysym.sym){
			case SDLK_ESCAPE:

            case SDLK_q:
            	world->gameover =1;
            break;
                  
			case SDLK_SPACE : 
						
			break;
            
            case SDLK_LEFT:
                world->mario.x = world->mario.x - MOVING_STEP ;
            break;
                    
			case SDLK_RIGHT:
               world->mario.x = world->mario.x + MOVING_STEP;
            break;
		}
                
        ressources->DestR_mario[1].x = world->mario.x;
                
                
	}
}

void Destroy(ressources_t ressources){
	SDL_DestroyTexture(ressources.fond);
	SDL_DestroyRenderer(ressources.ecran);
	SDL_DestroyWindow(ressources.fenetre);
}


