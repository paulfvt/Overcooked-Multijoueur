#ifndef TESTPROJECT_PERSONNAGE_H
#define TESTPROJECT_PERSONNAGE_H

#include "allegro5/allegro.h"
#include "map.h"
#include "Ingredient.h"

#define WIDSPLAY 1248
#define HIDSPLAY 702
#define PLAYER_RADIUS 20
#define PLAYER_SPEED 5
#define PLAYER_STUN_DURATION 200
#define BALL_SPEED 20
#define BALL_COOLDOWN 150
#define MAX_FRAMES 45
#define STUN_DURATION_CAFARD 500
#define COLLISION_MARGIN 20
#define BALL_POSITION (-500)
#define BALL_DISTANCE 0
#define JOUEUR_COOLDOWN 0


#define DEG_TO_RAD(x) ((x) * ALLEGRO_PI / 180)

enum {LEFT, UP, DOWN, RIGHT, A ,SPACE, E, Z, Q, S, D, P,O,R,M, NUMFLAGS }; //commandes utilisé pour se déplacer ou tirer



typedef struct Ingredients{
    int x,y; // position
    int type; // quels ingredients
    bool etat; //brulé ou pas
    ALLEGRO_BITMAP *imageIngredients;
    struct Element *prev;
    struct Element *next;
} Ingredients;

typedef struct Personnage { //structure des joueurs
    int x, y;
    int vx,vy;
    int cx, cy;
    float angle;
    int rayon;
    bool stun;
    int cooldown;
    ALLEGRO_BITMAP *image;
    Ingredients *main; // Pointeur vers la structure ingredients afin de savoir si le perso à un ingredients dans les mains et de savoir toutes les informations de l'ingrédient (position, état, etc...)

    bool assiette;
    bool tomate;
    bool fromage;
    bool poivrons;
    bool tomatedecoupe;
    bool poivronsdecoupe;
    bool fromagedecoupe;
    bool tortilla;
    bool salade;
    bool saladedecoupe;
    bool sauce;
    bool viande;
    bool viandecuite;
} joueur;


typedef struct Projectile { // structure de la balle
    int x1;
    int y1;
    int x2;
    int y2;
    float dx;
    float dy;
    float distance;
    int vitesse;

}balle;


typedef struct Cucaracha { // structure du cafard
    float x;
    float y;
    float vx;
    float vy;
    float rayon;
    bool stun;
}cafard;




void initialisationJoueur(joueur* joueur1, joueur* joueur2, cafard * cafard, balle* balle1, balle* balle2); // fonction d'initialisation des coordonées

void deplacementJoueur(joueur *joueur1, joueur *joueur2, ALLEGRO_TIMER* timer, ALLEGRO_EVENT event,bool flags[12], int cuisine[9][17], int frame); //fonctions des déplacements des 2 joueurs

void deplacementJoueurKeyDown(joueur *joueur1, joueur *joueur2, ALLEGRO_TIMER* timer, ALLEGRO_EVENT event, bool flags[12]);// fonction des déplacements lors de l'enfoncement de la touche

void deplacementJoueurKeyUp(joueur *joueur1, joueur *joueur2, ALLEGRO_TIMER* timer, ALLEGRO_EVENT event, bool flags[12]);// fonction des déplacments lors du relâchement de la touche

void charger_gif_cafard(ALLEGRO_BITMAP **gif_frames, const char *chemin_dossier, int nombre_frames); //fonction de generation de l'image du cafard

void deplacementCafard(cafard* cafard, ALLEGRO_BITMAP* gif_frames_cafard[], int* frame_counter_cafard, int* frame_actuelle_cafard); //fonction des déplacements du cafard

void stunJoueur(joueur* joueur1, joueur* joueur2,cafard* cafard); //fonction de blocage du joueur (stun)

void stunCafard(balle *balle1,balle* balle2, cafard *cafard); // fonction pour bloquer le cafard

void tirerballe(joueur *joueur1, joueur *joueur2, bool flags[10], balle* balle1,balle* balle2); // fonction pour tirer la balle qui tue le cafard

int collisionCuisine(joueur* joueur1, joueur* joueur2, Images images);

#endif //ESCOOKED_JOUEUR_H