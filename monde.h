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
    int h;/*!< Hauteur du sprite*/
    int w;/*!< Largeur du sprite*/
    int x;/*!< Position (horizontale) de son centre */
    int y;/*!< Position (verticale) de son centre */
    int d;/*!< Direction ( g: gauche , d: droite , q: statique vers la gauche, s: statique vers la droite) */
    int i;/*!< Image a utiliser */
    int decompte;/*!< décompte du mario par rapport au nombre de tour */
    int nbVies;/*!< nb de vies du sprite */
	int couleur;/*< la couleur du mario */
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
    sprite_t walls; /*!< Champ qui correspond au tableau du sprites de murs */
    sprite_t pieces; /*!< Champ qui correspond au sprite des pieces */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    unsigned int timer; /*!< Champ pour le timer */ 
    float vy; /*!< Champ pour la vitesse */ 
	int nb_pieces; /*< Champ pour le nombre de pieces ramassees */
    int gg;/*< Champ qui indique si le joueur a gagner */
    int decompte;/*< Champ qui indique le decompte pour les champis */
    int niveau;/*< Champ qui indique le niveau */
	int fin;/*< Champ qui indique si le jeu est fini (le joueur a quitte le jeu) */
};
/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;


/**
 * \brief La fonction initialise les données du monde
 * \param world le monde
 */
void init_data(world_t *world);


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
 * \brief La fonction verifie si le jeu est ferme
 * \param world le monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_closed(world_t *world);


/**
 * \brief La fonction verifie si le jeu est gagne
 * \param world le monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_win(world_t *world);



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);


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
 * \brief La fonction vérifie si le mario a dépassé la limite haut et le replace au bord le cas échéant
 * \param sprite le sprite
 */
void high_overflow(sprite_t *sprite);


/**
 * \brief La fonction vérifie si le mario a dépassé la limite bas et le joueur perds si c'est le cas
 * \param sprite le sprite
 * \param world le monde 
 */
void low_overflow(sprite_t *sprite, world_t *world);


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
void update_data(world_t *world, menu_t *menu,ressources_t *r);


/**
 * \brief La fonction qui mets a jour la position des murs
 * \param world les données du monde
 */
void update_walls(world_t *world);


/**
 * \brief La fonction regarde si le mario a une collision avec une piece 
 * \param r , les ressources
 * \param world , le monde 
 */
void colli_pieces(ressources_t *r, world_t *world);


/**
 * \brief La fonction regarde si il y a une collision avec les murs
 * \param r, les ressources
 * \param world, le monde  
 */
void colli_walls(ressources_t *r, world_t *world);


/**
 * \brief La fonction regarde si il y a une collision avec l'arrivee
 * \param r, les ressources
 * \param world, le monde  
 */
void colli_arrive(ressources_t *r, world_t *world);


/**
 * \brief La fonction regarde si il y a une collision avec les champis
 * \param r, les ressources
 * \param world, le monde  
 */
void colli_champi(ressources_t *r, world_t *world);


/**
 * \brief La fonction verifie si mario est sur un mur
 * \param r les ressources
 * \return 1 si le oui, 0 sinon
 */
int down_collide(ressources_t *r);


/**
 * \brief La fonction verifie si le champi est sur un mur
 * \param r les ressources
 * \param c le champi a verifier
 * \return 1 si le oui, 0 sinon
 */
int down_collide_champi(ressources_t *r, int c);


/**
 * \brief La fonction verifie si mario touche le bas d'un mur
 * \param r les ressources
 * \return 1 si le oui, 0 sinon
 */
int up_collide(ressources_t *r);


/**
 * \brief La fonction met a jour la gravite
 * \param r les ressources
 * \param world le monde
 */
void update_gravite(ressources_t *r, world_t *world);


/**
 * \brief La fonction change le niveau
 * \param r les ressources
 * \param world le monde
 */
void changement_niveau(ressources_t *r, world_t *world);


/**
 * \brief met a jours toutes les collisions
 * \param r, les ressources
 * \param world, le monde 
 */
void update_colli(ressources_t *r, world_t *world);


/**
 * \brief met a jours tout les dépassement 
 * \param world, le monde 
 */
void overflow(world_t *world);
#endif
