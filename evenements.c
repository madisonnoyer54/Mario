/**
 * \file evenements.c
 * \author Juliette Schilling / Madison Noyer.
 * \brief Module de gestion des événements.
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"

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
				world->mario.d = 'g';
				world->mario.decompte = world->mario.decompte +1;
				animation_mario(world); 
            			break;
                    
			case SDLK_RIGHT:
               			world->mario.x = world->mario.x + MOVING_STEP;
			   	world->mario.d = 'd';
			   	world->mario.decompte = world->mario.decompte +1;
				animation_mario(world); 
            			break;
		}
		
        	for(int i = 0; i < 72; i++){
			ressources->DestR_mario[i].x = world->mario.x;	 
		}       
        }
}


unsigned int timer(){
	return (SDL_GetTicks())/1000;
}


void update_timer(world_t * world){
	if((world->gameover!=1)){
		world->timer = timer();
	}
}
