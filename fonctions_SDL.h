/**
 * \file fonctions_SDL.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des fonctions SDL (en-tête).
 */

#ifndef FONCTIONS_SDL_H
#define FONCTIONS_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/**
 * \brief La fonction permet de charger l'image 
 * \param nomfichier nom de l'image a charger 
 * \param renderer le renderer 
 * \return returne la texture 
 */
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer);


/**
 * \brief La fonction permet de charger l'image avec le fond transparent 
 * \param nomfichier nom de l'image a charger 
 * \param renderer le renderer 
 * \return returne la texture 
 */
SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer);


/**
 * \brief La fonction permet de charger le texte 
 * \param message message a charger 
 * \param renderer le renderer 
 * \param font le police à utiliser
 * \param color la couleur à utiliser 
 * \return returne la texture 
 */
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) ;



#endif