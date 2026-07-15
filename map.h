#ifndef TESTPROJECT_MAP_H
#define TESTPROJECT_MAP_H

#define WIDSPLAY 1248
#define HIDSPLAY 702
#define TILE_SIZE 60
#define NOMBRESL  9
#define NOMBRESC 17

typedef struct {
    ALLEGRO_BITMAP *decor1;
    ALLEGRO_BITMAP *cuisson;
    ALLEGRO_BITMAP *assiette;
    ALLEGRO_BITMAP *decoupe;
    ALLEGRO_BITMAP *distribassiettes;
    ALLEGRO_BITMAP *distributeurtomates;
    ALLEGRO_BITMAP *plantravail;
    ALLEGRO_BITMAP *poubelle;
    ALLEGRO_BITMAP *sortie;
    ALLEGRO_BITMAP *sol;
    ALLEGRO_BITMAP *assiettePosee;
    ALLEGRO_BITMAP *distributeurfromage;
    ALLEGRO_BITMAP *distributeurpoivrons;
    ALLEGRO_BITMAP *distributeurtortilla;
    ALLEGRO_BITMAP *distributeurviande;
    ALLEGRO_BITMAP *distributeursalade;
    ALLEGRO_BITMAP *overcooked3;
    ALLEGRO_BITMAP *gameover;
} Images;

void chargement(); // fonction pour l'ecran de chargement

void chargement2();

void lectureCuisineFichierText(int cuisine[NOMBRESL][NOMBRESC], char* filePath);

void dessinerCuisine(int cuisine[NOMBRESL][NOMBRESC], Images images); //fonction qui stocke les elements de la cuisine pour le fichier texte

#endif //TESTPROJECT_MAP_H
