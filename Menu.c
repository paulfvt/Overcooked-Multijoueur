#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <math.h>
#include "Menu.h"


void Menu(ALLEGRO_EVENT_QUEUE* fifo, ALLEGRO_EVENT event, int *niveauCourant){

    // géneration des images du menu
    ALLEGRO_BITMAP *menu = al_load_bitmap("../assets/Image/menu.png");
    ALLEGRO_BITMAP *scoreboard = al_load_bitmap("../assets/Image/scoreboard.png");
    ALLEGRO_BITMAP *loadgame = al_load_bitmap("../assets/Image/loadgame.png");


    //fifo pour scoreboard
    ALLEGRO_EVENT_QUEUE *scoreboard_fifo = al_create_event_queue();
    al_register_event_source(scoreboard_fifo, al_get_mouse_event_source());

    ALLEGRO_EVENT_QUEUE *loadgame_fifo = al_create_event_queue();
    al_register_event_source(loadgame_fifo, al_get_mouse_event_source());

    bool DansMenu = true;



    while (DansMenu) {

        al_draw_bitmap(menu, 0, 0, 0);
        al_flip_display();

        al_wait_for_event(fifo, &event);

        switch (event.type) {
            // enfoncement du clic gauche de la souris
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {

                // recup des coordonées de la souris
                int mouseX = event.mouse.x;
                int mouseY = event.mouse.y;

                // commmande new game du menu
                if (mouseX >= 600 && mouseX <= 1000 && mouseY >= 20 && mouseY <= 140) { //coordonnées de la souris par rapport aux rectangles
                    DansMenu = false;
                    *niveauCourant = 1;
                }

                // commmande load game du menu
                if (mouseX >= 605 && mouseX <= 1000 && mouseY >= 155 && mouseY <= 265) {
                    al_draw_bitmap(loadgame, 0, 0, 0);
                    al_flip_display();
                    int inLoadgame = true;
                    while (inLoadgame) {
                        ALLEGRO_EVENT loadgame_event;
                        al_wait_for_event(scoreboard_fifo, &loadgame_event);
                        if (loadgame_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                            int mouseX = loadgame_event.mouse.x;
                            int mouseY = loadgame_event.mouse.y;
                            if (mouseX >= 1155 && mouseX <= 1234 && mouseY >= 15 && mouseY <= 92) {
                                inLoadgame = false;
                            }
                            else if (mouseX >= 50 && mouseX <= 410 && mouseY >= 170 && mouseY <= 330) {
                                inLoadgame = false;
                                DansMenu = false;
                                *niveauCourant = 1;
                            }
                            else if (mouseX >= 45 && mouseX <= 410 && mouseY >= 340 && mouseY <= 500) {
                                inLoadgame = false;
                                DansMenu = false;
                                *niveauCourant = 2;
                            }
                            else if (mouseX >= 40 && mouseX <= 410 && mouseY >= 525 && mouseY <= 690) {
                                inLoadgame = false;
                                DansMenu = false;
                                *niveauCourant = 3;
                            }
                        }
                    }
                }

                // commmande scoreboard du menu
                if (mouseX >= 605 && mouseX <= 1000 && mouseY >= 285 && mouseY <= 385) {
                    al_draw_bitmap(scoreboard, 0, 0, 0);
                    al_flip_display();
                    int inScoreboard = true;
                    while (inScoreboard) {
                        ALLEGRO_EVENT scoreboard_event;
                        al_wait_for_event(scoreboard_fifo, &scoreboard_event);
                        if (scoreboard_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                            int mouseX = scoreboard_event.mouse.x;
                            int mouseY = scoreboard_event.mouse.y;
                            if (mouseX >= 1155 && mouseX <= 1234 && mouseY >= 15 && mouseY <= 92) {
                                inScoreboard = false;
                            }
                        }
                    }
                }
                // commmande exit du menu
                if (mouseX >= 600 && mouseX <= 905 && mouseY >= 430 && mouseY <= 512) {
                    al_destroy_event_queue(fifo);
                    exit(DansMenu);
                }
                break;
            }

        }
    }
}


