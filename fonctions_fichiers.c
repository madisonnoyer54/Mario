
#include <stdlib.h>
#include <stdio.h>
#include "fonctions_fichiers.h"


char** allouer_tab_2D(int n, int m) {
    char** tab = malloc(sizeof(*tab) * n) ;
    for (int i = 0 ; i < n ; i++) {
        tab[i] = malloc(sizeof(**tab) * m) ;
    }
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            tab[i][j] = ' ' ;
        }
    }
    return tab;
}


void desallouer_tab_2D(char** tab, int n){
    for(int i=0; i<n ; i++){
        free(tab[i]);
    }
    free(tab);
}


void afficher_tab_2D(char** tab, int n, int m){
    for(int i=0; i<n ; i++){
        for(int j=0; j<m ; j++){
                printf("%c",tab[i][j]);   
        }
        printf("\n");
    }  
}


void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol) { 
    int c, n = 0 ; 
    int m = 0; 
    int i = 0;
    FILE * ptrFichier=fopen (nomFichier,"r"); 
    if (ptrFichier==NULL) 
        perror ("Error opening file"); 
    else { 
        do { 
            c = fgetc (ptrFichier) ;
            if (c == '\n') {
                n++;
                if (i > m) {
                    m = i;
                }
                i = 0 ;
            } else if (c != 13){
                i++;
            }
        }   while (c != EOF); 
        fclose (ptrFichier); 
        *nbLig = n ;
        *nbCol = m ;
    }
}


char** lire_fichier(const char* nomFichier) {
    int* n = malloc(sizeof(n)) ;
    int* m = malloc(sizeof(m)) ;
    taille_fichier(nomFichier, &n, &m) ;
    char** tab = allouer_tab_2D(n, m);
    FILE* ptrFichier = fopen(nomFichier, "r") ;
    if (ptrFichier==NULL) 
        perror ("Error opening file");
    else {
        int i = 0, j = 0 ;
        char c ;
        c = fgetc (ptrFichier) ;
        while (c != EOF) {
            if (c == '\n') {
                j = 0 ;
                i++ ;
            } else if (c != 13){
                tab[i][j] = c ;
                j++ ;
            }
            c = fgetc (ptrFichier) ;
        }
        fclose(ptrFichier) ;
    }
    return tab ;
}


char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tab[i][j] == ancien) {
                tab[i][j] = nouveau ;
            }
        }
    }
    return tab ;
}

void ecrire_fichier(const char* nomFichier, char** tab, int n, int m) {
    FILE * pFile;
    pFile=fopen(nomFichier,"w"); 
    if (pFile==NULL) 
        perror ("Error opening file"); 
    else { 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fputc (tab[i][j],pFile); 
                if (ferror (pFile)) 
                    perror ("Error Writing to nomFichier\n"); 
            }
            fputc ('\n',pFile); 
        }
        fclose (pFile) ;
    } 
}







