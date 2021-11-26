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