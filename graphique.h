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

	//gérer l'affichage du fond
   	SDL_Texture* fond;
	SDL_Rect SrcR_fond;
	SDL_Rect DestR_fond;

	TTF_Font* font; 
	
	//Gérer l'affichage du menu
	SDL_Texture* fond_menu;
	SDL_Texture* texte_menu;
	TTF_Font* font_menu;
	SDL_Rect texte_menu_pos;
	
	SDL_Texture* marioRouge;
	SDL_Texture* marioViolet;
	SDL_Texture* marioJaune;
	SDL_Rect SrcR_marioMenu[3];
	SDL_Rect DestR_marioMenu[3];

	//Gérer affichage du timer
	SDL_Texture* texte_timer;
	SDL_Rect timer_pos;

	//Gérer affichage des vies
	SDL_Texture* vie;
	SDL_Rect SrcR_vie;
	SDL_Rect DestR_vies[3];
    
  	// Pour gérer l'affichage du Mario 
   	SDL_Texture* mario;
   	SDL_Rect SrcR_mario[72];
	SDL_Rect DestR_mario;

	// Pour gérer l'affichage des murs
	SDL_Texture* walls;
	SDL_Rect ScrR_walls[4];
	SDL_Rect DestR_walls[200];
	int nb_walls;
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

void init_fond(ressources_t *ressources);

/**
 * \brief Initialise le tableau de Mario, permet de découper la plage de Sprite 
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void init_mario(ressources_t *ressources, world_t *world);


/**
 * \brief Initialise des murs de Mario, permet de découper la plage de Sprite 
 * \param ressources les ressources du jeu
 */
void init_block(ressources_t *ressources);


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
 * \brief La fonction affiche les textures nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu
 */
void affichage(ressources_t *ressources, world_t *world);

void afficher_fond(ressources_t *ressources);

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
 * \brief Gère l'affichage des vies
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_vies(ressources_t *ressources,world_t *world);


/**
 * \brief Gère l'affichage des murs
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void affiche_walls(ressources_t *ressources);


/**
 * \brief La fonction detruit les textures, le window et le renderer nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu (SDL) 
 */
void Destroy(ressources_t ressources);

#endif
