/**
 * \file evenements.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des evenements (en-tête).
 */

#ifndef EVENEMENTS_H
#define EVENEMENTS_H
#include "menu.h"

/**
 * \brief La fonction gère les évènements du menu du jeu 
 * \param ressources les ressources du jeu (SDL) 
 * \param menu le menu du jeu
 * \param world le monde
 */
void evenement_menu(ressources_t *ressources, menu_t *menu, world_t *world);


/**
 * \brief La fonction gère le choix du personnage
 * \param ressources les ressources du jeu (SDL) 
 * \param world le monde
 * \param x l'abscisse du clic de souris
 * \param y l'ordonnée du clic de souris
 */
void choix_mario(ressources_t *ressources, world_t *world, int x, int y);


/**
 * \brief La fonction gère les évènements du jeu 
 * \param ressources les ressources du jeu (SDL) 
 * \param world le monde
 */
void evenement(ressources_t *ressources,world_t *world);


/**
 * \brief le timer du menu
 * 
 * \param menu, le menu
 */
void timer_menu(menu_t *menu);


/**
 * \brief La fonction cherche le temps écoulé dans le jeu
 */
unsigned int timer();


/**
 * \brief La fonction met à jour le timer du jeu
 * \param world le monde
 */
void update_timer(world_t *world, menu_t *menu);


/**
 * \brief definie la graviter 
 * 
 * \param world, le monde 
 * \param ressources, les ressources du jeu  
 * \param g, le type de gravite (1 pour gravite du monde et 2 pour saut)
 */
void gravite(world_t *world, ressources_t *ressources, int g);


/**
 * \brief permet au mario de sauter 
 * \param world, le monde 
 * \param ressources, les ressources du jeu 
 */
void saut(world_t *world, ressources_t *ressources);


/**
 * \brief deplacement droite a partir de la moitie de l'ecran mario + décor
 * \param ressources, les ressources du jeu 
 * \param world, le monde 
 */
void deplacement_droite(ressources_t *ressources, world_t *world);


/**
 * \brief deplacement des elements du jeu
 * \param ressources, les ressources du jeu 
 * \param world, le monde 
 */
void deplacement_element(ressources_t *ressources, world_t *world);


/**
 * \brief deplacement des champis
 * \param r, les ressources du jeu 
 * \param world, le monde 
 */
void deplacement_champi(ressources_t *r, world_t *world);


/**
 * \brief fin de jeu
 * \param ressources, les ressources du jeu 
 * \param world, le monde 
 */
void fin_du_jeu(ressources_t *ressources, world_t *world);



#endif
