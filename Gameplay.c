#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Gameplay.h"
#include "joueur.h"
#include "map.h"
#include "Ingredient.h"
#define SOL 'b'
#define ASSIETTE 'c'
#define DECOUPE 'd'
#define DISTRIBASSIETTE 'e'
#define DISTRIBTOMATE 'f'
#define PLANDETRAVAIL 'g'
#define POUBELLE 'h'
#define CUISSON 'i'
#define ASSIETTEPOSEE 'j'
#define SORTIE 'k'
#define DISTRIBFROMAGE 'l'
#define DISTRIBPOIVRONS 'm'
#define DISTRIBTORTILLA 'n'
#define DISTRIBVIANDE 'o'
#define DISTRIBSALADE 'p'

#define TEMPSNEWORDER1 40
#define TEMPSNEWORDER2 80




void dessinerTout(joueur* joueur1, joueur* joueur2,cafard* cafard, ALLEGRO_BITMAP* gif_frames_cafard[], int* frame_actuelle_cafard,balle* balle1, balle* balle2, int cuisine[9][17],Images images,ImagesIngredients imagesIngredients,bool flags [12],ALLEGRO_FONT* font, int temps, File *fileClients, int score){

    float gif_cafard_x = cafard->x - al_get_bitmap_width(gif_frames_cafard[*frame_actuelle_cafard]) / 2;
    float gif_cafard_y = cafard->y - al_get_bitmap_height(gif_frames_cafard[*frame_actuelle_cafard]) / 2;


    al_draw_bitmap(images.decor1, 0, 0, 0);
    dessinerCuisine(cuisine,images);
    DessinerSaisirAssiette(joueur1,joueur2,images);
    DessinerSaisirtomates(joueur1,joueur2,imagesIngredients);
    DessinerSaisirfromage(joueur1,joueur2,imagesIngredients);
    DessinerSaisirpoivron(joueur1, joueur2, imagesIngredients);
    DessinerSaisirtortilla(joueur1, joueur2, imagesIngredients);
    DessinerSaisirviande(joueur1, joueur2, imagesIngredients);
    DessinerSaisirsalade(joueur1, joueur2, imagesIngredients);
    dessinerTomateDecoupe(joueur1,joueur2,imagesIngredients);
    dessinerPoivronDecoupe(joueur1, joueur2, imagesIngredients);
    dessinerFromageDecoupe(joueur1, joueur2, imagesIngredients);
    dessinerViandeCuite(joueur1, joueur2, imagesIngredients);


    //dessin cafard
    al_draw_bitmap(gif_frames_cafard[*frame_actuelle_cafard], gif_cafard_x, gif_cafard_y, 0);
    //dessin boule de neige
    al_draw_filled_circle(balle1->x1,balle1->y1, 10, al_map_rgb(190,190,190));
    al_draw_filled_circle(balle2->x1,balle2->y1, 10, al_map_rgb(190,190,190));

    al_draw_rotated_bitmap(joueur1->image, al_get_bitmap_width(joueur1->image) / 2, al_get_bitmap_height(joueur1->image) / 2, joueur1->x, joueur1->y, DEG_TO_RAD(joueur1->angle), 0);
    al_draw_rotated_bitmap(joueur2->image, al_get_bitmap_width(joueur2->image) / 2, al_get_bitmap_height(joueur2->image) / 2, joueur2->x, joueur2->y, DEG_TO_RAD(joueur2->angle), 0);

    al_draw_textf(font, al_map_rgb(255, 255, 255), 20,  675, 0, "Temps : (%d s)", temps);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 190, 675, 0, "Coordonnées(j1) : (%d, %d)", joueur1->x, joueur1->y);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 420, 675, 0, "Coordonnées(j2) : (%d, %d)", joueur2->x, joueur2->y);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 705, 675, 0, "Case(j1) : (%d, %d)", (joueur1->cx - 114) / 60, (joueur1->cy - 81) / 60);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 850, 675, 0, "Case(j2) : (%d, %d)", (joueur2->cx - 114) / 60, (joueur2->cy - 81) / 60);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 1100,  675, 0, "Score : (%d)", score);

    afficherCommande(fileClients,font);

    al_flip_display();
}

/*
void EntrerSpeudo(ALLEGRO_DISPLAY* dispaly,Images images){
    images.overcooked3 = al_load_bitmap("../assets/Image/overcooked3.png");
    al_draw_bitmap(images.overcooked3,0,0,0);
}
*/

void liberer_gif_cafard(ALLEGRO_BITMAP **gif_frames, int nombre_frames) {
    for (int i = 0; i < nombre_frames; i++) {
        if (gif_frames[i] != NULL) {
            al_destroy_bitmap(gif_frames[i]);
            gif_frames[i] = NULL;
        }
    }
}

