#include "Joueur.h"
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <math.h>
#include "Ingredient.h"
#include "map.h"
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

void initialisationJoueur(joueur* joueur1, joueur* joueur2, cafard* cafard, balle* balle1, balle* balle2){

    joueur1->x = 0;
    joueur1->y = 0;
    joueur1->vx = PLAYER_SPEED; // vitesse initiale du joueur 1
    joueur1->vy = PLAYER_SPEED;
    joueur1->angle = 0.0f;
    joueur1->rayon = PLAYER_RADIUS; // rayon du cercle représentant le joueur1
    joueur1->image = al_load_bitmap("..\\assets\\image\\personnage.png"); // génération de l'image du joueur 1
    joueur1->x = (WIDSPLAY - al_get_bitmap_width(joueur1->image)) / 3; // ligne a modifier pour changer la position initial
    joueur1->y = (HIDSPLAY - al_get_bitmap_height(joueur1->image)) / 1.3;// ligne a modifier pour changer la position initial
    joueur1->stun = false;
    joueur1->cooldown = JOUEUR_COOLDOWN; // temps de recharge du tir de la balle
    joueur1->assiette = false;
    joueur1->fromage = false;
    joueur1->fromagedecoupe = false;
    joueur1->tomate = false;
    joueur1->tomatedecoupe = false;
    joueur1->poivrons = false;
    joueur1->poivronsdecoupe = false;
    joueur1->salade = false;
    joueur1->poivrons = false;
    joueur1->sauce = false;
    joueur1->viande = false;
    joueur1->viandecuite = false;
    joueur1->tortilla = false;




    joueur2->x = 0; //position initiale du joueur 2
    joueur2->y = 0;
    joueur2->vx = PLAYER_SPEED; // vitesse initiale du joueur 2
    joueur2->vy = PLAYER_SPEED;
    joueur2->angle = 0.0f;
    joueur2->rayon = PLAYER_RADIUS; // rayon du cercle représentant le joueur2
    joueur2->image = al_load_bitmap("..\\assets\\image\\personnage2.png"); // génération de l'image du joueur 2
    joueur2->x = (WIDSPLAY - al_get_bitmap_width(joueur2->image)) / 1.3; // ligne a modifier pour changer la position initial
    joueur2->y = (HIDSPLAY - al_get_bitmap_height(joueur2->image)) / 3; // ligne a modifier pour changer la position initial
    joueur2->stun = false;
    joueur2->cooldown = JOUEUR_COOLDOWN; // temps de recharge du tir de la balle
    joueur2->assiette = false;
    joueur2->fromage = false;
    joueur2->fromagedecoupe = false;
    joueur2->tomate = false;
    joueur2->tomatedecoupe = false;
    joueur2->poivrons = false;
    joueur2->poivronsdecoupe = false;
    joueur2->salade = false;
    joueur2->sauce = false;
    joueur2->viande = false;
    joueur2->viandecuite = false;
    joueur2->tortilla = false;

    cafard->x = 624; // position initiale du cafard
    cafard->y = 351;
    cafard->vx = 2.5; // vitesse initiale du cafard
    cafard->vy = 1.5;
    cafard->rayon = 3; // rayon du cercle représentant le cafard
    cafard->stun = false;


    // Init de la balle du joueur 1
    balle1->x1 = BALL_POSITION;
    balle1->y1 = BALL_POSITION;
    balle1->x2 = BALL_POSITION;
    balle1->y2 = BALL_POSITION;
    balle1->dx = 0;
    balle1->dy = 0;
    balle1->distance = BALL_DISTANCE;
    balle1->vitesse = BALL_SPEED;

    // Init de la balle du joueur 2
    balle2->x1 = BALL_POSITION;
    balle2->y1 = BALL_POSITION;
    balle2->x2 = BALL_POSITION;
    balle2->y2 = BALL_POSITION;
    balle2->dx = 0;
    balle2->dy = 0;
    balle2->distance = BALL_DISTANCE;
    balle2->vitesse = BALL_SPEED;


}


