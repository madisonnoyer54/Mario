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



void init_data(world_t *world){
	
	// Initialisation des données utiles à la boucle de jeu
	world->gameover = 0;
	world->gg = 0;
	world->fin = 0;
	
	// Initialisation du nombre de vies
  	world->mario.nbVies= 3;
    
	// Variable de déplacement pour Mario 
	world->mario.i = 0;
	world->mario.decompte= 0;
    init_sprite(&world->mario, 15, 478, MARIO_WIDTH, MARIO_SIZE);

    // Variable initialisation piece 
    world->pieces.i=0;
    world->nb_pieces = 0;
    
	// Variable initialisation du numero de niveau
	world->niveau = 1;
	
}

void init_sprite(sprite_t *sprite, int x, int y, int w, int h) {
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;   
}

int is_game_win(world_t *world){
	return world->gg;	
}


int is_game_over(world_t *world){
    return world->gameover;
}

int is_game_closed(world_t *world){
	return world->fin;
}


void left_overflow(sprite_t *sprite) {
    if (sprite->x  < 0) {                // Si la bordure gauche dépasse le bord gauche de l'écran
        sprite->x = 0  ;
    }
}


void right_overflow(sprite_t *sprite) {
    if (sprite->x + sprite->w > SCREEN_WIDTH - 300) {     // Si la bordure droite dépasse le bord droit de l'écran
        sprite->x = (SCREEN_WIDTH - sprite->w - 300);
    }
}

void high_overflow(sprite_t *sprite){
    if(sprite->y <= 0){
        sprite->y = 0;
    }
}

void low_overflow(sprite_t *sprite,world_t *world){
    if(sprite->y >= 550){
        world->mario.nbVies--;
        world->mario.x = 0;
        world->mario.y = 200;
        printf("Vous avez perdu une vie ! Plus que %u !\n", world->mario.nbVies);
    	
    }
}


void handle_vie(world_t *world) {
    if (world->mario.nbVies <= 0) {
        world->gameover = 1;   // La partie est terminée
        world->gg = 0; // le joueur a perdu 
    }
}


void update_data(world_t *world, menu_t *menu,ressources_t *r){
    // Gestion des dépassements de l'ecran
    overflow(world);

    // Gestion de la graviter 
   
    if (!down_collide(r)){
		
		gravite(world, r, 1);
		
		if(world->mario.d == 'd' || world->mario.d == 's'){
			world->mario.i = 6;
		}
		if(world->mario.d == 'g' || world->mario.d == 'q'){
			world->mario.i = 42;
		}
	}
	
	animation_mario(world);

    // Gestion du déplacement des éléments
    world->vy = INITIAL_SPEED;

    // Gestion des collisions
    update_colli(r,world);

	// Vérifie si le joueur est en vie
    handle_vie(world);

	// Màj du timer
	update_timer(world, menu);
    
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
            r->DestR_pieces[i].x  = -225;
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
        // Les collision quand mario est a droite du mur
         if(world->mario.d == 'd'){
            if((y_m <= r->DestR_walls[i].y  && y_m + h_m - 2 >= r->DestR_walls[i].y && x_m + w_m >= r->DestR_walls[i].x && x_m + w_m <= r->DestR_walls[i].x + r->DestR_walls[i].w )
                ||( y_m <= r->DestR_walls[i].y +  r->DestR_walls[i].h && y_m + h_m - 2>= r->DestR_walls[i].y +r->DestR_walls[i].h && x_m + w_m >= r->DestR_walls[i].x  && x_m  <= r->DestR_walls[i].x)){
                world->vy = 0;
            }
        }

        // Les collision quand mario est a gauche du mur 
        if(world->mario.d == 'g'){
           if((y_m <= r->DestR_walls[i].y  && y_m + h_m - 2 >= r->DestR_walls[i].y && x_m <= r->DestR_walls[i].x + r->DestR_walls[i].w && x_m + w_m >= r->DestR_walls[i].x + r->DestR_walls[i].w)
           || (y_m <= r->DestR_walls[i].y + r->DestR_walls[i].h  && y_m + h_m - 2>= r->DestR_walls[i].y + r->DestR_walls[i].h && x_m >= r->DestR_walls[i].x + r->DestR_walls[i].w && x_m + w_m <= r->DestR_walls[i].x + r->DestR_walls[i].w )){
                world->vy = 0;
            } 
        }
    } 
}

int up_collide(ressources_t *r){
	int x_m = r->DestR_mario.x; 
    int y_m = r->DestR_mario.y;
    int h_m = r->DestR_mario.h;
    int w_m = r->DestR_mario.w;
	
	for(int i = 0; i < r->nb_walls; i++){
	// Les collision quand mario touche le dessous d'un murs 
        if((x_m <= r->DestR_walls[i].x &&  x_m + w_m >= r->DestR_walls[i].x && y_m <= r->DestR_walls[i].y + r->DestR_walls[i].h && y_m + h_m - 2>= r->DestR_walls[i].y + r->DestR_walls[i].h)
        ||(x_m <= r->DestR_walls[i].x +r->DestR_walls[i].w &&  x_m + w_m >= r->DestR_walls[i].x +r->DestR_walls[i].w && y_m <= r->DestR_walls[i].y + r->DestR_walls[i].h && y_m + h_m - 2>= r->DestR_walls[i].y + r->DestR_walls[i].h)  ){
			return 1;
        }
	}
	return 0;
}

