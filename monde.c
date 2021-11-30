/**
 * \file monde.c
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des données du monde.
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "animations.h"
#include "evenements.h"


void init_sprite(sprite_t *sprite, int x, int y, int w, int h) {
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;   
}


int is_game_over(world_t *world){
    return world->gameover;
}

void init_data(world_t *world){
	
	//Initialisation des données utiles à la boucle de jeu
	world->gameover = 0;
	
	//Initialisation du nombre de vies
  	world->mario.nbVies= 3;

 
  
	// Variable de déplacement pour Mario 
	world->mario.i = 0;
	world->mario.decompte= 0;
    init_sprite(&world->mario,0,470,3,6);

	
}


void left_overflow(sprite_t *sprite) {
    if (sprite->x - sprite->w / 2 < 0) {        // Si la bordure gauche dépasse le bord gauche de l'écran
        sprite->x = (sprite->w/2);
    }
}


void right_overflow(sprite_t *sprite) {
    printf("  %d",sprite->x);
    if (sprite->x + sprite->w / 2 > 1130) {     // Si la bordure droite dépasse le bord droit de l'écran
        sprite->x = 1130;
    }
}


void handle_vie(world_t *world) {
    if (world->mario.nbVies <= 0) {
        world->gameover = 1;    // La partie est terminée
    }
}


void update_data(world_t *world){
    // Gestion des dépassements à gauche et à droite
    left_overflow(&(world->mario));
    right_overflow(&(world->mario));

    // Gestion des collisions
   


    // Gestion du déplacement des éléments

	// vérifie si le joueur est en vie
    handle_vie(world);

	// vérifie le timer
	update_timer(world);
}


