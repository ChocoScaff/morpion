/**
* @file main.c
* @author a.brouzes
*/

#include "morpion.h"
#include "gui.h"
#include "ttf.h"
/**
* 
*/
int main() {

    Morpion morpion;
    //memset(morpion, 0, sizeof(Morpion));
    morpion.sdl2.window = NULL;
    morpion.sdl2.renderer = NULL;
    morpion.tour = 0;
    morpion_initialiserGrille(&morpion);

    gui_init(&morpion.sdl2);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int ligne = event.button.y / CELL_SIZE;
                    int colonne = event.button.x / CELL_SIZE;
                    morpion_jouerCoup(&morpion, ligne, colonne);
                    if (morpion_verifierFinPartie(&morpion)) {
                        running = false;
                    }
                }
                break;
            }
        }

        morpion_dessinePlateau(&morpion);
        SDL_Delay(10); // Limite la vitesse d'affichage
    }

    printf("joueur %d a gagner\n", morpion.joueur);

    gui_destroy(&morpion.sdl2);

    SDL2 score;
    gui_init(&score);
    
    SDL_Delay(5000);

    gui_destroy(&score);

    SDL_Quit();

    return 0;
}
