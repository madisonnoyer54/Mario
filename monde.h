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
    int h;/*!< Hauteur */
    int w;/*!< Largeur */
    int x;/*!< Position (horizontale) de son centre */
    int y;/*!< Position (verticale) de son centre */
    int d;/*!< Direction ( g: gauche , d: droite , q: statique vers la gauche, s: statique vers la droite) */
    int i;/*!< Mario a utiliser */
    int decompte;/*!< décompte du mario par rapport au nombre de tour */
    int nbVies;/*!< nb de vies du sprite */
	int couleur;
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
    sprite_t walls; /*!< Champ qui correspond au tableau du sprites de murs */
    sprite_t piege; /*!< Champ qui correspond au sprite du piège */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    unsigned int timer; /*!< Champ pour le timer */ 
    float vy; /*!< Champ pour la vitesse */ 
  
};
/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;


/**
 * \brief La fonction initialise les données d'un sprite
 * \param sprite le sprite
 * \param x l'abscisse du centre du sprite
 * \param y l'ordonnée du centre du sprite
 * \param w la largeur du sprite
 * \param h la hauteur du sprite
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h);


/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);

/**
 * \brief La fonction initialise les données du monde
 * \param world le monde
 */
void init_data(world_t *world);


/**
 * \brief La fonction vérifie si le mario a dépassé la limite gauche et le replace au bord le cas échéant
 * \param sprite le sprite
 */
void left_overflow(sprite_t *sprite);


/**
 * \brief La fonction vérifie si le mario a dépassé la limite droite et le replace au bord le cas échéant
 * \param sprite le sprite
 */
void right_overflow(sprite_t *sprite);


/**
 * \brief La fonction vérifie la vie du joueur et si elle est épuisée, fait perdre la partie
 * \param world les données du monde
 */
void handle_vie(world_t *world);



#include "menu.h"



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t *world, menu_t *menu);


/**
 * \brief La fonction donne leur position initiale aux murs de météorites dans le monde pour former des couloirs
 * \param world les données du monde
 */
void init_walls(world_t *world);


/**
 * \brief La fonction qui mets a jour la position des murs
 * \param world les données du monde
 */
void update_walls(world_t *world);



#endif