void deplacementJoueur(joueur *joueur1, joueur *joueur2, ALLEGRO_TIMER* timer, ALLEGRO_EVENT event, bool flags[12], int cuisine[9][17], int frame) {

    // Init des collisions du joueur 1
    int colx1 = joueur1->x - COLLISION_MARGIN;
    int colxx1 = joueur1->x + COLLISION_MARGIN;
    int coly1 = joueur1->y + COLLISION_MARGIN;
    int colyy1 =joueur1 ->y - COLLISION_MARGIN;

    // Init des collisions du joueur 2
    int colx2 = joueur2->x - COLLISION_MARGIN;
    int colxx2 = joueur2->x + COLLISION_MARGIN;
    int coly2= joueur2->y + COLLISION_MARGIN;
    int colyy2 =joueur2 ->y - COLLISION_MARGIN;



    switch (event.type) {
        case ALLEGRO_EVENT_TIMER:

            // Deplacement des joueurs
            if (flags[Q] && joueur1->x > 144 && joueur1->stun == false && sqrt(pow(colx1 - joueur2->x, 2) + pow(joueur1->y - joueur2->y, 2)) >= 50) {
                int leftIndexX = ((joueur1->x - joueur1->vx - 143) / 60);
                int leftIndexY = (joueur1->y - 75) / 60;

                if (cuisine[leftIndexY][leftIndexX] != PLANDETRAVAIL && cuisine[leftIndexY][leftIndexX] != ASSIETTE && cuisine[leftIndexY][leftIndexX] != DECOUPE && cuisine[leftIndexY][leftIndexX] != DISTRIBASSIETTE && cuisine[leftIndexY][leftIndexX] != DISTRIBTOMATE && cuisine[leftIndexY][leftIndexX] != POUBELLE && cuisine[leftIndexY][leftIndexX] != CUISSON && cuisine[leftIndexY][leftIndexX] != ASSIETTEPOSEE && cuisine[leftIndexY][leftIndexX] != SORTIE && cuisine[leftIndexY][leftIndexX] != DISTRIBFROMAGE && cuisine[leftIndexY][leftIndexX] != DISTRIBPOIVRONS && cuisine[leftIndexY][leftIndexX] != DISTRIBTORTILLA && cuisine[leftIndexY][leftIndexX] != DISTRIBVIANDE && cuisine[leftIndexY][leftIndexX] != DISTRIBSALADE) {
                    joueur1->x -= joueur1->vx;
                    joueur1->cx = joueur1->x - 50;
                    joueur1->cy = joueur1->y;
                    joueur1->angle = -90 + (sin(frame * 0.5) * 10);

                }
            }

            if (flags[D] && joueur1->x < 1104 && joueur1->stun == false && sqrt(pow(colxx1 - joueur2->x, 2) + pow(joueur1->y - joueur2->y, 2)) >= 50) {
                int rightIndexX = (joueur1->x + joueur1->vx - 85) / 60;
                int rightIndexY = (joueur1->y - 75) / 60;

                if (cuisine[rightIndexY][rightIndexX] != PLANDETRAVAIL && cuisine[rightIndexY][rightIndexX] != ASSIETTE && cuisine[rightIndexY][rightIndexX] != DECOUPE && cuisine[rightIndexY][rightIndexX] != DISTRIBASSIETTE && cuisine[rightIndexY][rightIndexX] != DISTRIBTOMATE && cuisine[rightIndexY][rightIndexX] != POUBELLE && cuisine[rightIndexY][rightIndexX] != CUISSON && cuisine[rightIndexY][rightIndexX] != ASSIETTEPOSEE && cuisine[rightIndexY][rightIndexX] != SORTIE && cuisine[rightIndexY][rightIndexX] != DISTRIBFROMAGE && cuisine[rightIndexY][rightIndexX] != DISTRIBPOIVRONS && cuisine[rightIndexY][rightIndexX] != DISTRIBTORTILLA && cuisine[rightIndexY][rightIndexX] != DISTRIBVIANDE && cuisine[rightIndexY][rightIndexX] != DISTRIBSALADE) {
                    joueur1->x += joueur1->vx;

                    joueur1->cx = joueur1->x + 50;
                    joueur1->cy = joueur1->y;
                    joueur1->angle = 90 + (sin(frame * 0.5) * 10);

                }
            }

            if (flags[Z] && joueur1->y > 115 && joueur1->stun == false && sqrt(pow(colyy1 - joueur2->y, 2) + pow(joueur1->x - joueur2->x, 2)) >= 50) {
                int upIndexX = (joueur1->x - 118) / 60;
                int upIndexY = (joueur1->y - joueur1->vy - 110) / 60;

                if (cuisine[upIndexY][upIndexX] != PLANDETRAVAIL && cuisine[upIndexY][upIndexX] != ASSIETTE && cuisine[upIndexY][upIndexX] != DECOUPE && cuisine[upIndexY][upIndexX] != DISTRIBASSIETTE && cuisine[upIndexY][upIndexX] != DISTRIBTOMATE && cuisine[upIndexY][upIndexX] != POUBELLE && cuisine[upIndexY][upIndexX] != CUISSON && cuisine[upIndexY][upIndexX] != ASSIETTEPOSEE && cuisine[upIndexY][upIndexX] != SORTIE && cuisine[upIndexY][upIndexX] != DISTRIBFROMAGE && cuisine[upIndexY][upIndexX] != DISTRIBPOIVRONS && cuisine[upIndexY][upIndexX] != DISTRIBTORTILLA && cuisine[upIndexY][upIndexX] != DISTRIBVIANDE && cuisine[upIndexY][upIndexX] != DISTRIBSALADE) {
                    joueur1->y -= joueur1->vy;

                    joueur1->cy = joueur1->y - 50;
                    joueur1->cx = joueur1->x;
                    joueur1->angle = 0 + (sin(frame * 0.5) * 10);

                }
            }

            if (flags[S] && joueur1->y < 590  && joueur1->stun == false && sqrt(pow(coly1 - joueur2->y, 2) + pow(joueur1->x - joueur2->x, 2)) >= 50) {
                int downIndexX = (joueur1->x - 110) / 60;
                int downIndexY = (joueur1->y + joueur1->vy - 55) / 60;

                if (cuisine[downIndexY][downIndexX] != PLANDETRAVAIL && cuisine[downIndexY][downIndexX] != ASSIETTE && cuisine[downIndexY][downIndexX] != DECOUPE && cuisine[downIndexY][downIndexX] != DISTRIBASSIETTE && cuisine[downIndexY][downIndexX] != DISTRIBTOMATE && cuisine[downIndexY][downIndexX] != POUBELLE && cuisine[downIndexY][downIndexX] != CUISSON && cuisine[downIndexY][downIndexX] != ASSIETTEPOSEE && cuisine[downIndexY][downIndexX] != SORTIE && cuisine[downIndexY][downIndexX] != DISTRIBFROMAGE && cuisine[downIndexY][downIndexX] != DISTRIBPOIVRONS && cuisine[downIndexY][downIndexX] != DISTRIBTORTILLA && cuisine[downIndexY][downIndexX] != DISTRIBVIANDE && cuisine[downIndexY][downIndexX] != DISTRIBSALADE) {
                    joueur1->y += joueur1->vy;
                    joueur1->cy = joueur1->y + 50;
                    joueur1->cx = joueur1->x;

                    joueur1->angle = -180 + (sin(frame * 0.5) * 10);
                }
            }



            if(flags[Q] && flags[S]){
                joueur1->angle = -135 + (sin(frame * 0.5) * 10);
                joueur1->cy = joueur1->y + 40;
                joueur1->cx = joueur1->x - 40;
            }
            if(flags[Q] && flags [Z]){
                joueur1->angle = -45 + (sin(frame * 0.5) * 10);
                joueur1->cy = joueur1->y - 40;
                joueur1->cx = joueur1->x - 40;
            }
            if(flags[Z] && flags [D]){
                joueur1->angle = 45 + (sin(frame * 0.5) * 10);
                joueur1->cy = joueur1->y - 40;
                joueur1->cx = joueur1->x + 40;
            }
            if(flags[S] && flags[D]){
                joueur1->angle = 145 + (sin(frame * 0.5) * 10);
                joueur1->cy = joueur1->y + 40;
                joueur1->cx = joueur1->x + 40;
            }



            if (flags[LEFT] && joueur2->x > 144 && joueur2->stun == false && sqrt(pow(colx2 - joueur1->x, 2) + pow(joueur2->y - joueur1->y, 2)) >= 50) {
                int leftIndexX = ((joueur2->x - joueur2->vx - 143) / 60);
                int leftIndexY = (joueur2->y - 75) / 60;

                if (cuisine[leftIndexY][leftIndexX] != PLANDETRAVAIL && cuisine[leftIndexY][leftIndexX] != ASSIETTE && cuisine[leftIndexY][leftIndexX] != DECOUPE && cuisine[leftIndexY][leftIndexX] != DISTRIBASSIETTE && cuisine[leftIndexY][leftIndexX] != DISTRIBTOMATE && cuisine[leftIndexY][leftIndexX] != POUBELLE && cuisine[leftIndexY][leftIndexX] != CUISSON && cuisine[leftIndexY][leftIndexX] != ASSIETTEPOSEE && cuisine[leftIndexY][leftIndexX] != SORTIE && cuisine[leftIndexY][leftIndexX] != DISTRIBFROMAGE && cuisine[leftIndexY][leftIndexX] != DISTRIBPOIVRONS && cuisine[leftIndexY][leftIndexX] != DISTRIBTORTILLA && cuisine[leftIndexY][leftIndexX] != DISTRIBVIANDE && cuisine[leftIndexY][leftIndexX] != DISTRIBSALADE) {
                    joueur2->x -= joueur2->vx;
                    joueur2->angle = -90 + (sin(frame * 0.5) * 10);
                    joueur2->cx = joueur2->x - 50;
                    joueur2->cy = joueur2->y;
                }
            }


            if (flags[RIGHT] && joueur2->x < 1104 && joueur2->stun == false && sqrt(pow(colxx2 - joueur1->x, 2) + pow(joueur2->y - joueur1->y, 2)) >= 50) {
                int rightIndexX = (joueur2->x + joueur2->vx - 85) / 60;
                int rightIndexY = (joueur2->y - 75) / 60;

                if (cuisine[rightIndexY][rightIndexX] != PLANDETRAVAIL && cuisine[rightIndexY][rightIndexX] != ASSIETTE && cuisine[rightIndexY][rightIndexX] != DECOUPE && cuisine[rightIndexY][rightIndexX] != DISTRIBASSIETTE && cuisine[rightIndexY][rightIndexX] != DISTRIBTOMATE && cuisine[rightIndexY][rightIndexX] != POUBELLE && cuisine[rightIndexY][rightIndexX] != CUISSON && cuisine[rightIndexY][rightIndexX] != ASSIETTEPOSEE && cuisine[rightIndexY][rightIndexX] != SORTIE && cuisine[rightIndexY][rightIndexX] != DISTRIBFROMAGE && cuisine[rightIndexY][rightIndexX] != DISTRIBPOIVRONS && cuisine[rightIndexY][rightIndexX] != DISTRIBTORTILLA && cuisine[rightIndexY][rightIndexX] != DISTRIBVIANDE && cuisine[rightIndexY][rightIndexX] != DISTRIBSALADE) {
                    joueur2->x += joueur2->vx;
                    joueur2->angle = 90 + (sin(frame * 0.5) * 10);
                    joueur2->cx = joueur2->x + 50;
                    joueur2->cy = joueur2->y;
                }
            }


            if (flags[UP] && joueur2->y > 115 && joueur2->stun == false && sqrt(pow(colyy2 - joueur1->y, 2) + pow(joueur2->x - joueur1->x, 2)) >= 50) {
                int upIndexX = (joueur2->x - 118) / 60;
                int upIndexY = (joueur2->y - joueur2->vy - 110) / 60;

                if (cuisine[upIndexY][upIndexX] != PLANDETRAVAIL && cuisine[upIndexY][upIndexX] != ASSIETTE && cuisine[upIndexY][upIndexX] != DECOUPE && cuisine[upIndexY][upIndexX] != DISTRIBASSIETTE && cuisine[upIndexY][upIndexX] != DISTRIBTOMATE && cuisine[upIndexY][upIndexX] != POUBELLE && cuisine[upIndexY][upIndexX] != CUISSON && cuisine[upIndexY][upIndexX] != ASSIETTEPOSEE && cuisine[upIndexY][upIndexX] != SORTIE && cuisine[upIndexY][upIndexX] != DISTRIBFROMAGE && cuisine[upIndexY][upIndexX] != DISTRIBPOIVRONS && cuisine[upIndexY][upIndexX] != DISTRIBTORTILLA && cuisine[upIndexY][upIndexX] != DISTRIBVIANDE && cuisine[upIndexY][upIndexX] != DISTRIBSALADE) {
                    joueur2->y -= joueur2->vy;
                    joueur2->angle = 0 + (sin(frame * 0.5) * 10);
                    joueur2->cy = joueur2->y - 50;
                    joueur2->cx = joueur2->x;
                }
            }



            if (flags[DOWN] && joueur2->y < 590 && joueur2->stun == false && sqrt(pow(coly2 - joueur1->y, 2) + pow(joueur2->x - joueur1->x, 2)) >= 50 ) {
                int downIndexX = (joueur2->x - 110) / 60;
                int downIndexY = (joueur2->y + joueur2->vy - 55) / 60;

                if (cuisine[downIndexY][downIndexX] != PLANDETRAVAIL && cuisine[downIndexY][downIndexX] != ASSIETTE && cuisine[downIndexY][downIndexX] != DECOUPE && cuisine[downIndexY][downIndexX] != DISTRIBASSIETTE && cuisine[downIndexY][downIndexX] != DISTRIBTOMATE && cuisine[downIndexY][downIndexX] != POUBELLE && cuisine[downIndexY][downIndexX] != CUISSON && cuisine[downIndexY][downIndexX] != ASSIETTEPOSEE && cuisine[downIndexY][downIndexX] != SORTIE && cuisine[downIndexY][downIndexX] != DISTRIBFROMAGE && cuisine[downIndexY][downIndexX] != DISTRIBPOIVRONS && cuisine[downIndexY][downIndexX] != DISTRIBTORTILLA && cuisine[downIndexY][downIndexX] != DISTRIBVIANDE && cuisine[downIndexY][downIndexX] != DISTRIBSALADE) {
                    joueur2->y += joueur2->vy;
                    joueur2->angle = -180 + (sin(frame * 0.5) * 10);
                    joueur2->cy = joueur2->y + 50;
                    joueur2->cx = joueur2->x;
                }
            }


            if(flags[LEFT] && flags[DOWN]){
                joueur2->angle = -135 + (sin(frame * 0.5) * 10);
                joueur2->cy = joueur2->y + 40;
                joueur2->cx = joueur2->x - 40;
            }
            if(flags[LEFT] && flags [UP]){
                joueur2->angle = -45 + (sin(frame * 0.5) * 10);
                joueur2->cy = joueur2->y - 40;
                joueur2->cx = joueur2->x - 40;
            }
            if(flags[UP] && flags [RIGHT]){
                joueur2->angle = 45 + (sin(frame * 0.5) * 10);
                joueur2->cy = joueur2->y - 40;
                joueur2->cx = joueur2->x + 40;
            }
            if(flags[DOWN] && flags[RIGHT]){
                joueur2->angle = 145 + (sin(frame * 0.5) * 10);
                joueur2->cy = joueur2->y + 40;
                joueur2->cx = joueur2->x + 40;
            }

            break;


    }
}