void liberation(ALLEGRO_BITMAP **gif_frames, int nombre_frames, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* fifo, ALLEGRO_SAMPLE* sample, ALLEGRO_BITMAP *menu, ALLEGRO_BITMAP *scoreboard, ALLEGRO_EVENT_QUEUE *scoreboard_fifo, Images images, ImagesIngredients imagesIngredients, ALLEGRO_FONT* font,joueur* joueur1, joueur* joueur2,File *fileCommande) {
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(fifo);
    al_destroy_sample(sample);
    liberer_gif_cafard(gif_frames, nombre_frames);
    freeFile(fileCommande);
    al_destroy_bitmap(menu);
    al_destroy_bitmap(scoreboard);
    al_destroy_event_queue(scoreboard_fifo);

    al_destroy_font(font);

    al_destroy_bitmap(menu);
    al_destroy_bitmap(scoreboard);
    al_destroy_bitmap(joueur1->image);
    al_destroy_bitmap(joueur2->image);

    al_destroy_bitmap(images.decor1);
    al_destroy_bitmap(images.poubelle);
    al_destroy_bitmap(images.plantravail);
    al_destroy_bitmap(images.cuisson);
    al_destroy_bitmap(images.distributeurtomates);
    al_destroy_bitmap(images.distribassiettes);
    al_destroy_bitmap(images.sol);
    al_destroy_bitmap(images.sortie);
    al_destroy_bitmap(images.decoupe);
    al_destroy_bitmap(images.assiette);
    al_destroy_bitmap(images.distributeurfromage);
    al_destroy_bitmap(images.distributeurpoivrons);
    al_destroy_bitmap(images.gameover);

    al_destroy_bitmap(imagesIngredients.tomate);
    al_destroy_bitmap(imagesIngredients.tomatedecoupe);
    al_destroy_bitmap(imagesIngredients.pain);
    al_destroy_bitmap(imagesIngredients.fromage);
    al_destroy_bitmap(imagesIngredients.sauce);
    al_destroy_bitmap(imagesIngredients.viande);
    al_destroy_bitmap(imagesIngredients.viandecuite);
    al_destroy_bitmap(imagesIngredients.poivrons);
    al_destroy_bitmap(imagesIngredients.poivronsdecoupe);
}


void DessinerSaisirAssiette(joueur* joueur1,joueur* joueur2, Images images){
    if (joueur1->assiette == true) {
        float assiettex = joueur1->cx - al_get_bitmap_width(images.assiette) / 2.0;
        float assiettey = joueur1->cy - al_get_bitmap_height(images.assiette) / 2.0;
        al_draw_bitmap(images.assiette, assiettex, assiettey, 0);
    }
    if (joueur2->assiette == true) {
        float assiettex = joueur2->cx - al_get_bitmap_width(images.assiette) / 2.0;
        float assiettey = joueur2->cy - al_get_bitmap_height(images.assiette) / 2.0;
        al_draw_bitmap(images.assiette, assiettex, assiettey, 0);
    }

}

void DessinerSaisirtomates(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients){
    if (joueur1->tomate == true) {
        float tomatex = joueur1->cx - al_get_bitmap_width(imagesIngredients.tomate) / 2.0;
        float tomatey = joueur1->cy - al_get_bitmap_height(imagesIngredients.tomate) / 2.0;
        al_draw_bitmap(imagesIngredients.tomate, tomatex, tomatey, 0);
    }
    if (joueur2->tomate == true) {
        float tomatex = joueur2->cx - al_get_bitmap_width(imagesIngredients.tomate) / 2.0;
        float tomatey = joueur2->cy - al_get_bitmap_height(imagesIngredients.tomate) / 2.0;
        al_draw_bitmap(imagesIngredients.tomate, tomatex, tomatey, 0);
    }

}

void DessinerSaisirfromage(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients){
    if (joueur1->fromage == true) {
        float fromagex = joueur1->cx - al_get_bitmap_width(imagesIngredients.fromage) / 2.0;
        float fromagey = joueur1->cy - al_get_bitmap_height(imagesIngredients.fromage) / 2.0;
        al_draw_bitmap(imagesIngredients.fromage, fromagex, fromagey, 0);
    }
    if (joueur2->fromage == true) {
        float fromagex = joueur2->cx - al_get_bitmap_width(imagesIngredients.fromage) / 2.0;
        float fromagey = joueur2->cy - al_get_bitmap_height(imagesIngredients.fromage) / 2.0;
        al_draw_bitmap(imagesIngredients.fromage, fromagex, fromagey, 0);
    }

}

