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
#include <SDL/SDL_mixer.h>

void evenement_menu(ressources_t *ressources, menu_t *menu, world_t *world){
  SDL_Event evenements;
  SDL_PollEvent(&evenements);
	
	int x = (int)evenements.button.x;
	int y = (int)evenements.button.y;
  
  switch(evenements.type){
  	case SDL_QUIT:
   		menu->fin = 1; 
		world->gameover = 1; 
		init_mario(ressources, world);
    		break;
    
    
  	case SDL_MOUSEBUTTONUP:
		  	choix_mario(ressources, world, x, y);
			init_mario(ressources,world);   
		  	timer_menu(menu);
    		menu->fin = 1;
    		break;
    		
    	case SDL_KEYDOWN:
		switch(evenements.key.keysym.sym){
			case SDLK_ESCAPE:

            		case SDLK_q:
            			menu->fin = 1;
						world->gameover = 1; 
						init_mario(ressources, world);
            			break;
            	}
            	break;
            	
    
  }
}


void choix_mario(ressources_t *ressources, world_t *world, int x, int y){
		int xMario, yMario, wMario, hMario;
		world->mario.couleur = 4;
		for(int i=0; i<3; i++){
			xMario = ressources->DestR_marioMenu[i].x;
			yMario = ressources->DestR_marioMenu[i].y;
			wMario = ressources->DestR_marioMenu[i].w;
			hMario = ressources->DestR_marioMenu[i].h;
			if((x >= xMario) && (x <= xMario+wMario) && (y >= yMario) && (y <= yMario+hMario)){
				world->mario.couleur = i;
			}
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
            case SDLK_LEFT:
            	world->mario.x = world->mario.x - INITIAL_SPEED ;
				world->mario.d = 'g'; 
				world->mario.decompte = world->mario.decompte + 1;

            	break;
                    
			case SDLK_RIGHT:
			   	world->mario.d = 'd';
			   	world->mario.decompte = world->mario.decompte + 1; 

				deplacement_droite(ressources,world);
				
            	break;    			
		}
		animation_mario(world);
        
		ressources->DestR_mario.x = world->mario.x;	 
		ressources->DestR_mario.y = world->mario.y;	
		break;

		case SDL_KEYUP:
		switch(evenements.key.keysym.sym){
			case SDLK_SPACE : 
				if(keystates[SDL_SCANCODE_RIGHT] || (keystates[SDL_SCANCODE_LEFT])){   //saut oriente
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
		}
		break;
		
		animation_mario(world);
        
		ressources->DestR_mario.x = world->mario.x;	 
		ressources->DestR_mario.y = world->mario.y;	
			   
    }
}

void timer_menu(menu_t *menu){
	menu->timer_menu = (SDL_GetTicks())/1000;
}



unsigned int timer(unsigned int time_menu){
	return (SDL_GetTicks())/1000 - time_menu;
}


void update_timer(world_t *world, menu_t *menu){
	if(!is_game_over(world)){
		world->timer = timer(menu->timer_menu);
	}
}



void gravite(world_t *world, ressources_t *ressources){
    while (world->mario.y <470){
    	world->mario.y += Graviter;
		
		if(world->mario.d == 'd'){
			deplacement_droite(ressources,world);
			world->mario.i = 15; 

	    }
	     	
		if(world->mario.d == 'g'){
			world->mario.x = world->mario.x - INITIAL_SPEED;  
			world->mario.i = 50;  
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
		SDL_Delay(10);
		
	}
	
	if(world->mario.d == 'd' || world->mario.d == 's'){
		world->mario.i = 6;
	}
	if(world->mario.d == 'g' || world->mario.d == 'q'){
		world->mario.i = 42;
	}

        
	world->mario.y =470;
}

void saut(world_t *world, ressources_t *ressources){
	if(world->mario.y == 470){
		while(world->mario.y > 350){
			world->mario.y = world->mario.y - 10 - Graviter;
			if(world->mario.d == 'd'){
				deplacement_droite(ressources,world);
				world->mario.x = world->mario.x + 10;
				world->mario.i = 6;
			}
			if(world->mario.d == 'g'){
				world->mario.x = world->mario.x - INITIAL_SPEED - 10;
				world->mario.i = 42;
			}

			left_overflow(&world->mario);
			right_overflow(&world->mario);

			
			ressources->DestR_mario.x = world->mario.x;	 
			ressources->DestR_mario.y = world->mario.y;	
			affichage(ressources,world);
			SDL_RenderPresent(ressources->ecran);
			SDL_Delay(10);

		
		}			
	}
}

void deplacement_droite(ressources_t *ressources,world_t *world){
	if(world->mario.x > SCREEN_WIDTH/2 ){
		ressources->DestR_walls[1].x =  ressources->DestR_walls[1].x - INITIAL_SPEED/2;
		ressources->DestR_fond.x = ressources->DestR_fond.x -INITIAL_SPEED/2;
		world->mario.x = world->mario.x + INITIAL_SPEED/2;
	}
	else{
		world->mario.x = world->mario.x + INITIAL_SPEED;
	}
	
}