void deplacementJoueurKeyDown(joueur *joueur1, joueur *joueur2, ALLEGRO_TIMER* timer, ALLEGRO_EVENT event, bool flags[12]){

    // enfoncement des commandes du clavier
    switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
            flags[LEFT] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            flags[RIGHT] = true;
            break;
        case ALLEGRO_KEY_UP:
            flags[UP] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            flags[DOWN] = true;
            break;
        case ALLEGRO_KEY_A:
            flags[A] = true;
            break;
        case ALLEGRO_KEY_SPACE:
            flags[SPACE] = true;
            break;
        case ALLEGRO_KEY_E:
            flags[E] = true;
            break;
        case ALLEGRO_KEY_M:
            flags[M] = true;
            break;
        case ALLEGRO_KEY_Q:
            flags[Q] = true;
            break;
        case ALLEGRO_KEY_D:
            flags[D] = true;
            break;
        case ALLEGRO_KEY_Z:
            flags[Z] = true;
            break;
        case ALLEGRO_KEY_S:
            flags[S] = true;
            break;
        case ALLEGRO_KEY_P:
            flags[P] = true;
            break;
        case ALLEGRO_KEY_O:
            flags[O] = true;
            break;
        case ALLEGRO_KEY_R:
            flags[R] = true;
            break;
    }

}

