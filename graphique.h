/**
 * \file graphique.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion de l'affichage graphique (en-tête).
 */



#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "constantes.h"


/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
 */
struct ressources_s{
   	SDL_Window* fenetre;
   	SDL_Renderer* ecran;

	//Gestion de l'affichage du fond
   	SDL_Texture* fond;
	SDL_Rect SrcR_fond;
	SDL_Rect DestR_fond;

	//Font generale du jeu
	TTF_Font* font; 
	
	//Gestion de l'affichage du menu
	SDL_Texture* fond_menu;
	SDL_Texture* texte_menu;
	TTF_Font* font_menu;
	SDL_Rect texte_menu_pos;
	
	SDL_Texture* marioRouge;
	SDL_Texture* marioViolet;
	SDL_Texture* marioJaune;
	SDL_Rect SrcR_marioMenu[3];
	SDL_Rect DestR_marioMenu[3];

	//Gestion de l'affichage du timer
	SDL_Texture* texte_timer;
	SDL_Rect timer_pos;

	//Gestion de l'affichage des vies
	SDL_Texture* vie;
	SDL_Rect SrcR_vie;
	SDL_Rect DestR_vies[3];
    
  	//Gestion de l'affichage du Mario 
   	SDL_Texture* mario;
   	SDL_Rect SrcR_mario[72];
	SDL_Rect DestR_mario;

	//Gestion de l'affichage des murs
	SDL_Texture* walls;
	SDL_Rect SrcR_walls[6];
	SDL_Rect* DestR_walls;
	int nb_walls;

	//Gestion de l'affichage des pieces
	SDL_Texture* pieces;
	SDL_Rect SrcR_pieces[6];
	SDL_Rect* DestR_pieces;
	SDL_Rect DestR_nb_pieces[2];
	SDL_Texture* texte_nb_pieces;
	int nb_pieces;

	//Gestion de l'affichage des champis
	SDL_Texture* champi;
	SDL_Rect SrcR_champi[23];
	SDL_Rect* DestR_champi;
	int nb_champi;

	//Gestion de l'affichage de l'arrive
	SDL_Texture* arrive;
	SDL_Rect SrcR_arrive;
	SDL_Rect DestR_arrive;
	
	//Gestion de l'affichage du num de niveau
	SDL_Texture* texte_niv;
	SDL_Rect niv_pos;

	//Gestion de l'affichage du texte de fin
	SDL_Texture* texte_fin;
	SDL_Rect fin_pos;

};
/**
 * \brief Type qui correspond aux textures du jeu
 */
typedef struct ressources_s ressources_t;


#include "monde.h"


/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu
 */
void init_for_SDL(ressources_t *ressources);


/**
 * \brief initialise le fond du jeux 
 * \param ressources, les ressources du jeu 
 */
void init_fond(ressources_t *ressources);


/**
 * \brief Initialisation de l'arriver
 * \param ressources , les ressources
 */
void init_arrive(ressources_t *ressources);


/**
 * \brief Initialise le tableau de Mario, permet de découper la plage de Sprite 
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void init_mario(ressources_t *ressources, world_t *world);


/**
 * \brief Initialise les champignon, permet de découper la plage de sprite 
 * \param ressources, les ressources
 */
void init_champi(ressources_t *ressources);

/**
 * \brief Initialise des murs de Mario, permet de découper la plage de Sprite 
 * \param ressources les ressources du jeu
 */
void init_walls(ressources_t *ressources);


/**
 * \brief Initialise des piece de Mario, permet de découper la plage de Sprite 
 * \param ressources les ressources du jeu
 */
void init_pieces(ressources_t *ressources);


/**
 * \brief La fonction initialise le timer
 * \param ressources les ressources du jeu
 */
void init_timer(ressources_t *ressources);



/**
 * \brief La fonction initialise les données SDL pour l'affichage des vies
 * \param ressources les ressources du jeu
 */
void init_vies(ressources_t *ressources);


/**
 * \brief La fonction affiche nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu
 */
void affichage(ressources_t *ressources, world_t *world);


/**
 * \brief La fonction affiche le fond du jeu
 * \param ressources les ressources du jeu
 */
void afficher_fond(ressources_t *ressources);


/**
 * \brief gére l'affichage de l'arriver
 * \param ressources , les ressources
 */
void afficher_arrive(ressources_t *ressources);


/**
 * \brief Gère l'affichage du mario
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_mario(ressources_t *ressources,world_t *world);


/**
 * \brief Gère l'affichage du timer
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_timer(ressources_t *ressources,world_t *world);


/**
 * \brief Gère l'affichage du numero de niveau
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_niveau(ressources_t *ressources, world_t *world);


/**
 * \brief Gère l'affichage des vies
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_vies(ressources_t *ressources,world_t *world);


/**
 * \brief gére l'affichage du champignon 
 * \param ressources, les ressources
 */
void affiche_champi(ressources_t *ressources, world_t *world);


/**
 * \brief Gère l'affichage des murs
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_walls(ressources_t *ressources);


/**
 * \brief Gère l'affichage des pieces
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_pieces(ressources_t *ressources, world_t *world);


/**
 * \brief La fonction detruit les textures, le window et le renderer nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu (SDL) 
 */
void Destroy(ressources_t ressources);


/**
 * \brief retourne le nombre de murs dans le tableau
 * \param tab le tableau de caractères
 * \param n la hauteur du tableau
 * \param m la largeur du tableau
 */
int nbWalls(char** tab, int n, int m);

/**
 * \brief retourne le nombre d'etoile dans le tableau
 * \param tab le tableau de caractères
 * \param n la hauteur du tableau
 * \param m la largeur du tableau
 */
int nbPieces(char** tab, int n, int m);

/**
 * \brief retourne le nombre de champignon dans le tableau
 * \param tab, le tableau 
 * \param n , la hauteur du tableau 
 * \param m , la largeur du tableau 
 * \return int , le nombre de champi
 */
int nbChampi(char** tab, int n, int m);

#endif
