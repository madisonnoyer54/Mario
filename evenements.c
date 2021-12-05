/**
 * \file evenements.c
 * \author Juliette Schilling / Madison Noyer.
 * \brief Module de gestion des animations.
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "animations.h"
#include "evenements.h"
#include "menu.h"

void evenement_menu(ressources_t *ressources, menu_t *menu){
  SDL_Event evenements;
  SDL_PollEvent(&evenements);
  
  switch(evenements.type){
  	case SDL_QUIT:
   		menu->fin = 1; 
    		break;
    
    
  	case SDL_MOUSEBUTTONUP:
    		menu->fin = 1;
    		break;
    		
    	case SDL_KEYDOWN:
		switch(evenements.key.keysym.sym){
			case SDLK_ESCAPE:

            		case SDLK_q:
            			menu->fin = 1;
            			break;
            	}
            	break;
            	
    
  }
}


void evenement(ressources_t *ressources,world_t *world){
	SDL_Event evenements;

	SDL_PollEvent(&evenements);
	
	const Uint8 *keystates = SDL_GetKeyboardState(NULL);
	
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
				if(keystates[SDL_SCANCODE_RIGHT] || (keystates[SDL_SCANCODE_LEFT])){   //saut orienté
					saut(world,ressources);
					gravite(world,ressources);
				}
				else{             //saut vertical
					if(world->mario.d == 'g'){
						world->mario.d = 'q';
					}
					if(world->mario.d == 'd'){
						world->mario.d = 's';
					}
					saut(world, ressources);
					gravite(world, ressources);
				}
						
				break;
				
			
            
            		case SDLK_LEFT:
            			world->mario.x = world->mario.x - INITIAL_SPEED ;
				world->mario.d = 'g'; 
				world->mario.decompte = world->mario.decompte + 1;

            			break;
                    
			case SDLK_RIGHT:
            			world->mario.x = world->mario.x + INITIAL_SPEED;
			   	world->mario.d = 'd';
			   	world->mario.decompte = world->mario.decompte + 1; 

				if(world->mario.x > SCREEN_WIDTH/2 ){
					ressources->DestR_walls[1].x =  ressources->DestR_walls[1].x - INITIAL_SPEED;
					ressources->DestR_fond.x = ressources->DestR_fond.x -INITIAL_SPEED;
				}
				
            			break;
         
            			
		}
		
		animation_mario(world);
        
		
		ressources->DestR_mario.x = world->mario.x;	 
		ressources->DestR_mario.y = world->mario.y;	
			   
    }
}



unsigned int timer(){
	return (SDL_GetTicks())/1000;
}


void update_timer(world_t * world){
	if(!is_game_over(world)){
		world->timer = timer();
	}
}



void gravite(world_t *world, ressources_t *ressources){
    while (world->mario.y <470){
    	world->mario.y += Graviter;
		
		if(world->mario.d == 'd'){
			world->mario.x = world->mario.x + INITIAL_SPEED;
	    }
	     	
		if(world->mario.d == 'g'){
			world->mario.x = world->mario.x - INITIAL_SPEED;  
		}
		
		//Orientation du mario quand il retombe dans le cas statique
		if(world->mario.d == 'q'){
			world->mario.i = 37;    
		}
		if(world->mario.d == 's'){
			world->mario.i = 1;    
		}

		left_overflow(&world->mario);
		right_overflow(&world->mario);

		ressources->DestR_mario.x = world->mario.x;	 
		ressources->DestR_mario.y = world->mario.y;	
		affichage(ressources,world);
		SDL_RenderPresent(ressources->ecran);
		
	}
	

        
	world->mario.y =470;
}

void saut(world_t *world, ressources_t *ressources){
	if(world->mario.y == 470){
		while(world->mario.y > 350){
			world->mario.y = world->mario.y - 10 - Graviter;
			if(world->mario.d == 'd'){
				world->mario.x = world->mario.x + INITIAL_SPEED + 10;
				world->mario.i = 14;
			}
			if(world->mario.d == 'g'){
				world->mario.x = world->mario.x - INITIAL_SPEED - 10;
				world->mario.i = 49;
			}

			left_overflow(&world->mario);
			right_overflow(&world->mario);

			
			ressources->DestR_mario.x = world->mario.x;	 
			ressources->DestR_mario.y = world->mario.y;	
			affichage(ressources,world);
			SDL_RenderPresent(ressources->ecran);

		
		}
					
	}
}