void deplacementJoueurKeyUp(joueur *joueur1, joueur *joueur2, ALLEGRO_TIMER* timer, ALLEGRO_EVENT event, bool flags[12]) {

    // relachement des commandes du clavier
    switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_LEFT:
            flags[LEFT] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            flags[RIGHT] = false;
            break;
        case ALLEGRO_KEY_UP:
            flags[UP] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            flags[DOWN] = false;
            break;
        case ALLEGRO_KEY_A:
            flags[A] = false;
            break;
        case ALLEGRO_KEY_SPACE:
            flags[SPACE] = false;
            break;
        case ALLEGRO_KEY_E:
            flags[E] = false;
            break;
        case ALLEGRO_KEY_M:
            flags[M] = false;
            break;
        case ALLEGRO_KEY_Q:
            flags[Q] = false;
            break;
        case ALLEGRO_KEY_D:
            flags[D] = false;
            break;
        case ALLEGRO_KEY_Z:
            flags[Z] = false;
            break;
        case ALLEGRO_KEY_S:
            flags[S] = false;
            break;
        case ALLEGRO_KEY_P:
            flags[P] = false;
            break;
        case ALLEGRO_KEY_O:
            flags[O] = false;
            break;
        case ALLEGRO_KEY_R:
            flags[R] = false;
            break;
    }
}