void DessinerSaisirpoivron(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients){
    if (joueur1->poivrons == true) {
        float poivronx = joueur1->cx - al_get_bitmap_width(imagesIngredients.poivrons) / 2.0;
        float poivrony = joueur1->cy - al_get_bitmap_height(imagesIngredients.poivrons) / 2.0;
        al_draw_bitmap(imagesIngredients.poivrons, poivronx, poivrony, 0);
    }
    if (joueur2->poivrons == true) {
        float poivronx = joueur2->cx - al_get_bitmap_width(imagesIngredients.poivrons) / 2.0;
        float poivrony = joueur2->cy - al_get_bitmap_height(imagesIngredients.poivrons) / 2.0;
        al_draw_bitmap(imagesIngredients.poivrons, poivronx, poivrony, 0);
    }

}

void DessinerSaisirtortilla(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients){
    if (joueur1->tortilla == true) {
        float tortillax = joueur1->cx - al_get_bitmap_width(imagesIngredients.tortilla) / 2.0;
        float tortillay = joueur1->cy - al_get_bitmap_height(imagesIngredients.tortilla) / 2.0;
        al_draw_bitmap(imagesIngredients.tortilla, tortillax, tortillay, 0);
    }
    if (joueur2->tortilla == true) {
        float tortillax = joueur2->cx - al_get_bitmap_width(imagesIngredients.tortilla) / 2.0;
        float tortillay = joueur2->cy - al_get_bitmap_height(imagesIngredients.tortilla) / 2.0;
        al_draw_bitmap(imagesIngredients.tortilla, tortillax, tortillay, 0);
    }

}

void DessinerSaisirviande(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients){
    if (joueur1->viande == true) {
        float viandex = joueur1->cx - al_get_bitmap_width(imagesIngredients.viande) / 2.0;
        float viandey = joueur1->cy - al_get_bitmap_height(imagesIngredients.viande) / 2.0;
        al_draw_bitmap(imagesIngredients.viande, viandex, viandey, 0);
    }
    if (joueur2->viande == true) {
        float viandex = joueur2->cx - al_get_bitmap_width(imagesIngredients.viande) / 2.0;
        float viandey = joueur2->cy - al_get_bitmap_height(imagesIngredients.viande) / 2.0;
        al_draw_bitmap(imagesIngredients.viande, viandex, viandey, 0);
    }

}

void DessinerSaisirsalade(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients){
    if (joueur1->salade == true) {
        float saladex = joueur1->cx - al_get_bitmap_width(imagesIngredients.salade) / 2.0;
        float saladey = joueur1->cy - al_get_bitmap_height(imagesIngredients.salade) / 2.0;
        al_draw_bitmap(imagesIngredients.salade, saladex, saladey, 0);
    }
    if (joueur2->salade== true) {
        float saladex = joueur2->cx - al_get_bitmap_width(imagesIngredients.salade) / 2.0;
        float saladey = joueur2->cy - al_get_bitmap_height(imagesIngredients.salade) / 2.0;
        al_draw_bitmap(imagesIngredients.salade, saladex, saladey, 0);
    }

}

void dessinerTomateDecoupe(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients) {
    if (joueur1->tomatedecoupe == true){
        float tomatex = joueur1->cx - al_get_bitmap_width(imagesIngredients.tomatedecoupe) / 2.0;
        float tomatey = joueur1->cy - al_get_bitmap_height(imagesIngredients.tomatedecoupe) / 2.0;
        al_draw_bitmap(imagesIngredients.tomatedecoupe, tomatex, tomatey, 0);
    }

    if (joueur2->tomatedecoupe == true) {
        float tomatex = joueur2->cx - al_get_bitmap_width(imagesIngredients.tomatedecoupe) / 2.0;
        float tomatey = joueur2->cy - al_get_bitmap_height(imagesIngredients.tomatedecoupe) / 2.0;
        al_draw_bitmap(imagesIngredients.tomatedecoupe, tomatex, tomatey, 0);
    }
}

void dessinerPoivronDecoupe(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients) {
    if (joueur1->poivronsdecoupe == true){
        float poivronsx = joueur1->cx - al_get_bitmap_width(imagesIngredients.poivronsdecoupe) / 2.0;
        float poivronsy = joueur1->cy - al_get_bitmap_height(imagesIngredients.poivronsdecoupe) / 2.0;
        al_draw_bitmap(imagesIngredients.poivronsdecoupe, poivronsx, poivronsy, 0);
    }

    if (joueur2->poivronsdecoupe == true) {
        float poivronsx = joueur2->cx - al_get_bitmap_width(imagesIngredients.poivronsdecoupe) / 2.0;
        float poivronsy = joueur2->cy - al_get_bitmap_height(imagesIngredients.poivronsdecoupe) / 2.0;
        al_draw_bitmap(imagesIngredients.poivronsdecoupe, poivronsx, poivronsy, 0);
    }
}

