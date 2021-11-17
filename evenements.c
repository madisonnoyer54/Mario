/**
 * \file evenements.c
 * \author Juliette Schilling / Madison Noyer.
 * \brief Module de gestion des événements.
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "graphique.h"
#include "monde.h"


unsigned int timer(){
	return (SDL_GetTicks())/1000;
}

void update_timer(world_t * world){
	if((world->gameover!=1)){
		world->timer = timer();
	}
}