void charger_gif_cafard(ALLEGRO_BITMAP **gif_frames, const char *chemin_dossier, int nombre_frames) {
    char chemin_fichier[100];
    for (int i = 0; i < nombre_frames; i++) {
        sprintf(chemin_fichier, "%s\\frame_%02d_delay-0.03s.gif", chemin_dossier, i);
        gif_frames[i] = al_load_bitmap(chemin_fichier);
    }
}


void deplacementCafard(cafard* cafard, ALLEGRO_BITMAP* gif_frames_cafard[], int* frame_counter_cafard, int* frame_actuelle_cafard) {


    if(cafard->stun ==false){
        cafard->x += cafard->vx;
        cafard->y += cafard->vy;
    }


    if (cafard->x + cafard->rayon >= 1100 || cafard->x - cafard->rayon <= 100) {
        cafard->vx = -cafard->vx; // faire rebondir le cafard sur les bords horizontaux
    }
    if (cafard->y + cafard->rayon >= 600 || cafard->y - cafard->rayon <= 60) {
        cafard->vy = -cafard->vy; // faire rebondir le cafard sur les bords verticaux
    }



    if (*frame_counter_cafard % 2 == 0 && cafard->stun == false) { //Vitesse d'actualisation par rapport aux frames

        (*frame_actuelle_cafard)++;
        if (*frame_actuelle_cafard >= MAX_FRAMES) {
            *frame_actuelle_cafard = 0;
        }
    }
    (*frame_counter_cafard)++;
}

