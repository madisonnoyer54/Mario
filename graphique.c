/**
 * \file graphique.c
 * \author Juliette Schilling / Madison Noyer.
 * \brief Module de gestion de l'affichage graphique.
**/ 

#include "fonctions_SDL.h"
#include "fonctions_fichiers.h"
#include "constantes.h"
#include "monde.h"
#include "graphique.h"
#include "animations.h"
#include "evenements.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>



void init_for_SDL(ressources_t *ressources){
	
	IMG_Init(IMG_INIT_PNG);   //Initialisation de SDL_image
	
        //Création de la fenêtre
	ressources->fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if(ressources->fenetre == NULL)      //Si erreur
	{
		printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
		SDL_Quit();
	}
	

	ressources->ecran = SDL_CreateRenderer(ressources->fenetre, -1, SDL_RENDERER_ACCELERATED);  	// Mise en place un contexte de rendu de l’écran

	//ressources->fond = charger_image("ressources/fond.bmp", ressources->ecran );          //Chargement du fond de jeu

	ressources->fond_menu = charger_image("ressources/fond_menu.bmp", ressources->ecran);    //Chargement fond de menu
	
	//Initialisation des données 
	init_vies(ressources);
	init_timer(ressources);

	init_pieces(ressources);

	init_walls(ressources);
	init_fond(ressources);

	//init_champi(ressources);

	init_arrive(ressources);

	
}

void init_fond(ressources_t *ressources){
	int tailleW_f, tailleH_f;
	ressources->fond = charger_image("ressources/map.bmp", ressources->ecran );  

	 SDL_QueryTexture(ressources->fond, NULL, NULL, &tailleW_f, &tailleH_f);

	
		ressources->SrcR_fond.x = 0;
		ressources->SrcR_fond.y = 0;
		ressources->SrcR_fond.w = tailleW_f; // Largeur de l’objet en pixels 
		ressources->SrcR_fond.h = tailleH_f; // Hauteur de l’objet en pixels 

		ressources->DestR_fond.x = 0;
		ressources->DestR_fond.y = 0;
		ressources->DestR_fond.w = tailleW_f*2; // Largeur du sprite
		ressources->DestR_fond.h = tailleH_f*2; // Hauteur du sprite
}


void init_arrive(ressources_t *ressources){
	int tailleW_r, tailleH_r;
	ressources->arrive = charger_image("ressources/arrive.png", ressources->ecran );  

	 SDL_QueryTexture(ressources->arrive, NULL, NULL, &tailleW_r, &tailleH_r);

	
		ressources->SrcR_arrive.x = 0;
		ressources->SrcR_arrive.y = 0;
		ressources->SrcR_arrive.w = tailleW_r; // Largeur de l’objet en pixels 
		ressources->SrcR_arrive.h = tailleH_r; // Hauteur de l’objet en pixels 

		ressources->DestR_arrive.x = 10;
		ressources->DestR_arrive.y = 100;
		ressources->DestR_arrive.w = tailleW_r*100; // Largeur du sprite
		ressources->DestR_arrive.h = tailleH_r*100; // Hauteur du sprite
}

void init_mario(ressources_t *ressources,world_t *world){              //appelée dans evenements.c
	int tailleW, tailleH;

	 // tableau de sprite 
	
	switch(world->mario.couleur){
		case 0:
			ressources->mario = charger_image_transparente("ressources/mario.png", ressources->ecran);
			break;
		case 1:
			ressources->mario = charger_image_transparente("ressources/marioViolet.png", ressources->ecran);
			break;
		case 2:
			ressources->mario = charger_image_transparente("ressources/marioJaune.png", ressources->ecran);
			break;
		default:   //par defaut, on applique le mario normal (rouge)
			ressources->mario = charger_image_transparente("ressources/mario.png", ressources->ecran);
			break;
	}


    
    SDL_QueryTexture(ressources->mario, NULL, NULL, &tailleW, &tailleH);
 
	int y =0;
	int a= 0;
        for(int i = 0; i < 8; i++) {
		for(int j =0; j < 9; j++){
			ressources->SrcR_mario[a].x = j* (tailleW/9) ;
			if(i<4){
				ressources->SrcR_mario[a].y = y ;
			}
			else{
				ressources->SrcR_mario[a].y = y + 3;
			}
			ressources->SrcR_mario[a].w = tailleW/9; // Largeur de l’objet en pixels 
			ressources->SrcR_mario[a].h = tailleH/8 ; // Hauteur de l’objet en pixels 

		
			a = a +1;
		}
			ressources->DestR_mario.x = world->mario.x;
			ressources->DestR_mario.y = world->mario.y;
			ressources->DestR_mario.w = tailleW/10  ; // Largeur du sprite
			ressources->DestR_mario.h = tailleH/9 ; // Hauteur du sprite
       y = y + tailleH/8;
	   
	}
	
	world->mario.i =6;

}


