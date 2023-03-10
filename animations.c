/**
 * \file animation.c
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
#include "animations.h"
#include "evenements.h"


void animation_mario(world_t *world){
	if(world->mario.decompte > 5){
		world->mario.decompte = 1;
	}

	if(world->mario.d == 'd'){	
		
		if(world->mario.decompte== 1){
			world->mario.i = 4;
		}	
		if(world->mario.decompte== 2){
			world->mario.i = 5;
		}	
		if(world->mario.decompte== 3){
			world->mario.i = 6;
		}	
		if(world->mario.decompte== 4){
			world->mario.i = 7;
		}	
		if(world->mario.decompte== 5){
			world->mario.i = 8;
		}	
	}
	if(world->mario.d == 'g'){
		if(world->mario.decompte== 1){
			world->mario.i = 40;
		}	
		if(world->mario.decompte== 2){
			world->mario.i = 41;
		}	
		if(world->mario.decompte== 3){
			world->mario.i = 42;
		}	
		if(world->mario.decompte== 4){
			world->mario.i = 43;
		}	
		if(world->mario.decompte== 5){
			world->mario.i = 44;
		}	
	}
}

void animation_pieces(world_t *world){
	world->pieces.i = (SDL_GetTicks()/125) % 5;
}


void animation_champi(char d, ressources_t *r, int i, int decompte, int ecrase){
	int de;
	
	if(d == 'd'){
		de = decompte%11;
		if(!ecrase){
			SDL_RenderCopy(r->ecran, r->champi, &r->SrcR_champi[de], &r->DestR_champi[i]); 
		}
		else{
			SDL_RenderCopy(r->ecran, r->champi, &r->SrcR_champi[22], &r->DestR_champi[i]);
		}
	}
	if(d == 'g'){
		de = decompte%11 +12; 
		if(de == 22){
			de = 13;
		}
		if(!ecrase){
			SDL_RenderCopy(r->ecran, r->champi, &r->SrcR_champi[de], &r->DestR_champi[i]); 
		}
		else{
			SDL_RenderCopy(r->ecran, r->champi, &r->SrcR_champi[22], &r->DestR_champi[i]); 
		}
	}

}