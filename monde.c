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
    init_sprite(&world->mario,0,470,MARIO_WIDTH,MARIO_SIZE);


    // Variable pour les Murs 
    //init_walls(world);
     init_sprite(&(world->walls), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, WALLS_SIZE, WALLS_SIZE);

    world->vy =3;

	
}


void left_overflow(sprite_t *sprite) {
    if (sprite->x - sprite->w / 2 < 0) {                // Si la bordure gauche dépasse le bord gauche de l'écran
        sprite->x = (sprite->w/2);
    }
}


void right_overflow(sprite_t *sprite) {
    if (sprite->x + sprite->w / 2 > SCREEN_WIDTH) {     // Si la bordure droite dépasse le bord droit de l'écran
        sprite->x = (SCREEN_WIDTH - sprite->w/2);
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

    // vérifier les murs 
    update_walls(world);
}

/*
void init_walls(world_t *world){
    // Les differents murs de météorites 
    init_sprite(&world->walls[0],48,0,96,192); 
    init_sprite(&world->walls[1],252,0,96,192);
    init_sprite(&world->walls[2],16,-352,32,160);
    init_sprite(&world->walls[3],188,-352,224,160);
    init_sprite(&world->walls[4],48,-672,96,192);
    init_sprite(&world->walls[5],252,-672,96,192);
}*/


void update_walls(world_t *world) {
    // Murs de météorites de 0 à 5 
    for(int i=0; i<nb_walls; i++){
        // Gestion des collisions
        
        
        // Gestion du déplacement des éléments
        world->walls.x += world->vy;
    }
}

