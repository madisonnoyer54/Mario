/**
 * \file animations.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des animations (en-tête).
 */

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <SDL2/SDL.h>
#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "animations.h"
#include "evenements.h"

/**
 * \brief La fonction gère l'animation du mario
 * \param world le monde
 */
void animation_mario(world_t *world);


/**
 * \brief La fonction gère l'animation des pieces
 * \param world le monde
 */
void animation_pieces(world_t *world);

/**
 * \brief La fonction gère l'animation des champis
 * \param d la direction du champi
 * \param r les ressources
 * \param i le numero de champi à animer
 * \param decompte le decompte
 * \param ecrase si le champi s'ecrase (1) ou pas (0)
 */
void animation_champi(char d, ressources_t *r, int i, int decompte, int ecrase);


#endif