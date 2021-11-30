/**
 * \file graphique.c
 * \author Juliette Schilling / Madison Noyer.
 * \brief Module de gestion de l'affichage graphique.
**/ 

#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "animations.h"
#include "evenements.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>



void init_for_SDL(ressources_t *ressources, world_t *world){
	
	IMG_Init(IMG_INIT_PNG);   //Initialisation de SDL_image
	
        //Création de la fenêtre
	ressources->fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if(ressources->fenetre == NULL)      //Si erreur
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
	}
	

	ressources->ecran = SDL_CreateRenderer(ressources->fenetre, -1, SDL_RENDERER_ACCELERATED);  	// Mise en place un contexte de rendu de l’écran

	ressources->fond = charger_image("ressources/fond.bmp", ressources->ecran );          //Chargement du fond de jeu

	//Initialisation des données
	init_mario(ressources,world);      
	init_vies(ressources);
	init_timer(ressources);
}


void init_mario(ressources_t *ressources,world_t *world){
	int tailleW, tailleH;

	 // tableau de sprite 
   ressources->mario = charger_image_transparente("ressources/mario.png", ressources->ecran);

    
    SDL_QueryTexture(ressources->mario, NULL, NULL, &tailleW, &tailleH);
 
	int y =0;
	int a= 0;
        for(int i = 0; i < 8; i++) {
		for(int j =0; j < 9; j++){
			ressources->SrcR_mario[a].x = j* (tailleW/9) ;
			ressources->SrcR_mario[a].y = y ;
			ressources->SrcR_mario[a].w = tailleW/9; // Largeur de l’objet en pixels 
			ressources->SrcR_mario[a].h = tailleH/8 ; // Hauteur de l’objet en pixels 

			ressources->DestR_mario[a].x = world->mario.x;
			ressources->DestR_mario[a].y = world->mario.y;
			ressources->DestR_mario[a].w = tailleW/9  ; // Largeur du sprite
			ressources->DestR_mario[a].h = tailleH/8 ; // Hauteur du sprite
			a = a +1;
		}
       y = y + tailleH/8;
	   
	}

}


void init_timer(ressources_t *ressources){
	TTF_Init();
	ressources->font = TTF_OpenFont("ressources/arial.ttf", 26);
	TTF_SetFontStyle(ressources->font, TTF_STYLE_BOLD);
	SDL_Color color = {0,0,0,0};
	char timer[] = "Timer :";
	ressources->texte_timer = charger_texte(timer, ressources->ecran, ressources->font, color);
	int timerW, timerH;
	SDL_QueryTexture(ressources->texte_timer, NULL, NULL, &timerW, &timerH);
	ressources->timer_pos.x = 10;
	ressources->timer_pos.y = 10;
	ressources->timer_pos.w = timerW;
	ressources->timer_pos.h = timerH;
}


void init_vies(ressources_t *ressources){
  int tailleW, tailleH;
  
  //On charge l'image et on récupère sa taille
  ressources->vie = charger_image_transparente("ressources/vie.png", ressources->ecran);
  SDL_QueryTexture(ressources->vie, NULL, NULL, &tailleW, &tailleH);
  
  //On initialise les données de tailles
  ressources->SrcR_vie.x = 0;
  ressources->SrcR_vie.y = 0;
  ressources->SrcR_vie.w = tailleW;
  ressources->SrcR_vie.h = tailleH;
  
  for(int i=0; i<3; i++){
    ressources->DestR_vies[i].x = 10 + (i*(tailleW + 5));
    ressources->DestR_vies[i].y = 45;
    ressources->DestR_vies[i].w = tailleW;
    ressources->DestR_vies[i].h = tailleH;
  }
}


void affichage(ressources_t *ressources,world_t *world){
	SDL_RenderClear(ressources->ecran);        //Mise à jour de l'écran

	SDL_RenderCopy(ressources->ecran, ressources->fond, NULL, NULL);   //Affichage du fond de jeu

	affiche_mario(ressources, world);   //Affichage du mario
	
	//affiche_timer(ressources, world);      //Affichage du timer

	affiche_vies(ressources, world);       //Affichage des vies
	
}


void affiche_mario(ressources_t *ressources,world_t *world){
	SDL_RenderCopy(ressources->ecran, ressources->mario, &ressources->SrcR_mario[world->mario.i], &ressources->DestR_mario[world->mario.i]);
}


void affiche_timer(ressources_t *ressources, world_t *world){
	char timer[50];
	sprintf(timer, "Timer : %d", world->timer);
	
	
	SDL_Color color = {0,0,0,0};
	ressources->texte_timer = charger_texte(timer, ressources->ecran, ressources->font, color);
	int timerW, timerH;
	SDL_QueryTexture(ressources->texte_timer, NULL, NULL, &timerW, &timerH);
	ressources->timer_pos.x = 10;
	ressources->timer_pos.y = 10;
	ressources->timer_pos.w = timerW;
	ressources->timer_pos.h = timerH;

	SDL_RenderCopy(ressources->ecran, ressources->texte_timer, NULL, &ressources->timer_pos); 
}

void affiche_vies(ressources_t *ressources,world_t *world){
	for(int i=0; i<world->mario.nbVies; i++){
		SDL_RenderCopy(ressources->ecran, ressources->vie, &ressources->SrcR_vie, &ressources->DestR_vies[i]);
	}
}


void Destroy(ressources_t ressources){
	SDL_DestroyTexture(ressources.fond);
	//SDL_DestroyTexture(ressources.mario);
	//SDL_DestroyTexture(ressources.vie);
	SDL_DestroyTexture(ressources.texte_timer);

	SDL_DestroyRenderer(ressources.ecran);
	SDL_DestroyWindow(ressources.fenetre);
	
}
