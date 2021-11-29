/**
 * \file graphique.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion de l'affichage graphique (en-tête).
 */

#include "constantes.h"
#include "monde.h"

#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H



/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
 */
struct ressources_s{
    SDL_Window* fenetre;
    SDL_Renderer* ecran;
    SDL_Texture* fond;
	SDL_Texture* texte_timer;
	SDL_Texture* vie;
	TTF_Font* font; 
	SDL_Rect timer_pos;
	SDL_Rect SrcR_vie;
	SDL_Rect DestR_vies[3];
    
    // Pour gérer l'affichage du Mario 
    SDL_Texture* mario;
    SDL_Rect SrcR_mario[72];
	SDL_Rect DestR_mario[72];
};
/**
 * \brief Type qui correspond aux textures du jeu
 */
typedef struct ressources_s ressources_t;


/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu
 */
void initialisation(ressources_t *ressources, world_t *world);


/**
 * \brief Le tableau de Mario, permet de découper la plage de Sprite 
 * \param ressources les ressources du jeu
 * \param world le monde
 */
void tableau_mario(ressources_t *ressources, world_t *world);


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



/**
 * \brief La fonction detruit les textures, le window et le renderer nécessaires à l'affichage graphique du jeu
 * \param ressources les ressources du jeu (SDL) 
 */
void Destroy(ressources_t ressources);

#endif
