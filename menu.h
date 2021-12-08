/**
 * \file menu.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion du menu du jeu
 */


#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL_ttf.h>


/**
 * \brief Representation du menu 
 */
struct menu_s{
    int fin;/*!< Indique si le menu est fini ou pas */
	unsigned int timer_menu; /*< Représente le temps ecoule sur le menu */
};
/**
 * \brief Type qui correspont au menu du jeu 
 */
typedef struct menu_s menu_t;

#include "graphique.h"

void init_menu(menu_t *menu, ressources_t *ressources);

void affiche_menu(ressources_t *ressources);

void affiche_texte_menu(ressources_t *ressources);


#endif