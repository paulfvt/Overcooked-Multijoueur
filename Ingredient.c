#include "Ingredient.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "map.h"
#include <stdlib.h>
#include "Joueur.h"

#include <stdbool.h>


#define MAX_INGREDIENTS 5

/*
// Fonction pour générer aléatoirement un entier entre min et max (inclus)
int genererNombreAleatoire(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Fonction pour générer aléatoirement une commande de tacos
void genererCommandeTacos(){
    char *ingredients[] = {"tomate", "fromage", "poivron", "salade", "viande"};
    int nombreIngredients = genererNombreAleatoire(1, MAX_INGREDIENTS);

    printf("Nouvelle Commande de tacos : tortilla "); // On inclut toujours la tortilla

    // Choix aléatoire des ingrédients
    bool ingredientsChoisis[sizeof(ingredients) / sizeof(ingredients[0])] = {false};
    for (int i = 0; i < nombreIngredients; ++i) {
        int index;
        do {
            index = genererNombreAleatoire(0, sizeof(ingredients) / sizeof(ingredients[0]) - 1);
        } while (ingredientsChoisis[index]);

        ingredientsChoisis[index] = true;
        printf("%s ", ingredients[index]);
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void commandeClient(int* recette){

}

void recette(int* recette,Assiette* assiette){
    if(assiette->pain == true){
        *recette = 1;
    }
    if (assiette->pain == true && assiette->viandecuite == true){
        *recette = 2;
    }
    if (assiette->pain == true && assiette->viandecuite == true && assiette->tomatedecoupe == true){
        *recette = 3;
    }
    if (assiette->pain == true && assiette->viandecuite == true && assiette->tomatedecoupe == true && assiette->poivronsdecoupe){
        *recette = 4;
    }
    if (assiette->pain == true && assiette->viandecuite == true && assiette->tomatedecoupe == true && assiette->poivronsdecoupe && assiette->salade == true){
        *recette = 5;
    }
}
*/

void addCommande(File *fileCommande) {

    // Allocation de mémoire pour la nouvelle commande
    Commande* newCommande = (Commande* ) malloc(sizeof(Commande));

    // Choix aléatoire du type de tacos
    int choix = (rand() % 4) + 1;
    switch (choix) {
        case 1:
            newCommande->type = EL_NORMAL;
            newCommande->imageCommande = al_load_bitmap("../assets/Image/commande1.png");
            break;

        case 2:
            newCommande->type = EL_CLASICO;
            newCommande->imageCommande = al_load_bitmap("../assets/Image/commande2.png");
            break;

        case 3:
            newCommande->type = EL_VEGANO;
            newCommande->imageCommande = al_load_bitmap("../assets/Image/commande3.png");
            break;

        case 4:
            newCommande->type = LA_TOTALIDAD;
            newCommande->imageCommande = al_load_bitmap("../assets/Image/commande4.png");
            break;
    }


    // Initialisation des autres données de la commande
    newCommande->temps = (rand() % 40) + 70; // Temps avant suppression
    newCommande->next = NULL;
    newCommande->prev = NULL;

    // Ajout de la nouvelle commande à la file
    if (fileCommande->first == NULL || fileCommande->last == NULL) {
        fileCommande->first = newCommande;
        fileCommande->last = newCommande;
    } else {
        fileCommande->last->next = newCommande;
        newCommande->prev = fileCommande->last;
        fileCommande->last = newCommande;
    }
}


void freeFile(File *fileCommande) {
    Commande *toDelete = NULL;
    if (fileCommande->first == NULL) {

        return;
    }

    while (fileCommande->first != NULL) {
        toDelete = fileCommande->first;
        fileCommande->first = fileCommande->first->next;
        al_destroy_bitmap(toDelete->imageCommande);
        free(toDelete);
    }
    fileCommande->first = NULL;
    fileCommande->last = NULL;
}

void initialiserCommande(File *fileCommande) {
    for (int i = 0; i < 3; i++) {

        addCommande(fileCommande);
    }
}


void afficherCommande(File *fileCommande, ALLEGRO_FONT *font) {

    //affiche la file
    float y = 50;
    float x = 100;
    Commande* temp = fileCommande->first;

    for (int n = 0; n < 3 && temp != NULL; n++) {
        al_draw_bitmap(temp->imageCommande, x - 50 + n * 280, y - 45, 0);
        al_draw_textf(font, al_map_rgb(0, 0, 0), x + 65, y + 58, ALLEGRO_ALIGN_CENTER, "%d s", temp->temps);
        temp = temp->next;
    }
   // printf("ok\n");
}
