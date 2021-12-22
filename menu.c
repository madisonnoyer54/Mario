/**
 * \file menu.c
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion du menu de jeu
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.h"
#include "fonctions_SDL.h"


void init_menu(menu_t *menu, ressources_t *ressources){
	
	ressources->font_menu = TTF_OpenFont("ressources/Minecraft.ttf", 50);
	SDL_Color color = {0,0,0,0};
	ressources->texte_menu = charger_texte("CHOISISSEZ VOTRE PERSONNAGE", ressources->ecran, ressources->font_menu, color);
	int texteW, texteH;
	SDL_QueryTexture(ressources->texte_menu, NULL, NULL, &texteW, &texteH); //On récupère hauteur et largeur de l'image de 6 sprites
	
	ressources->texte_menu_pos.x = SCREEN_WIDTH/2 - texteW/2;
	ressources->texte_menu_pos.y = 100;
	ressources->texte_menu_pos.w = texteW; // Largeur du texte en pixels 
	ressources->texte_menu_pos.h = texteH; // Hauteur du texte en pixels 
	
	// à mettre dans une fonction à part 
	int tailleW, tailleH;
	
	ressources->marioRouge = charger_image_transparente("ressources/marioRMenu.png", ressources->ecran);
	SDL_QueryTexture(ressources->marioRouge, NULL, NULL, &tailleW, &tailleH);
	ressources->SrcR_marioMenu[0].x = 0;
	ressources->SrcR_marioMenu[0].y = 0;
	ressources->SrcR_marioMenu[0].w = tailleW;
	ressources->SrcR_marioMenu[0].h = tailleH;
	ressources->DestR_marioMenu[0].x = SCREEN_WIDTH/2 - tailleW/2;
	ressources->DestR_marioMenu[0].y = 220;
	ressources->DestR_marioMenu[0].w = tailleW;
	ressources->DestR_marioMenu[0].h = tailleH;
	
	ressources->marioViolet = charger_image_transparente("ressources/marioVMenu.png", ressources->ecran);
	SDL_QueryTexture(ressources->marioViolet, NULL, NULL, &tailleW, &tailleH);
	ressources->SrcR_marioMenu[1].x = 0;
	ressources->SrcR_marioMenu[1].y = 0;
	ressources->SrcR_marioMenu[1].w = tailleW;
	ressources->SrcR_marioMenu[1].h = tailleH;
	ressources->DestR_marioMenu[1].x = SCREEN_WIDTH/2 - tailleW/2 - 80;
	ressources->DestR_marioMenu[1].y = 220;
	ressources->DestR_marioMenu[1].w = tailleW;
	ressources->DestR_marioMenu[1].h = tailleH;
	
	ressources->marioJaune = charger_image_transparente("ressources/marioJMenu.png", ressources->ecran);
	SDL_QueryTexture(ressources->marioJaune, NULL, NULL, &tailleW, &tailleH);
	ressources->SrcR_marioMenu[2].x = 0;
	ressources->SrcR_marioMenu[2].y = 0;
	ressources->SrcR_marioMenu[2].w = tailleW;
	ressources->SrcR_marioMenu[2].h = tailleH;
	ressources->DestR_marioMenu[2].x = SCREEN_WIDTH/2 - tailleW/2 + 80;
	ressources->DestR_marioMenu[2].y = 220;
	ressources->DestR_marioMenu[2].w = tailleW;
	ressources->DestR_marioMenu[2].h = tailleH;
	
	menu->fin = 0;
}

void affiche_menu(ressources_t *ressources){
	SDL_RenderCopy(ressources->ecran, ressources->fond_menu, NULL, NULL);   //Affichage du fond de jeu
	affiche_texte_menu(ressources);
	
	SDL_RenderCopy(ressources->ecran, ressources->marioRouge, &ressources->SrcR_marioMenu[0], &ressources->DestR_marioMenu[0]);
	SDL_RenderCopy(ressources->ecran, ressources->marioViolet, &ressources->SrcR_marioMenu[1], &ressources->DestR_marioMenu[1]);
	SDL_RenderCopy(ressources->ecran, ressources->marioJaune, &ressources->SrcR_marioMenu[2], &ressources->DestR_marioMenu[2]);
	
}

void affiche_texte_menu(ressources_t *ressources){
	SDL_RenderCopy(ressources->ecran, ressources->texte_menu, NULL, &ressources->texte_menu_pos);
}