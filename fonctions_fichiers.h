/**
 * \file fonctions_fichiers.h
 * \author Juliette Schilling / Madison Noyer
 * \brief Module de gestion des fonctions fichiers (en-tête).
 */
#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H

/**
 * @brief alloue le tableau 2D
 * 
 * @param n, largeur 
 * @param m, longeur 
 * @return char**, le tableau de char 
 */
char** allouer_tab_2D(int n, int m);

/**
 * @brief desalloue le tableau 2D
 * 
 * @param tab, le tableau de char
 * @param n, la largeur
 */
void desallouer_tab_2D(char** tab, int n);

/**
 * @brief affiche le tableau 2D 
 * 
 * @param tab, le tableau 
 * @param n, la largeur 
 * @param m, la hauteur 
 */
void afficher_tab_2D(char** tab, int n, int m);

/**
 * @brief taille du fichier donner 
 * 
 * @param nomFichier, le fichier
 * @param nbLig, la largeur
 * @param nbCol, la hauteur 
 */
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);

/**
 * @brief lit le fichier donner 
 * 
 * @param nomFichier, le fichier 
 * @return char**, retourne le fichier en tableau 
 */
char** lire_fichier(const char* nomFichier);

/**
 * @brief modifier un caractere dans le tableau 
 * 
 * @param tab, le tableau 
 * @param n, longeur
 * @param m, largeur
 * @param ancien, ancien caractaire
 * @param nouveau, nouveau caractaire 
 * @return char**, le nouveau tableau changer
 */
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);

/**
 * @brief ecrire le fichier 
 * 
 * @param nomFichier, le fichier donner 
 * @param tab, le tableau donner 
 * @param n, la largeur 
 * @param m, la longeur 
 */
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);



#endif