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
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "animations.h"
#include "evenements.h"
#include "menu.h"


/** 
*   \brief programme principal qui implémente la boucle de jeu
*/
int main(){

	//Initialisation du monde et des ressources
	world_t world;
	ressources_t r;
	menu_t menu;

	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}


	//Initialisation des données globales du monde + SDL
	init_data(&world); 
	init_for_SDL(&r);  
	init_menu(&menu, &r);
	
	
	//Boucle de menu
	while(menu.fin != 1){
	  affiche_menu(&r);
	  evenement_menu(&r, &menu, &world);
	  SDL_RenderPresent(r.ecran);
	  SDL_Delay(10);
	}
	   
	    

	// Boucle principale
	while(!is_game_over(&world)){
		// Affichage des élement 
		affichage(&r, &world);

		// evenement du joueur 
		evenement(&r,&world);

		SDL_RenderPresent(r.ecran);

		// Mise à jour des données liée à la physique du monde
		update_data(&world, &menu, &r);

		// Pause de 10 ms pour controler la vitesse de rafraichissement
		SDL_Delay(10);
	}
	
	//Quitter TTF_Font
	TTF_CloseFont(r.font);
	//TTF_CloseFont(r.fond_menu);
	TTF_Quit();
	
	Destroy(r);
	// Quitter SDL
	SDL_Quit();

	return 0;
}

