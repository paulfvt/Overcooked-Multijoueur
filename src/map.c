#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "map.h"

void chargement(){ // fonction de l'ecran de chargement

    // Création d'une fenêtre
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_COLOR noir = al_map_rgb(0,0,0);

    background = al_load_bitmap("../assets/Image/overcooked4.jpg");
    al_draw_bitmap(background, 0, 0, 0);

    //barre de chargement
    for (int i = 780; i < 1210; i++) {
        for(int z = 10; z < 1240; z++)
            al_draw_rectangle(i, 655, 1210, 680, noir, 5);
        al_flip_display();

    }
    //al_rest(2);
    al_flip_display();
    al_destroy_bitmap(background);

}


void chargement2(){ // fonction de l'ecran de chargement

    // Création d'une fenêtre
    ALLEGRO_BITMAP *background2 = NULL;
    ALLEGRO_COLOR noir = al_map_rgb(0,0,0);

    background2 = al_load_bitmap("../assets/Image/chargement2.png");
    al_draw_bitmap(background2, 0, 0, 0);

    //barre de chargement
    for (int i = 380; i < 830; i++) {
        for(int z = 10; z < 940; z++)
            al_draw_rectangle(i, 655, 830, 680, noir, 5);
        al_flip_display();

    }
    //al_rest(3);
    al_flip_display();
    al_destroy_bitmap(background2);

}




void lectureCuisineFichierText(int cuisine[NOMBRESL][NOMBRESC], char* filePath) {
    FILE *niveau = fopen(filePath, "r");
    assert(niveau != NULL); // Vérifiez si le fichier est ouvert avec succès

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 17; ++j) {
            char caractere;
            if (fscanf(niveau, " %c", &caractere) == 1) {
                cuisine[i][j] = caractere;
            } else {
                printf("Erreur de lecture du fichier.\n");
                return;
            }
        }
    }
    fclose(niveau);
}

#define NOMBREL 9
#define NOMBREC 17

void dessinerCuisine(int cuisine[NOMBRESL][NOMBRESC], Images images) {
    // Dessin de la cuisine
    float x = 0, y = 0;
    for (int i = 0; i < NOMBRESL; ++i) {
        for (int j = 0; j < NOMBRESC; ++j) {
            char caractere = (char)cuisine[i][j]; // Caractère de la case du tableau
            ALLEGRO_BITMAP *bitmap = NULL;

            switch (caractere) {
                case 'a':
                    bitmap = images.decor1;
                    break;
                case 'b':
                    bitmap = images.sol;
                    break;
                case 'c':
                    bitmap = images.assiette;
                    break;
                case 'd':
                    bitmap = images.decoupe;
                    break;
                case 'e':
                    bitmap = images.distribassiettes;
                    break;
                case 'f':
                    bitmap = images.distributeurtomates;
                    break;
                case 'g':
                    bitmap = images.plantravail;
                    break;
                case 'h':
                    bitmap = images.poubelle;
                    break;
                case 'i':
                    bitmap = images.cuisson;
                    break;
                case 'j':
                    bitmap = images.assiettePosee;
                    break;
                case 'k':
                    bitmap = images.sortie;
                    break;
                case 'l':
                    bitmap = images.distributeurfromage;
                    break;
                case 'm':
                    bitmap = images.distributeurpoivrons;
                    break;
                case 'n':
                    bitmap = images.distributeurtortilla;
                    break;
                case 'o':
                    bitmap = images.distributeurviande;
                    break;
                case 'p':
                    bitmap = images.distributeursalade;
                    break;
                case '\n':
                    x = 0;
                    y++;
                    break;
            }
            if (bitmap != NULL) {
                al_draw_bitmap(bitmap, x * TILE_SIZE + 114 , y * TILE_SIZE + 81 , 0);
            }
            x++; // Déplacer vers la droite pour le prochain élément
        }
        x = 0;
        y++;
    }
}