void dessinerFromageDecoupe(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients) {
    if (joueur1->fromagedecoupe == true){
        float fromagex = joueur1->cx - al_get_bitmap_width(imagesIngredients.fromagedecoupe) / 2.0;
        float fromagey = joueur1->cy - al_get_bitmap_height(imagesIngredients.fromagedecoupe) / 2.0;
        al_draw_bitmap(imagesIngredients.fromagedecoupe, fromagex, fromagey, 0);
    }

    if (joueur2->fromagedecoupe == true) {
        float poivronsx = joueur2->cx - al_get_bitmap_width(imagesIngredients.fromagedecoupe) / 2.0;
        float poivronsy = joueur2->cy - al_get_bitmap_height(imagesIngredients.fromagedecoupe) / 2.0;
        al_draw_bitmap(imagesIngredients.fromagedecoupe, poivronsx, poivronsy, 0);
    }
}

void dessinerViandeCuite(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients) {
    if (joueur1->viandecuite == true){
        float viandecuitex = joueur1->cx - al_get_bitmap_width(imagesIngredients.viandecuite) / 2.0;
        float viandecuitey = joueur1->cy - al_get_bitmap_height(imagesIngredients.viandecuite) / 2.0;
        al_draw_bitmap(imagesIngredients.viandecuite, viandecuitex, viandecuitey, 0);
    }

    if (joueur2->viandecuite == true) {
        float viandecuitex = joueur2->cx - al_get_bitmap_width(imagesIngredients.viandecuite) / 2.0;
        float viandecuitey = joueur2->cy - al_get_bitmap_height(imagesIngredients.viandecuite) / 2.0;
        al_draw_bitmap(imagesIngredients.viandecuite, viandecuitex, viandecuitey, 0);
    }
}

void saisirAssiette(joueur* joueur1,joueur* joueur2, Images images, bool flags[12],int cuisine[NOMBRESL][NOMBRESC]){

    int caseX = (joueur1->cx - 114) / 60; //le curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; //le curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;

    if (flags[E] == true){


        if(cuisine[caseY][caseX] == DISTRIBASSIETTE){
            joueur1->assiette = true;
        }
        else if(cuisine[caseY][caseX] == POUBELLE){
            joueur1->assiette = false;
        }
        else if(cuisine[caseY][caseX] == PLANDETRAVAIL && joueur1->assiette){
            cuisine[caseY][caseX] = ASSIETTEPOSEE;
            joueur1->assiette = false; // le joueur n'a plus l'assiette
        }

        else if(cuisine[caseY][caseX] == ASSIETTEPOSEE){
            cuisine[caseY][caseX] = PLANDETRAVAIL;
            joueur1->assiette = true; // le joueur reprends l'assiette
        }
        else if(cuisine[caseY][caseX] == SORTIE){
            joueur1->assiette = false; // le joueur n'a plus l'assiette
        }
    }


    if (flags[P] == true ){
        if(cuisine[caseB][caseA] == DISTRIBASSIETTE){
            joueur2->assiette = true;
        }
        else if(cuisine[caseB][caseA] == POUBELLE){
            joueur2->assiette = false;
        }
        else if(cuisine[caseB][caseA] == PLANDETRAVAIL && joueur2->assiette){
            cuisine[caseB][caseA] = ASSIETTEPOSEE;
            joueur2->assiette = false; // le joueur n'a plus l'assiette
        }

        else if(cuisine[caseB][caseA] == ASSIETTEPOSEE){
            cuisine[caseB][caseA] = PLANDETRAVAIL;
            joueur2->assiette = true; // le joueur reprends l'assiette
        }
        else if(cuisine[caseB][caseA] == SORTIE){
            joueur2->assiette = false; // le joueur n'a plus l'assiette
        }
    }
}

void decouperTomate(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]){
    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;

    if(flags[R] == true && joueur1->tomate == true && cuisine[caseY][caseX] == DECOUPE ){
        joueur1->tomate = false;
        joueur1->tomatedecoupe = true;
    }

    if(flags[E] == true && joueur1->tomatedecoupe == true && cuisine[caseY][caseX] == POUBELLE){
        joueur1->tomatedecoupe = false;
    }
    if(flags[E] == true && joueur1->tomatedecoupe == true && cuisine[caseY][caseX] == SORTIE){
        joueur1->tomatedecoupe = false;
    }

    if(flags[O] == true && joueur2-> tomate == true && cuisine[caseB][caseA] == DECOUPE){
        joueur2->tomate = false;
        joueur2->tomatedecoupe = true;
    }

    if(flags[P] == true && joueur2->tomatedecoupe == true && cuisine[caseB][caseA] == POUBELLE){
        joueur2->tomatedecoupe = false;
    }
    if(flags[P] == true && joueur2->tomatedecoupe == true && cuisine[caseB][caseA] == SORTIE){
        joueur2->tomatedecoupe = false;
    }
}

