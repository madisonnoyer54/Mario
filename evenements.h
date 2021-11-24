/**
 * \file evenements.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des evenements (en-tête).
 */

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

/**
 * \brief La fonction gère les évènements du jeu 
 * \param ressources les ressources du jeu (SDL) 
 * \param world le monde
 */
void evenement(ressources_t *ressources,world_t *world);

/**
 * \brief La fonction cherche le temps écoulé dans le jeu
 */
unsigned int timer();

/**
 * \brief La fonction met à jour le timer du jeu
 * \param world le monde
 */
void update_timer(world_t * world);

/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu (SDL) 
 * \param world le monde
 */
void evenement(ressources_t *ressources,world_t *world);

#endif