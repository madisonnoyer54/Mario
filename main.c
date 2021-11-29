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
#include <SDL2/SDL_ttf.h>
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

	//Initialisation du monde et des ressources
	world_t world;
	ressources_t r;

	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	
	//Initialisation des données globales du monde + SDL
	init_data(&world);       
	init_for_SDL(&r, &world);      

	// Boucle principale
	while(world.gameover != 1 ){
		affichage(&r, &world);
		evenement(&r,&world);
		SDL_RenderPresent(r.ecran);
		update_timer(&world);
		SDL_Delay(10);
	}
	
	//Quitter TTF_Font
	TTF_CloseFont(r.font);
	TTF_Quit();
	
	Destroy(r);
	// Quitter SDL
	SDL_Quit();

	return 0;
}