void decouperPoivron(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]){
    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;

    if(flags[R] == true && joueur1->poivrons == true && cuisine[caseY][caseX] == DECOUPE){
        joueur1->poivrons = false;
        joueur1->poivronsdecoupe = true;
    }
    if(flags[E] == true && joueur1->poivronsdecoupe == true && cuisine[caseY][caseX] == POUBELLE){
        joueur1->poivronsdecoupe = false;
    }
    if(flags[E] == true && joueur1->poivronsdecoupe == true && cuisine[caseY][caseX] == SORTIE){
        joueur1->poivronsdecoupe = false;
    }

    if(flags[O] == true && joueur2-> poivrons == true && cuisine[caseB][caseA] == DECOUPE){
        joueur2->poivrons = false;
        joueur2->poivronsdecoupe = true;
    }
    if(flags[P] == true && joueur2->poivronsdecoupe == true && cuisine[caseB][caseA] == POUBELLE){
        joueur2->poivronsdecoupe = false;
    }
    if(flags[P] == true && joueur2->poivronsdecoupe == true && cuisine[caseB][caseA] == SORTIE){
        joueur2->poivronsdecoupe = false;
    }
}

void decouperFromage(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]){
    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;

    if(flags[R] == true && joueur1->fromage == true && cuisine[caseY][caseX] == DECOUPE){
        joueur1->fromage = false;
        joueur1->fromagedecoupe = true;
    }
    if(flags[E] == true && joueur1->fromagedecoupe == true && cuisine[caseY][caseX] == POUBELLE){
        joueur1->fromagedecoupe = false;
    }
    if(flags[E] == true && joueur1->fromagedecoupe == true && cuisine[caseY][caseX] == SORTIE){
        joueur1->fromagedecoupe = false;
    }

    if(flags[O] == true && joueur2-> fromage == true && cuisine[caseB][caseA] == DECOUPE ){
        joueur2->fromage = false;
        joueur2->fromagedecoupe = true;
    }
    if(flags[P] == true && joueur2->fromagedecoupe == true && cuisine[caseB][caseA] == POUBELLE){
        joueur2->fromagedecoupe = false;
    }
    if(flags[P] == true && joueur2->fromagedecoupe == true && cuisine[caseB][caseA] == SORTIE){
        joueur2->fromagedecoupe = false;
    }
}

void cuireViande(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]){
    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;

    if(flags[R] == true && joueur1->viande == true && cuisine[caseY][caseX] == CUISSON){
        joueur1->viande = false;
        joueur1->viandecuite = true;
    }
    if(flags[E] == true && joueur1->viandecuite == true && cuisine[caseY][caseX] == POUBELLE){
        joueur1->viandecuite = false;
    }
    if(flags[E] == true && joueur1->viandecuite == true && cuisine[caseY][caseX] == SORTIE){
        joueur1->viandecuite = false;
    }

    if(flags[O] == true && joueur2-> viande == true && cuisine[caseB][caseA] == CUISSON ){
        joueur2->viande = false;
        joueur2->viandecuite = true;
    }
    if(flags[P] == true && joueur2->viandecuite == true && cuisine[caseB][caseA] == POUBELLE){
        joueur2->viandecuite = false;
    }
    if(flags[P] == true && joueur2->viandecuite == true && cuisine[caseB][caseA] == SORTIE){
        joueur2->viandecuite = false;
    }
}


/*
void tempsAttentePreparationAliment(ALLEGRO_DISPLAY* display, int cuisine [NOMBRESL][NOMBRESC]) {
    const int duree_attente = 10; // Durée d'attente en secondes
    const int nombre_etapes = 100; // Nombre d'étapes pour la barre de chargement
    const float attente_par_etape = (float) duree_attente / nombre_etapes;

    int etape_actuelle = 0;

    for (int i = 0; i < nombre_etapes; ++i) {
        // Dessiner la barre de chargement
        float chargement = (float) etape_actuelle / nombre_etapes;
        int longueur_barre = chargement * 10;
        al_draw_filled_rectangle(posX, posY, posX + longueur_barre, posY + hauteur, al_map_rgb(255, 255, 255));
    }
}*/


void saisirTomate(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]) {

    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;


    if (flags[E] == true ) {
        if (cuisine[caseY][caseX] == DISTRIBTOMATE) {
            joueur1->tomate = true;
        }
        else if (cuisine[caseY][caseX] == POUBELLE) {
            joueur1->tomate = false;
        }
    }



    if (flags[P] == true) {
        if (cuisine[caseB][caseA] == DISTRIBTOMATE) {
            joueur2->tomate = true;
        }
        else if (cuisine[caseB][caseA] == POUBELLE) {
            joueur2->tomate = false;
        }
    }
}

