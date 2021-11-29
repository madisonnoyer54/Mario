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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>



void initialisation(ressources_t *ressources, world_t *world){
	//Initialisation du nombre de vies
  	world->mario.nbVies= 3;
  
	// Variable de déplacement pour Mario 
	world->mario.y =470;
	world->mario.x =0;
	
	//Initialisation pour SDL_image
	IMG_Init(IMG_INIT_PNG);
	
	// Créer la fenêtre
	ressources->fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_RESIZABLE);

	// En cas d’erreur
	if(ressources->fenetre == NULL)
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
	}
	
	// Mettre en place un contexte de rendu de l’écran
	ressources->ecran = SDL_CreateRenderer(ressources->fenetre, -1, SDL_RENDERER_ACCELERATED);
	// Charger l’image
	ressources->fond = charger_image("ressources/fond.bmp", ressources->ecran );

	tableau_mario(ressources,world);

	init_vies(ressources);
	
	//Initialisation pour affichage du timer
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


void tableau_mario(ressources_t *ressources,world_t *world){
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


void affichage(ressources_t *ressources,world_t *world){
	

	SDL_RenderClear(ressources->ecran);
	SDL_RenderCopy(ressources->ecran, ressources->fond, NULL, NULL);
	SDL_RenderCopy(ressources->ecran, ressources->mario, &ressources->SrcR_mario[world->mario.i], &ressources->DestR_mario[world->mario.i]);
	
	for(int i=0; i<world->mario.nbVies; i++){
		SDL_RenderCopy(ressources->ecran, ressources->vie, &ressources->SrcR_vie, &ressources->DestR_vies[i]);
	}
	
	//Affichage des vies
	SDL_RenderCopy(ressources->ecran, ressources->texte_timer, NULL, &ressources->timer_pos);
	
	affiche_timer(ressources, world);
	
}


void Destroy(ressources_t ressources){
	SDL_DestroyTexture(ressources.fond);
	SDL_DestroyRenderer(ressources.ecran);
	SDL_DestroyWindow(ressources.fenetre);
}
