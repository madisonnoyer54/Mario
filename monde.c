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

    init_tab_world(world);
	

	// Variable de déplacement pour Mario 
	world->mario.i = 0;
	world->mario.decompte= 0;
	int n, m;
	pos_tab_mario(world, &n, &m);
	world->tab_initial[n][m] = ' ';

        init_sprite(&world->mario, m*BLOCK_SIZE, n*BLOCK_SIZE, 2*BLOCK_SIZE, 2*BLOCK_SIZE);

    // variable initialisation piece 
    world->pieces.i=0;
	
	world->mario.x_tab = world->mario.x;
	
}


void init_tab_world(world_t *world){
    world->tab = lire_fichier("ressources/terrain.txt");
	
    world->tab_initial = lire_fichier("ressources/terrain.txt");
}


void pos_tab_mario(world_t *world, int *n, int *m){
    int a, b;
    taille_fichier("ressources/terrain.txt", &a, &b);
	for(int i=0; i<a; i++){
		for(int j=0; j<b; j++){
			if(world->tab[i][j] == 'm'){
				*n = i;
				*m = j;
			}
		}
	}
}


void update_pos_mario_tab(world_t *world){
    int a, b;
    taille_fichier("ressources/terrain.txt", &a, &b);
	
	supprimer_occ_tab(world, a, b, 'm');
	
	world->mario.x_tab = world->mario.x + world->defilement;
	
	int x = (world->mario.x_tab / BLOCK_SIZE) +2;
	int y = world->mario.y / BLOCK_SIZE;
	
	world->tab[y][x] = 'm';
	
	
	afficher_tab_2D(world->tab, a, b);
}



void supprimer_occ_tab(world_t *world, int n, int m, char c){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(world->tab[i][j] == c){
				world->tab[i][j] = world->tab_initial[i][j];
			}
		}
	}
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


void update_data(world_t *world, ressources_t *ressources, menu_t *menu){
    // Gestion des dépassements à gauche et à droite
    left_overflow(&(world->mario));
    right_overflow(&(world->mario));


	update_pos_mario_tab(world);
	

    // Gestion de la graviter 
	//gravite(world, ressources);
   

    // Gestion des collisions
   


    // Gestion du déplacement des éléments
   

	// vérifie si le joueur est en vie
    handle_vie(world);

	// vérifie le timer
	update_timer(world, menu);

    // vérifier les murs 
    
}


int nbWalls(char** tab, int n, int m){
	int res = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(tab[i][j] == '1'  || tab[i][j] == '2' || tab[i][j] == '3' || tab[i][j] == '4'){
				res++;
			}
		}
	}
	return res;
}



int nbPieces(char** tab, int n, int m){
	int res = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(tab[i][j] == '*'){
				res++;
			}
		}
	}
	return res;
}


int est_sur_un_mur(world_t *world){
	int x, y;
	pos_tab_mario(world, &y, &x);
	if(world->tab[y+2][x] == '2' || world->tab[y+2][x] == '1' || world->tab[y+2][x] == '3' || world->tab[y+2][x] == '4'){
		return 1;
	}
	return 0;
}

/*
int sprites_collide(sprite_t *sp1, sprite_t *sp2) {
    if(){ // touche du coter
        return 1;
    }
    if(){ //toucher en bas
        return 2;
    }
    if(){ //toucher en haut
        return 3;
    }
    return 0;
}
*/

/*
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world, int type) {
    // Gestion du temps qui s'écoule 
    if (sprites_collide(sp1, sp2) == 1 || sprites_collide(sp1, sp2) == 2 || sprites_collide(sp1, sp2) == 3) {
        
        // Collision avec un mur 
        if (type == 1) {    
          
        } 

        // Collision avec l'arrivée
        if (type == 0) {    
      
        } 

        // Collision avec un champi
        if (type == 2) {   
           
        }


        // Collision avec la piece 
        if (type == 4) {    
            
        }
    }
}

*/

