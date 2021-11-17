/**
 * \file main.c
 * \author Juliette Schilling / Madison Noyer
 * \brief Programme principal
 */

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "evenements.h"


/** 
*   \brief programme principal qui implémente la boucle de jeu
*/
int main(){
	world_t world;
	ressources_t r;
	world.gameover = 0;
	

	// Variable de déplacement pour Mario 
	world.mario.y =460;
	world.mario.x =0;

	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	IMG_Init(IMG_INIT_PNG);
	initialisation(&r);
	tableau_mario(&r,&world);

	// Boucle principale
	while(world.gameover != 1 ){
		affichage(&r);
		evenement(&r,&world);
		SDL_RenderPresent(r.ecran);
		update_timer(&world);
		//printf("%u\n", world.timer);
	}

	Destroy(r);
	// Quitter SDL
	SDL_Quit();

	return 0;
}