void init_champi(ressources_t *ressources){
	int tailleW_c, tailleH_c; 

	 // tableau de sprite 
   ressources->champi = charger_image_transparente("ressources/champi.png", ressources->ecran);
	
    
    SDL_QueryTexture(ressources->champi, NULL, NULL, &tailleW_c, &tailleH_c);

		
	int y =0;
	int a= 0;
    for(int i = 0; i < 5; i++) {
		for(int j =0; j < 5; j++){
			ressources->SrcR_champi[a].x = j* (tailleW_c/5) ;
			ressources->SrcR_champi[a].y = y ;
			ressources->SrcR_champi[a].w = tailleW_c/5; // Largeur de l’objet en pixels 
			ressources->SrcR_champi[a].h = tailleH_c/5 ; // Hauteur de l’objet en pixels 

				
			a = a +1;
		}
    	y = y + tailleH_c/5;
	}

	char** tab;
    int n, m;
	a =0;
    taille_fichier("ressources/terrain.txt",&n,&m);
    tab = lire_fichier("ressources/terrain.txt");
	ressources->nb_champi = nbChampi(tab, n, m);
	ressources->DestR_champi = malloc(ressources->nb_champi * sizeof(SDL_Rect));

		for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++){
               if('&' == tab[i][j]  ){
                    ressources->DestR_champi[a].x =  j * 28;
		            ressources->DestR_champi[a].y =  i * 29.8;
		           	ressources->DestR_champi[a].w = 38; // Largeur du sprite
		            ressources->DestR_champi[a].h = 40; // Hauteur du sprite
					a++;
                }
            }
        }

}

void init_walls(ressources_t *ressources){
	int tailleW_B, tailleH_B; 

	 // tableau de sprite 
   ressources->walls = charger_image_transparente("ressources/blocks.png", ressources->ecran);
	
    
    SDL_QueryTexture(ressources->walls, NULL, NULL, &tailleW_B, &tailleH_B);

		
	int y =0;
	int a= 0;
    for(int i = 0; i < 3; i++) {
		for(int j =0; j < 2; j++){
			ressources->SrcR_walls[a].x = j* (tailleW_B/2) ;
			ressources->SrcR_walls[a].y = y ;
			ressources->SrcR_walls[a].w = tailleW_B/2; // Largeur de l’objet en pixels 
			ressources->SrcR_walls[a].h = tailleH_B/3 ; // Hauteur de l’objet en pixels 

				
			a = a +1;
		}
    	y = y + tailleH_B/3;
	}

	char** tab;
    int n, m;
	a =0;
    taille_fichier("ressources/terrain.txt",&n,&m);
    tab = lire_fichier("ressources/terrain.txt");
	ressources->nb_walls = nbWalls(tab, n, m);
	ressources->DestR_walls = malloc(ressources->nb_walls * sizeof(SDL_Rect));

		for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++){
               if('1' == tab[i][j] || '2' == tab[i][j] || '3' == tab[i][j]  || '4' == tab[i][j] ){
                    ressources->DestR_walls[a].x =  j *tailleW_B / 6;
		            ressources->DestR_walls[a].y =  i * tailleH_B / 8;
		           	ressources->DestR_walls[a].w = tailleW_B / 6; // Largeur du sprite
		            ressources->DestR_walls[a].h = tailleH_B / 8; // Hauteur du sprite
					a++;
                }
            }
        }
}



void init_pieces(ressources_t *ressources){
	int tailleW_p, tailleH_p; 
	
	 // tableau de sprite 
   ressources->pieces = charger_image_transparente("ressources/pieces.png", ressources->ecran);
	
    
    SDL_QueryTexture(ressources->pieces, NULL, NULL, &tailleW_p, &tailleH_p);

		for(int j = 0; j < 6; j++){
			ressources->SrcR_pieces[j].x = j* (tailleW_p/5) ;
			ressources->SrcR_pieces[j].y = 0 ;
			ressources->SrcR_pieces[j].w = tailleW_p/5; // Largeur de l’objet en pixels 
			ressources->SrcR_pieces[j].h = tailleH_p ; // Hauteur de l’objet en pixels 

				
		}
	

	char **tab;
    int n, m;
	int a = 0;
    taille_fichier("ressources/terrain.txt",&n,&m);
    tab = lire_fichier("ressources/terrain.txt");
	ressources->nb_pieces = nbPieces(tab, n, m);
	ressources->DestR_pieces = malloc(ressources->nb_pieces * sizeof(SDL_Rect));


	
		for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++){
               if('*' == tab[i][j]){
                    ressources->DestR_pieces[a].x =  j *(tailleW_p*0.4)/6 ;
		            ressources->DestR_pieces[a].y =  i * (tailleH_p*3)/8 ;
		           	ressources->DestR_pieces[a].w =(tailleW_p*0.4)/6 ; // Largeur du sprite
		            ressources->DestR_pieces[a].h = (tailleH_p*3)/8; // Hauteur du sprite
					a++;
                }
            }
        }
	

	
	//Données pour l'affichage du nombre de pieces
	ressources->DestR_nb_pieces[0].x = 10;
	ressources->DestR_nb_pieces[0].y = 75;
	ressources->DestR_nb_pieces[0].w = 28 ; // Largeur du sprite
	ressources->DestR_nb_pieces[0].h = 30; // Hauteur du sprite
	
	
}


