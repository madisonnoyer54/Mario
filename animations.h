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


#endif