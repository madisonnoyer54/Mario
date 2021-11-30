/**
 * \file monde.c
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des données du monde.
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "constantes.h"
#include "monde.h"


int is_game_over(world_t *world){
    return world->gameover;
}

void init_data(world_t *world){
	
	//Initialisation des données utiles à la boucle de jeu
	world->gameover = 0;
	
	//Initialisation du nombre de vies
  	world->mario.nbVies= 3;
  
	// Variable de déplacement pour Mario 
	world->mario.y = 470;
	world->mario.x = 0;
	world->mario.i = 0;
	world->mario.decompte= 0;

	
}


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