void init_timer(ressources_t *ressources){
	TTF_Init();
	ressources->font = TTF_OpenFont("ressources/arial.ttf", 26);
	TTF_SetFontStyle(ressources->font, TTF_STYLE_BOLD);
	SDL_Color color = {0,0,0,0};
	char timer[] = "Timer :";
	ressources->texte_timer = charger_texte(timer, ressources->ecran, ressources->font, color);
	int timerW, timerH;
	SDL_QueryTexture(ressources->texte_timer, NULL, NULL, &timerW, &timerH);
	ressources->timer_pos.x = 10;
	ressources->timer_pos.y = 10;
	ressources->timer_pos.w = timerW;
	ressources->timer_pos.h = timerH;
}


void init_vies(ressources_t *ressources){
  int tailleW, tailleH;
  
  //On charge l'image et on récupère sa taille
  ressources->vie = charger_image_transparente("ressources/vie.png", ressources->ecran);
  SDL_QueryTexture(ressources->vie, NULL, NULL, &tailleW, &tailleH);
  
  //On initialise les données de tailles
  ressources->SrcR_vie.x = 0;
  ressources->SrcR_vie.y = 0;
  ressources->SrcR_vie.w = tailleW;
  ressources->SrcR_vie.h = tailleH;
  
  for(int i=0; i<3; i++){
    ressources->DestR_vies[i].x = 10 + (i*(tailleW + 5));
    ressources->DestR_vies[i].y = 45;
    ressources->DestR_vies[i].w = tailleW;
    ressources->DestR_vies[i].h = tailleH;
  }
}



void affichage(ressources_t *ressources,world_t *world){
	SDL_RenderClear(ressources->ecran);        //Mise à jour de l'écran

	afficher_fond(ressources);    //Affichage du fond

	affiche_mario(ressources, world);   //Affichage du mario
	
	affiche_timer(ressources, world);      //Affichage du timer

	affiche_vies(ressources, world);       //Affichage des vies

	affiche_walls(ressources); // Affichage du murs

	affiche_pieces(ressources, world); // Affichage des pieces

	//affiche_champi(ressources);

	afficher_arrive(ressources);


	
}

void afficher_fond(ressources_t *ressources){
	SDL_RenderCopy(ressources->ecran, ressources->fond, &ressources->SrcR_fond,&ressources->DestR_fond);
}


void afficher_arrive(ressources_t *ressources){
	SDL_RenderCopy(ressources->ecran, ressources->arrive, &ressources->SrcR_arrive,&ressources->DestR_arrive);
}

void affiche_mario(ressources_t *ressources,world_t *world){
	SDL_RenderCopy(ressources->ecran, ressources->mario, &ressources->SrcR_mario[world->mario.i], &ressources->DestR_mario);
}


void affiche_timer(ressources_t *ressources, world_t *world){
	char timer[50];
	sprintf(timer, "Timer : %d", world->timer);
	
	
	SDL_Color color = {0,0,0,0};
	ressources->texte_timer = charger_texte(timer, ressources->ecran, ressources->font, color);
	int timerW, timerH;
	SDL_QueryTexture(ressources->texte_timer, NULL, NULL, &timerW, &timerH);
	ressources->timer_pos.x = 10;
	ressources->timer_pos.y = 10;
	ressources->timer_pos.w = timerW;
	ressources->timer_pos.h = timerH;

	SDL_RenderCopy(ressources->ecran, ressources->texte_timer, NULL, &ressources->timer_pos); 
}


void affiche_vies(ressources_t *ressources,world_t *world){
	for(int i=0; i<world->mario.nbVies; i++){
		SDL_RenderCopy(ressources->ecran, ressources->vie, &ressources->SrcR_vie, &ressources->DestR_vies[i]);
	}
}


