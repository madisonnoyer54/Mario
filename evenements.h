/**
 * \file evenements.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des evenements (en-tête).
 */

#ifndef EVENEMENTS_H
#define EVENEMENTS_H

void evenement(ressources_t *ressources,world_t *world);

unsigned int timer();

void update_timer(world_t * world);

#endif