void stunJoueur(joueur* joueur1, joueur* joueur2, cafard* cafard) {
    static int start_stun_joueur1 = 0;
    static int start_stun_joueur2 = 0;
    static int temps = 0;

    // stun du joueur1
    if (sqrt(pow(cafard->x - joueur1->x, 2) + pow(cafard->y - joueur1->y, 2)) <= joueur1->rayon + 40 && cafard->stun == false) {
        joueur1->stun = true;
        start_stun_joueur1 = temps;
    }
    if (joueur1->stun == true) {
        joueur1->angle = joueur1->angle + 10;
        if (temps >= start_stun_joueur1 + PLAYER_STUN_DURATION) {
            joueur1->stun = false;
        }
    }

    //stun du joueur2
    if (sqrt(pow(cafard->x - joueur2->x, 2) + pow(cafard->y - joueur2->y, 2)) <= joueur2->rayon + 40 && cafard->stun == false) {
        joueur2->stun = true;
        start_stun_joueur2 = temps;
    }
    if (joueur2->stun == true) {
        joueur2->angle = joueur2->angle + 10;
        if (temps >= start_stun_joueur2 + PLAYER_STUN_DURATION) {
            joueur2->stun = false;
        }
    }

    temps++;
}



void stunCafard(balle *balle1,balle* balle2, cafard *cafard){

    static int start_stun_cafard = 0 ;
    static int temps2 = 0;

    //stun du cafard à l'aide de la balle par le joueur1
    if (sqrt(pow(cafard->x - balle1->x1, 2) + pow(cafard->y - balle1->y1, 2)) <= 50) {
        cafard->stun = true;
        start_stun_cafard = temps2;
    }
    if (cafard->stun == true) {
        if (temps2 >= start_stun_cafard + STUN_DURATION_CAFARD) {
            cafard->stun = false;
        }
    }

    //stun du cafard à l'aide de la balle par le joueur2
    if (sqrt(pow(cafard->x - balle2->x1, 2) + pow(cafard->y - balle2->y1, 2)) <= 50) {
        cafard->stun = true;
        start_stun_cafard = temps2;
    }
    if (cafard->stun == true) {
        if (temps2 >= start_stun_cafard + STUN_DURATION_CAFARD) {
            cafard->stun = false;
        }
    }
    temps2 ++ ;
}