void saisirFromage(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]) {

    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;


    if (flags[E] == true) {
        if (cuisine[caseY][caseX] == DISTRIBFROMAGE) {
            joueur1->fromage = true;

        }
        else if (cuisine[caseY][caseX] == POUBELLE) {
            joueur1->fromage = false;
        }
    }


    if (flags[P] == true ) {
        if (cuisine[caseB][caseA] == DISTRIBFROMAGE) {
            joueur2->fromage = true;
        }
        else if (cuisine[caseB][caseA] == POUBELLE) {
            joueur2->fromage = false;
        }
    }
}

void saisirPoivron(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]) {

    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;


    if (flags[E] == true ) {
        if (cuisine[caseY][caseX] == DISTRIBPOIVRONS) {
            joueur1->poivrons = true;

        }
        else if (cuisine[caseY][caseX] == POUBELLE) {
            joueur1->poivrons = false;
        }
    }


    if (flags[P] == true) {
        if (cuisine[caseB][caseA] == DISTRIBPOIVRONS) {
            joueur2->poivrons = true;

        }
        else if (cuisine[caseB][caseA] == POUBELLE) {
            joueur2->poivrons = false;
        }
    }
}

void saisirTortilla(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]) {

    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;


    if (flags[E] == true ) {
        if (cuisine[caseY][caseX] == DISTRIBTORTILLA) {
            joueur1->tortilla = true;

        }
        else if (cuisine[caseY][caseX] == POUBELLE) {
            joueur1->tortilla = false;
        }
        else if(cuisine[caseY][caseX] == SORTIE){
            joueur1->tortilla = false;
        }
    }


    if (flags[P] == true) {
        if (cuisine[caseB][caseA] == DISTRIBTORTILLA) {
            joueur2->tortilla = true;

        }
        else if (cuisine[caseB][caseA] == POUBELLE) {
            joueur2->tortilla = false;
        }
        else if (cuisine[caseB][caseA] == SORTIE){
            joueur2->tortilla = false;
        }
    }
}

void saisirViande(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]) {

    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;


    if (flags[E] == true ) {
        if (cuisine[caseY][caseX] == DISTRIBVIANDE) {
            joueur1->viande = true;

        }
        else if (cuisine[caseY][caseX] == POUBELLE) {
            joueur1->viande = false;
        }
    }


    if (flags[P] == true) {
        if (cuisine[caseB][caseA] == DISTRIBVIANDE) {
            joueur2->viande = true;

        }
        else if (cuisine[caseB][caseA] == POUBELLE) {
            joueur2->viande = false;
        }
    }
}

void saisirSalade(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]) {

    int caseX = (joueur1->cx - 114) / 60; // Curseur du joueur1
    int caseY = (joueur1->cy - 81) / 60;

    int caseA = (joueur2->cx - 114) / 60; // Curseur du joueur2
    int caseB = (joueur2->cy - 81) / 60;


    if (flags[E] == true ) {
        if (cuisine[caseY][caseX] == DISTRIBSALADE) {
            joueur1->salade = true;

        }
        else if (cuisine[caseY][caseX] == POUBELLE) {
            joueur1->salade = false;
        }
        else if (cuisine[caseY][caseX] == SORTIE) {
            joueur1->salade = false;
        }
    }


    if (flags[P] == true) {
        if (cuisine[caseB][caseA] == DISTRIBSALADE) {
            joueur2->salade = true;

        }
        else if (cuisine[caseB][caseA] == POUBELLE) {
            joueur2->salade = false;
        }
        else if (cuisine[caseB][caseA] == SORTIE) {
            joueur2->salade = false;
        }
    }
}

/*
if (assiette->pain == true && assiette->viandecuite == true && assiette->tomatedecoupe == true && assiette->poivronsdecoupe == true && assiette->sauce == true){
//al_draw_bitmap(........) // faire une image 3D de la faritas pleine
return 1;
}
if (assiette->pain == true && assiette->viandecuite == true && assiette->tomatedecoupe == true && assiette->poivronsdecoupe == true){
//al_draw_bitmap(........) // faire une image 3D de la fraitas sans sauce
return 2;
}
if (assiette->pain == true && assiette->viandecuite == true && assiette->poivronsdecoupe == true && assiette->sauce == true){
//al_draw_bitmap(........) // faire une faritas sans tomates
return 3;
}
if (assiette->pain == true && assiette->viandecuite == true && assiette->tomatedecoupe == true && assiette->sauce == true){
// al_draw_bitmap(.......) // faire une faritas sans poivrons
return 4;
}
*/
/*
void dessinerConstructionDeLaTortilla(Assiette* assiette, int* recette){
    if (assiette->assiette == true){

        if (assiette->pain == true){
            printf("faritas\n");
           // al_draw_bitmap(); // desiiner image fartias avec assiette
           *recette = 1;
            if ( assiette->viandecuite == true){
                printf("faritas + viande");
                // al_draw_ bitmap(); // desisner image faritas avce viande
                *recette = 2;
                if (assiette->tomatedecoupe == true){
                    printf("faritas + viande + tomates");
                    // al_draw_bitamp(); // dessiner image faritas + viande + tomates
                    *recette = 3;
                    if (assiette->poivronsdecoupe == true){
                        printf("faritas + viande+ tomates + poivrons");
                        // al_draw_bitamp(); // dessiner image faritas + viande + tomates + poivrons
                        *recette = 4;
                        if (assiette->salade == true){
                            printf("faritas complete");
                            // al_draw_bitamp(); // dessiner image faritas + viande + tomates + poivrons + sauce
                            *recette = 5;
                        }
                    }
                }
            }
        }
    }
}
*/

