/**
 * \file graphique.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion de l'affichage graphique (en-tête).
 */


#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#endif



/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
 */
struct ressources_s{
    SDL_Window* fenetre;
    SDL_Renderer* ecran;
    SDL_Texture* fond;
    SDL_Texture* mario;
    SDL_Rect  SrcR_mario[72] ;
	SDL_Rect  DestR_mario[72];
};
/**
 * \brief Type qui correspond aux textures du jeu
 */
typedef struct ressources_s ressources_t;

void initialisation(ressources_t *ressources);

void tableau_mario(ressources_t *ressources, world_t *world);

void affichage(ressources_t *ressources);

void evenement(ressources_t *ressources,world_t *world);

void Destroy(ressources_t ressources);