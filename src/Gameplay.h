#ifndef TESTPROJECT_GAMEPLAY_H
#define TESTPROJECT_GAMEPLAY_H
#include "joueur.h"
#include "map.h"
#include "Ingredient.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define DEG_TO_RAD(x) ((x) * ALLEGRO_PI / 180)




void dessinerTout(joueur* joueur1, joueur* joueur2,cafard* cafard, ALLEGRO_BITMAP* gif_frames_cafard[], int* frame_actuelle_cafard,balle* balle1, balle* balle2, int cuisine[9][17],Images images,ImagesIngredients imagesIngredients,bool flags [12],ALLEGRO_FONT* font, int temps, File *fileClients, int score);

void EntrerSpeudo(ALLEGRO_DISPLAY* dispaly,Images images);

void liberer_gif_cafard(ALLEGRO_BITMAP **gif_frames, int nombre_frames);

void liberation(ALLEGRO_BITMAP **gif_frames, int nombre_frames, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* fifo, ALLEGRO_SAMPLE* sample, ALLEGRO_BITMAP *menu, ALLEGRO_BITMAP *scoreboard, ALLEGRO_EVENT_QUEUE *scoreboard_fifo, Images images, ImagesIngredients imagesIngredients, ALLEGRO_FONT* font,joueur* joueur1, joueur* joueur2,File *fileCommande);

void saisirAssiette(joueur* joueur1,joueur* joueur2, Images images, bool flags[12],int cuisine[NOMBRESL][NOMBRESC]);

void saisirTomate(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12],int cuisine[NOMBRESL][NOMBRESC]);

void DessinerSaisirAssiette(joueur* joueur1,joueur* joueur2, Images images);

void DessinerSaisirtomates(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients);

void DessinerSaisirfromage(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients);

void DessinerSaisirpoivron(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients);

void DessinerSaisirtortilla(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients);

void DessinerSaisirviande(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients);

void DessinerSaisirsalade(joueur* joueur1,joueur* joueur2, ImagesIngredients imagesIngredients);

void decouperTomate(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void decouperPoivron(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void decouperFromage(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void cuireViande(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void saisirFromage(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void saisirPoivron(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void saisirTortilla(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void saisirViande(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void saisirSalade(joueur* joueur1, joueur* joueur2, ImagesIngredients imagesIngredients, bool flags[12], int cuisine[NOMBRESL][NOMBRESC]);

void dessinerTomateDecoupe(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients);

void dessinerPoivronDecoupe(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients);

void dessinerFromageDecoupe(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients);

void dessinerViandeCuite(joueur *joueur1, joueur *joueur2, ImagesIngredients imagesIngredients);



// void tempsAttentePreparationAliment(ALLEGRO_DISPLAY* display, int cuisine [NOMBRESL][NOMBRESC]);

// void dessinerConstructionDeLaTortilla(Assiette* assiette, int* recette);

// fonction principale de jeu, lance le jeu
void gameplay(joueur* joueur1, joueur* joueur2 , cafard * cafard, balle* balle1,balle* balle2, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* fifo, ALLEGRO_EVENT event, ALLEGRO_SAMPLE *sample, ALLEGRO_DISPLAY* display, int * niveauCourant, Assiette* assiette);

#endif //TESTPROJECT_GAMEPLAY_H