void gameplay(joueur* joueur1, joueur* joueur2 , cafard* cafard, balle* balle1, balle* balle2,ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* fifo, ALLEGRO_EVENT event,ALLEGRO_SAMPLE *sample, ALLEGRO_DISPLAY* display, int * niveauCourant, Assiette* assiette){
    bool commandeGeneree1 = false;
    bool commandeGeneree2 = false;
    int cuisine[9][17] = {{0}}; // dimension de la cuisine
    int frame = 0;
    int temps = 0;  //temps = frames/60 pour pouvoir travailler en secondes depuis le lancement du lvl

    ALLEGRO_FONT *font = al_load_ttf_font("..\\assets\\Play-Regular.ttf", 14, 0);
    ALLEGRO_BITMAP * gif_frames_cafard[45];
    charger_gif_cafard(gif_frames_cafard, "..\\assets\\cafard_animation", 45); //génération des 45 images du gif du cafard

    // Initialisation de fileClients
    File *fileClients = (File *)malloc(sizeof(File));
    fileClients->first = NULL;
    fileClients->last = NULL;

    // Initialisation de fileCommande
    File *fileCommande = (File *)malloc(sizeof(File));
    fileCommande->first = NULL;
    fileCommande->last = NULL;

    bool fini = false;
    bool pause = false;
    initialisationJoueur(joueur1, joueur2, cafard, balle1, balle2);
    initialiserCommande(fileCommande);
    bool flags[NUMFLAGS] = {false};

    int frame_counter_cafard = 0; // Déclarer en dehors de la boucle
    int frame_actuelle_cafard = 0; // Déclarer en dehors de la boucle
    int recette = 0;

    assert(sample);
    al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL); //lancement de la musique


    Images images;
    images.decor1 = al_load_bitmap("../assets/Image/decor1.png");
    images.poubelle = al_load_bitmap("../assets/Image/poubelle.png");
    images.plantravail = al_load_bitmap("../assets/Image/plantravail.png");
    images.distributeurtomates = al_load_bitmap("../assets/Image/distributeurtomates.png");
    images.distribassiettes = al_load_bitmap("../assets/Image/distribassiettes.png");
    images.assiette = al_load_bitmap("../assets/Image/assiette.png");
    images.cuisson = al_load_bitmap("../assets/Image/cuisson.png");
    images.decoupe = al_load_bitmap("../assets/Image/decoupe.png");
    images.sortie = al_load_bitmap("../assets/Image/sortie.png");
    images.sol = al_load_bitmap("../assets/Image/sol.png");
    images.assiettePosee = al_load_bitmap("../assets/Image/assiettePosee.png");
    images.distributeurfromage = al_load_bitmap("../assets/Image/distributeurfromage.png");
    images.distributeurpoivrons = al_load_bitmap("../assets/Image/distributeurpoivrons.png");
    images.distributeurtortilla = al_load_bitmap("../assets/Image/distributeurTortilla.png");
    images.distributeursalade = al_load_bitmap("../assets/Image/distributeursalade.png");
    images.distributeurviande = al_load_bitmap("../assets/Image/distributeurViande.png");
    images.gameover = al_load_bitmap("../assets/Image/gameover.png");

    ImagesIngredients imagesIngredients;
    imagesIngredients.tomate = al_load_bitmap("../assets/Image/tomate.png");
    imagesIngredients.tomatedecoupe = al_load_bitmap("../assets/Image/tomateDecoupee.png");
    imagesIngredients.pain = al_load_bitmap("../assets/Image/pain.png");
    imagesIngredients.fromage = al_load_bitmap("../assets/Image/fromage.png");
    imagesIngredients.sauce = al_load_bitmap("../assets/Image/sauce.png");
    imagesIngredients.viande = al_load_bitmap("../assets/Image/viande.png");
    imagesIngredients.viandecuite = al_load_bitmap("../assets/Image/viandeCuite.png");
    imagesIngredients.poivrons = al_load_bitmap("../assets/Image/poivron.png");
    imagesIngredients.poivronsdecoupe = al_load_bitmap("../assets/Image/poivronDecoupee.png");
    imagesIngredients.fromagedecoupe = al_load_bitmap("../assets/Image/fromageDecoupee.png");
    imagesIngredients.tortilla = al_load_bitmap("../assets/Image/tortilla.png");
    imagesIngredients.salade = al_load_bitmap("../assets/Image/salade.png");


    if (*niveauCourant == 1){
        lectureCuisineFichierText(cuisine, "../Niveau1.txt");
    }

    if (*niveauCourant == 2){
        lectureCuisineFichierText(cuisine, "../Niveau2.txt");
    }

    if (*niveauCourant == 3){
        lectureCuisineFichierText(cuisine, "../Niveau3.txt");
    }

    int score = 0;


