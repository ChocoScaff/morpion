/**
* @file main.c
* @author a.brouzes
*/


#if defined(_WIN32)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "morpion.h"
#include "gui.h"
#include "ttf.h"

/**
* @struct Score
*/
typedef struct {
    SDL2 sdl2;
    TTF ttf;
}SCORE;


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

    printf("joueur %d a gagné\n", morpion.joueur);
    
    gui_destroy(&morpion.sdl2);

    SCORE score;
    score.ttf.font = NULL;
    score.sdl2.renderer = NULL;
    score.sdl2.window = NULL;

    gui_init(&score.sdl2);

    gui_displayBMP(&score.sdl2, "victoire.bmp");
    //ttf_init(&score.ttf);
    
    //sprintf(score.ttf.textes, "joueur %d a gagné\n", morpion.joueur);
    //ttf_renderTexts(&score.ttf, &score.sdl2);
    SDL_Delay(5000);

    gui_destroy(&score.sdl2);
    ttf_destroy(&score.ttf);

    SDL_Quit();

    return 0;
}
