/**
 * \file monde.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des données du monde (en-tête).
 */


#ifndef MONDE_H
#define MONDE_H

/**
 * \brief Représentation d'un sprite du jeu 
 */
struct sprite_s{
    int x;/*!< Position (horizontale) de son centre */
    int y;/*!< Position (verticale) de son centre */
    int h;/*!< Hauteur */
    int w;/*!< Largeur */
};
/**
 * \brief Type qui correspont au sprite du jeu 
 */
typedef struct sprite_s sprite_t;


/**
 * \brief Représentation du monde du jeu
 */
struct world_s{
    sprite_t mario; /*!< Champ qui correspond au sprite de mario */
    sprite_t panel; /*!< Champ qui correspond au sprite du panneau d'arrivée */
    sprite_t walls[nb_walls]; /*!< Champ qui correspond au tableau du sprites de murs */
    sprite_t piege; /*!< Champ qui correspond au sprite du piège */
};
/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;



#endif