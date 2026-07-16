#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "joueur.h"
#include "gameplay.h"
#include "map.h"
#include "Ingredient.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Menu.h"

int main(){

    // Declarations
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE *fifo = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_BITMAP *menu = NULL;
    ALLEGRO_BITMAP *scoreboard = NULL;
    ALLEGRO_EVENT_QUEUE *scoreboard_fifo = NULL;
    Images images;
    ImagesIngredients imagesIngredients;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_BITMAP **gif_frames = NULL;


    // Initialisation
    assert(al_init());
    al_init_primitives_addon();
    assert(al_install_keyboard());
    assert(al_init_image_addon());
    assert(al_install_joystick());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    assert(al_install_audio());
    assert(al_init_acodec_addon());
    assert(al_reserve_samples(1)); //reservation d'une place pour la musique du jeu
    assert(al_install_mouse());


    // Creation des elements
    display = al_create_display(WIDSPLAY, HIDSPLAY);
    al_set_window_position(display, 170, 50);
    timer = al_create_timer(1.0 / 60);
    fifo = al_create_event_queue();

    sample = al_load_sample("../musique/La_Cucaracha.wav"); //chargement de la musique
    assert(sample);

    // Sources d'evenements
    al_register_event_source(fifo, al_get_display_event_source(display));
    al_register_event_source(fifo, al_get_timer_event_source(timer));
    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_mouse_event_source());


    chargement(); //ecran de chargement principal


    int niveauCourant = 1;


    Menu(fifo,event, &niveauCourant);
// entrer votre speudo
    chargement2(); //ecran de chargement avec les commandes de jeu

    // Boucle d'evenements
    al_start_timer(timer);
    joueur joueur1;
    joueur joueur2;
    cafard cafard;
    balle balle1;
    balle balle2;
    Assiette assiette;

    gameplay(&joueur1, &joueur2, &cafard, &balle1, &balle2,timer, fifo, event, sample, display, &niveauCourant,&assiette);


    int nombre_frames = 0;
    File* fileCommande;

    liberation(gif_frames, nombre_frames,display,timer, fifo, sample, menu, scoreboard, scoreboard_fifo,  images,  imagesIngredients, font, &joueur1, &joueur2,fileCommande);

}
