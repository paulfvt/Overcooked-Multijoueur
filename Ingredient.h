#ifndef ESCOOKED_INGREDIENT_H
#define ESCOOKED_INGREDIENT_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Joueur.h"

typedef struct {
    ALLEGRO_BITMAP *tomate;
    ALLEGRO_BITMAP *tomatedecoupe;
    ALLEGRO_BITMAP *pain;
    ALLEGRO_BITMAP *fromage;
    ALLEGRO_BITMAP *sauce;
    ALLEGRO_BITMAP *viande;
    ALLEGRO_BITMAP *viandecuite;
    ALLEGRO_BITMAP *poivrons;
    ALLEGRO_BITMAP *poivronsdecoupe;
    ALLEGRO_BITMAP *fromagedecoupe;
    ALLEGRO_BITMAP *tortilla;
    ALLEGRO_BITMAP *salade;
} ImagesIngredients;


typedef struct Assiette{
    bool assiette;
    bool pain;
    bool poivronsdecoupe;
    bool tomatedecoupe;
    bool viandecuite;
    bool salade;
    int type;
}Assiette;

typedef enum {
    EL_NORMAL,
    EL_CLASICO,
    EL_VEGANO,
    LA_TOTALIDAD
} type;

typedef struct commande{
    // data
    Assiette tacos;
    unsigned int temps;
    ALLEGRO_BITMAP* imageCommande;
    // lien
    struct commande* prev;
    struct commande * next;
    int nbIngredients;
}Commande;

typedef struct FileCommande{
    Commande* first;
    Commande* last;
}File;


void genererCommandeTacos();

void commandes();

void addCommande(File *fileCommande);

void freeFile(File *fileCommande);

void initialiserCommande(File *fileCommande);

void afficherCommande(File *fileClients, ALLEGRO_FONT *font);

#endif //ESCOOKED_INGREDIENT_H