int down_collide(ressources_t *r){
	int x_m = r->DestR_mario.x; 
    int y_m = r->DestR_mario.y;
    int h_m = r->DestR_mario.h;
    int w_m = r->DestR_mario.w;
	
	for(int i = 0; i < r->nb_walls; i++){
        if((x_m - 2 >= r->DestR_walls[i].x && x_m <= r->DestR_walls[i].x + r->DestR_walls[i].w  && y_m + h_m + 2 >= r->DestR_walls[i].y && y_m + h_m + 2<= r->DestR_walls[i].y + r->DestR_walls[i].h) 
        || (x_m + w_m - 2 >= r->DestR_walls[i].x && x_m + w_m<= r->DestR_walls[i].x + r->DestR_walls[i].w && y_m + h_m + 2 >= r->DestR_walls[i].y && y_m + h_m + 2<= r->DestR_walls[i].y + r->DestR_walls[i].h)   ){
			return 1;
        }
	}
	return 0;
}

int down_collide_champi(ressources_t *r, int c){
	int x_m = r->DestR_champi[c].x; 
    int y_m = r->DestR_champi[c].y;
    int h_m = r->DestR_champi[c].h;
    int w_m = r->DestR_champi[c].w;
	
	for(int i = 0; i < r->nb_walls; i++){
        if((x_m - 2 >= r->DestR_walls[i].x && x_m <= r->DestR_walls[i].x + r->DestR_walls[i].w  && y_m + h_m + 2 >= r->DestR_walls[i].y && y_m + h_m + 2<= r->DestR_walls[i].y + r->DestR_walls[i].h) 
        || (x_m + w_m - 2 >= r->DestR_walls[i].x && x_m + w_m<= r->DestR_walls[i].x + r->DestR_walls[i].w && y_m + h_m + 2 >= r->DestR_walls[i].y && y_m + h_m + 2<= r->DestR_walls[i].y + r->DestR_walls[i].h)   ){
			return 1;
        }
	}
	return 0;
}
	

void update_gravite(ressources_t *r, world_t *world){
	if(!down_collide(r)){
			gravite(world, r, 1);
	}
}

void colli_arrive(ressources_t *r, world_t *world){
    int x_m = r->DestR_mario.x; 
    int w_m = r->DestR_mario.w;

    if(x_m + w_m >= r->DestR_arrive.x && x_m + w_m <= r->DestR_arrive.x + r->DestR_arrive.w){
		changement_niveau(r, world);
    }  
}

void changement_niveau(ressources_t *r, world_t *world){
	if(world->niveau == 3){
		world->gg = 1;
		
	}
	else{
		world->niveau++;
	
		world->mario.nbVies = 3;
	
		world->nb_pieces = 0;
		
		world->mario.x = 15;
		
		if(world->niveau == 3){
			world->mario.y = 10;
		}
		else{
			world->mario.y = 478;
		}
		
		for(int i=0; i<r->nb_walls;i++){
			r->DestR_walls[i].x -= 2100;
		}
		
		for(int i=0; i<r->nb_pieces;i++){
			r->DestR_pieces[i].x -= 2100;
		}

		for(int i= 0; i<r->nb_champi; i++){
			r->DestR_champi[i].x -= 2100;
		}

		r->DestR_fond.x -= 2100;
	
		r->DestR_arrive.x += 6000;
	}
}


void colli_champi(ressources_t *r, world_t *world){
    int x_m = world->mario.x; 
    int y_m = world->mario.y;
    int h_m = r->DestR_mario.h;
    int w_m = r->DestR_mario.w;

    for(int i=0; i<r->nb_champi; i++){
		
        if((x_m >= r->DestR_champi[i].x && x_m <= r->DestR_champi[i].x + r->DestR_champi[i].w && h_m + y_m >= r->DestR_champi[i].y &&  y_m <= r->DestR_champi[i].y)
        || (x_m + w_m>= r->DestR_champi[i].x && x_m + w_m<= r->DestR_champi[i].x + r->DestR_champi[i].w && h_m + y_m >= r->DestR_champi[i].y &&  y_m <= r->DestR_champi[i].y)){
			if((x_m - 2 >= r->DestR_champi[i].x && x_m <= r->DestR_champi[i].x + r->DestR_champi[i].w  && y_m + h_m + 2 >= r->DestR_champi[i].y && y_m + h_m + 2<= r->DestR_champi[i].y + r->DestR_champi[i].h) 
        	|| (x_m + w_m - 2 >= r->DestR_champi[i].x && x_m + w_m<= r->DestR_champi[i].x + r->DestR_champi[i].w && y_m + h_m + 2 >= r->DestR_champi[i].y && y_m + h_m + 2<= r->DestR_champi[i].y + r->DestR_champi[i].h)   ){
				animation_champi('d', r, i, world->decompte, 1);
				r->DestR_champi[i].x = -1200;
			}
			else{
            	world->mario.nbVies--;
            	world->mario.x = 0;
            	world->mario.y = 200;
				r->DestR_mario.x = 0;
				r->DestR_mario.y = 200;
            	x_m = 0;
				y_m = 0;
				printf("Vous avez perdu une vie ! Plus que %u !\n", world->mario.nbVies);
			}
		}
    }
    
}



void update_colli(ressources_t *r, world_t *world){
    colli_pieces(r, world);
    colli_walls(r, world);
    colli_arrive(r,world);
    colli_champi(r,world);
}


void overflow(world_t *world){
    left_overflow(&(world->mario));
    right_overflow(&(world->mario));
    low_overflow(&(world->mario), world);
    high_overflow(&world->mario);
}