void tirerballe(joueur *joueur1, joueur *joueur2, bool flags[12], balle* balle1, balle* balle2){
    if(flags[A] && joueur1->cooldown >= BALL_COOLDOWN){
        balle1->x1 = joueur1->x;
        balle1->y1 = joueur1->y;
        balle1->x2 = joueur1->cx+30*(joueur1->cx-joueur1->x);
        balle1->y2 = joueur1->cy+30*(joueur1->cy-joueur1->y); //set distance de fin (a mettre en dehors de l'écran
        flags[A] = false;
        joueur1->cooldown = JOUEUR_COOLDOWN;
    }
    balle1->dx = balle1->x2 - balle1->x1;
    balle1->dy = balle1->y2 - balle1->y1;

    balle1->distance = sqrt(balle1->dx * balle1->dx + balle1->dy * balle1->dy);

    balle1->dx /= balle1->distance;
    balle1->dy /= balle1->distance;

    balle1->x1 += balle1->dx * balle1->vitesse;
    balle1->y1 += balle1->dy * balle1->vitesse;

    joueur1->cooldown++;


    if(flags[SPACE] && joueur2->cooldown >= BALL_COOLDOWN){
        balle2->x1 = joueur2->x;
        balle2->y1 = joueur2->y;
        balle2->x2 = joueur2->cx+30*(joueur2->cx-joueur2->x);
        balle2->y2 = joueur2->cy+30*(joueur2->cy-joueur2->y); //set distance de fin (a mettre en dehors de l'écran
        flags[SPACE] = false;
        joueur2->cooldown = JOUEUR_COOLDOWN;
    }
    balle2->dx = balle2->x2 - balle2->x1;
    balle2->dy = balle2->y2 - balle2->y1;

    balle2->distance = sqrt(balle2->dx * balle2->dx + balle2->dy * balle2->dy);

    balle2->dx /= balle2->distance;
    balle2->dy /= balle2->distance;

    balle2->x1 += balle2->dx * balle2->vitesse;
    balle2->y1 += balle2->dy * balle2->vitesse;
    joueur2->cooldown++;
}