void affiche_champi(ressources_t *ressources){
	char** tab; 
    int n = 0;
    int m = 0; 
	int a =0;
    taille_fichier("ressources/terrain.txt",&n,&m);
    tab = lire_fichier("ressources/terrain.txt");
		for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
        
			    if('&' == tab[i][j]){
                 	SDL_RenderCopy(ressources->ecran, ressources->champi, &ressources->SrcR_champi[1], &ressources->DestR_champi[a]); 
					a=a +1;
               }
            }
        } 
}

void affiche_walls(ressources_t *ressources){
	char** tab; 
    int n = 0;
    int m = 0; 
	int a =0;
    taille_fichier("ressources/terrain.txt",&n,&m);
    tab = lire_fichier("ressources/terrain.txt");
		for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
        
               if('1' == tab[i][j]){
                	SDL_RenderCopy(ressources->ecran, ressources->walls, &ressources->SrcR_walls[0], &ressources->DestR_walls[a]); 
					a=a +1;
                }
                if('2' == tab[i][j]){
                 	SDL_RenderCopy(ressources->ecran, ressources->walls, &ressources->SrcR_walls[1], &ressources->DestR_walls[a]); 
					a=a +1;
               } 
			    if('3' == tab[i][j]){
                 	SDL_RenderCopy(ressources->ecran, ressources->walls, &ressources->SrcR_walls[2], &ressources->DestR_walls[a]); 
					a=a +1;
               } 
			    if('4' == tab[i][j]){
                 	SDL_RenderCopy(ressources->ecran, ressources->walls, &ressources->SrcR_walls[3], &ressources->DestR_walls[a]); 
					a=a +1;
               }
            }
        } 
}


void affiche_pieces(ressources_t *ressources, world_t *world){
	animation_pieces(world);
	char** tab; 
    int n, m;
	int a = 0;
	//world_t *world;
    taille_fichier("ressources/terrain.txt",&n,&m);
    tab = lire_fichier("ressources/terrain.txt");
		for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
        
               if('*' == tab[i][j]){
                	SDL_RenderCopy(ressources->ecran, ressources->pieces, &ressources->SrcR_pieces[world->pieces.i], &ressources->DestR_pieces[a]); 
					a++;
                }
            }
        }
	
	
	char nb_pieces[50];
	sprintf(nb_pieces, "%u", world->nb_pieces);

	SDL_Color color = {0,0,0,0};
	ressources->texte_nb_pieces = charger_texte(nb_pieces, ressources->ecran, ressources->font, color);
	int nb_piecesW, nb_piecesH;
	SDL_QueryTexture(ressources->texte_nb_pieces, NULL, NULL, &nb_piecesW, &nb_piecesH);
	ressources->DestR_nb_pieces[1].x = 40;
	ressources->DestR_nb_pieces[1].y = 75;
	ressources->DestR_nb_pieces[1].w = nb_piecesW;
	ressources->DestR_nb_pieces[1].h = nb_piecesH;
	

	SDL_RenderCopy(ressources->ecran, ressources->texte_nb_pieces, NULL, &ressources->DestR_nb_pieces[1]); 
	
    SDL_RenderCopy(ressources->ecran, ressources->pieces, &ressources->SrcR_pieces[0], &ressources->DestR_nb_pieces[0]); 
}





void Destroy(ressources_t ressources){
	free(ressources.DestR_pieces);
	free(ressources.DestR_walls);


	SDL_DestroyTexture(ressources.fond);
	SDL_DestroyTexture(ressources.mario);
	SDL_DestroyTexture(ressources.vie);
	SDL_DestroyTexture(ressources.texte_timer);
	SDL_DestroyTexture(ressources.walls);
	SDL_DestroyTexture(ressources.pieces);
	SDL_DestroyTexture(ressources.champi);
	SDL_DestroyTexture(ressources.arrive);

	// Pour le menu 
	SDL_DestroyTexture(ressources.fond_menu);
	SDL_DestroyTexture(ressources.texte_menu);
	SDL_DestroyTexture(ressources.marioJaune);
	SDL_DestroyTexture(ressources.marioRouge);
	SDL_DestroyTexture(ressources.marioViolet);

	SDL_DestroyRenderer(ressources.ecran);
	SDL_DestroyWindow(ressources.fenetre);
}


int nbWalls(char** tab, int n, int m){
	int res = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(tab[i][j] == '1'  || tab[i][j] == '2' || tab[i][j] == '3' || tab[i][j] == '4'){
				res++;
			}
		}
	}
	return res;
}



int nbPieces(char** tab, int n, int m){
	int res = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(tab[i][j] == '*'){
				res++;
			}
		}
	}
	return res;
}


int nbChampi(char** tab, int n, int m){
	int res = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(tab[i][j] == '&'){
				res++;
			}
		}
	}
	return res;
}



