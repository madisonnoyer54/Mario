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
#include "graphique.h"
#include "animations.h"
#include "evenements.h"
#include "menu.h" 


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

    // variable initialisation piece 
    world->pieces.i=0;
    world->nb_pieces = 0;
    

   

	
}


void left_overflow(sprite_t *sprite) {
    if (sprite->x  < 0) {                // Si la bordure gauche dépasse le bord gauche de l'écran
        sprite->x = 0  ;
    }
}


void right_overflow(sprite_t *sprite) {
    if (sprite->x + sprite->w > SCREEN_WIDTH) {     // Si la bordure droite dépasse le bord droit de l'écran
        sprite->x = (SCREEN_WIDTH - sprite->w);
    }
}


void handle_vie(world_t *world) {
    if (world->mario.nbVies <= 0) {
        world->gameover = 1;   // La partie est terminée
    }
}


void update_data(world_t *world, menu_t *menu,ressources_t *r){
    // Gestion des dépassements à gauche et à droite
    left_overflow(&(world->mario));
    right_overflow(&(world->mario));

    // Gestion e la graviter 
   

 


    // Gestion du déplacement des éléments
    world->vy = INITIAL_SPEED;


    // Gestion des collisions
    colli_pieces(r, world);
    colli_walls(r, world);
   

	// vérifie si le joueur est en vie
    handle_vie(world);

	// vérifie le timer
	update_timer(world, menu);

    // vérifier les murs 
    
}


void colli_pieces(ressources_t *r, world_t *world){
    int x_m = r->DestR_mario.x; 
    int y_m = r->DestR_mario.y;
    int h_m = r->DestR_mario.h;
    int w_m = r->DestR_mario.w;

    for(int i = 0; i < r->nb_pieces; i++){
        if( (x_m <= r->DestR_pieces[i].x && r->DestR_pieces[i].x <= x_m + w_m && r->DestR_pieces[i].y <= y_m +h_m && y_m <= r->DestR_pieces[i].y)
            ||  (x_m <= r->DestR_pieces[i].x && r->DestR_pieces[i].x <= x_m + w_m && r->DestR_pieces[i].y + r->DestR_pieces[i].h <= y_m +h_m && y_m <= r->DestR_pieces[i].y + r->DestR_pieces[i].h)
            ||  (x_m <= r->DestR_pieces[i].x + r->DestR_pieces[i].w && r->DestR_pieces[i].x + r->DestR_pieces[i].w <= x_m + w_m && r->DestR_pieces[i].y <= y_m +h_m && y_m <= r->DestR_pieces[i].y)
            ||  (x_m <= r->DestR_pieces[i].x +r->DestR_pieces[i].w && r->DestR_pieces[i].x + r->DestR_pieces[i].w <= x_m + w_m && r->DestR_pieces[i].y + r->DestR_pieces[i].h<= y_m +h_m && y_m <= r->DestR_pieces[i].y + r->DestR_pieces[i].h)){
            r->DestR_pieces[i].x  = -25;
            world->nb_pieces++;
           
       }
    }
}

void colli_walls(ressources_t *r, world_t *world){
    int x_m = r->DestR_mario.x; 
    int y_m = r->DestR_mario.y;
    int h_m = r->DestR_mario.h;
    int w_m = r->DestR_mario.w;

    for(int i = 0; i < r->nb_walls; i++){
        // Les collision quand mario est a droite avec le coter du murs 
         if(world->mario.d == 'd'){
            if((y_m <= r->DestR_walls[i].y  && y_m + h_m - 2>= r->DestR_walls[i].y && x_m + w_m >= r->DestR_walls[i].x && x_m + w_m <= r->DestR_walls[i].x + r->DestR_walls[i].w )
                ||( y_m <= r->DestR_walls[i].y +  r->DestR_walls[i].h && y_m + h_m - 2>= r->DestR_walls[i].y +r->DestR_walls[i].h && x_m + w_m >= r->DestR_walls[i].x  && x_m  <= r->DestR_walls[i].x)){
                world->vy = 0;
            }
        }

        // Les collision quand mario est a gauche avec le coter du murs 
        if(world->mario.d == 'g'){
           if((y_m <= r->DestR_walls[i].y  && y_m + h_m - 2>= r->DestR_walls[i].y && x_m <= r->DestR_walls[i].x + r->DestR_walls[i].w && x_m + w_m >= r->DestR_walls[i].x + r->DestR_walls[i].w)
           || (y_m <= r->DestR_walls[i].y + r->DestR_walls[i].h  && y_m + h_m - 2>= r->DestR_walls[i].y + r->DestR_walls[i].h && x_m >= r->DestR_walls[i].x + r->DestR_walls[i].w && x_m + w_m <= r->DestR_walls[i].x + r->DestR_walls[i].w )){
                world->vy = 0;
            } 
        }

         /*
        // Les collision quand mario touche le dessous d'un murs 
        if((x_m <= r->DestR_walls[i].x &&  x_m + w_m >= r->DestR_walls[i].x && y_m <= r->DestR_walls[i].y + r->DestR_walls[i].h && y_m + h_m - 2>= r->DestR_walls[i].y + r->DestR_walls[i].h)
        ||(x_m <= r->DestR_walls[i].x +r->DestR_walls[i].w &&  x_m + w_m >= r->DestR_walls[i].x +r->DestR_walls[i].w && y_m <= r->DestR_walls[i].y + r->DestR_walls[i].h && y_m + h_m - 2>= r->DestR_walls[i].y + r->DestR_walls[i].h)  ){
           // r->DestR_walls[i].y = 6;
           world->mario.y= r->DestR_walls[i].y + r->DestR_walls[i].h;
           
        }
        // Les collision quand mario touche le dessus d'un murs 
        if((x_m >= r->DestR_walls[i].x && x_m <= r->DestR_walls[i].x + r->DestR_walls[i].w && y_m + h_m - 2<= r->DestR_walls[i].y) 
        || (x_m + w_m>= r->DestR_walls[i].x && x_m + w_m<= r->DestR_walls[i].x + r->DestR_walls[i].w && y_m + h_m - 2<= r->DestR_walls[i].y)   ){
          // world->mario.s = 1;
        }*/

    }

    
}