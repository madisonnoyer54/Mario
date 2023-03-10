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
	world.decompte = 0;

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
	while(!is_game_over(&world) && !is_game_win(&world) && !is_game_closed(&world)){
		// Affichage des élement 
		affichage(&r, &world);

		// Evenement du joueur 
		evenement(&r,&world);

		SDL_RenderPresent(r.ecran);

		// Mise à jour des données liée à la physique du monde
		update_data(&world, &menu, &r);
		
		// Màj de la gravite du monde
		update_gravite(&r, &world);

		// Pause de 10 ms pour controler la vitesse de rafraichissement
		SDL_Delay(10);
	}
	
	// Gestion de la fin du jeu
	fin_du_jeu(&r, &world);
	
	
	//Quitter TTF_Font
	TTF_CloseFont(r.font);
	TTF_CloseFont(r.font_menu);
	TTF_Quit();
	
	
	//Destruction des textures
	Destroy(r);
	
	
	// Quitter SDL
	SDL_Quit();
	

	return 0;
}