//    genererCommandeTacos();


    while (!fini) {

        al_wait_for_event(fifo, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fini = true;
                break;
            }
            case ALLEGRO_EVENT_TIMER:

                if (!pause) {

                    if (flags[M]) {
                        pause = true;
                    }



                    if (*niveauCourant == 1 && temps == 100){  //condition de victoire niveau 1
                        if (score >= 100){
                            initialisationJoueur(joueur1, joueur2, cafard, balle1, balle2);
                            lectureCuisineFichierText(cuisine, "../Niveau2.txt");
                            temps = 0;
                            frame = 0;
                            *niveauCourant = 2;
                        }
                        else {
                            al_draw_bitmap(images.gameover, 0, 0, 0);
                            al_flip_display();
                            al_rest(5);
                            al_destroy_event_queue(fifo);
                            exit(0);
                        }
                    }


                frame = frame + 1;
                if(frame % 60 == 0){ //convertisseur frames --> secondes
                    temps = temps + 1 ;
                }

                /*
                if (temps == TEMPSNEWORDER1 && !commandeGeneree1) {
                    genererCommandeTacos();
                    commandeGeneree1 = true;
                }

                /*else if (temps != TEMPSNEWORDER1) {
                    commandeGeneree1 = false; // Réinitialiser la variable si temps n'est pas égal à 40
                }

                if (temps == TEMPSNEWORDER2 && !commandeGeneree2) {
                    genererCommandeTacos();
                    commandeGeneree2 = true;
                }

                /*else if (temps != TEMPSNEWORDER2) {
                    commandeGeneree1 = false; // Réinitialiser la variable si temps n'est pas égal à 80
                }*/

                //appel des fonctions utiles pour le lancement du jeu
                deplacementJoueur(joueur1, joueur2, timer, event, flags, cuisine, frame);
                stunJoueur(joueur1,joueur2,cafard);
                stunCafard(balle1,balle2,cafard);
                deplacementCafard(cafard, gif_frames_cafard, &frame_counter_cafard, &frame_actuelle_cafard);
                tirerballe(joueur1, joueur2,flags,balle1,balle2);
                //verificationPixel(display,joueur1);
                saisirAssiette(joueur1,joueur2,images,flags,cuisine);
                saisirTomate(joueur1, joueur2,imagesIngredients,flags,cuisine);
                saisirFromage(joueur1, joueur2, imagesIngredients, flags, cuisine);
                saisirPoivron(joueur1, joueur2, imagesIngredients, flags, cuisine);
                saisirTortilla(joueur1, joueur2, imagesIngredients, flags, cuisine);
                saisirViande(joueur1, joueur2, imagesIngredients, flags, cuisine);
                saisirSalade(joueur1, joueur2, imagesIngredients, flags, cuisine);
                decouperTomate(joueur1,joueur2,imagesIngredients,flags,cuisine);
                decouperPoivron(joueur1, joueur2, imagesIngredients, flags, cuisine);
                decouperFromage(joueur1, joueur2, imagesIngredients, flags, cuisine);
                cuireViande(joueur1, joueur2, imagesIngredients, flags, cuisine);
                //dessinerConstructionDeLaTortilla(assiette,&recette);
                addCommande(fileCommande);


                    dessinerTout(joueur1, joueur2, cafard, gif_frames_cafard, &frame_actuelle_cafard, balle1, balle2,cuisine,images,imagesIngredients,flags,font,temps,fileClients, score);

                break;
                }

            case ALLEGRO_EVENT_KEY_DOWN:

                if (flags[M]) {
                    pause = false;
                }
                if (pause){
                    al_draw_filled_rectangle(0, 0, 1248, 702, al_map_rgba(0, 0, 0, 200));
                    al_draw_text(font, al_map_rgb(255, 255, 255), 1248 / 2, 702 / 2, ALLEGRO_ALIGN_CENTER, "PAUSED");
                    al_flip_display();
                }

                deplacementJoueurKeyDown(joueur1, joueur2, timer, event, flags); //enfoncement de la touche
                break;

            case ALLEGRO_EVENT_KEY_UP:
                deplacementJoueurKeyUp(joueur1, joueur2, timer, event, flags); //relachement de la touche
                break;

            case ALLEGRO_EVENT_JOYSTICK_AXIS:

                break;
        }
    }
}


