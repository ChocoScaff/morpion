/**
* @file main.c
* @author a.brouzes
*/


#if defined(_WIN32)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include "morpion.h"
#include "gui.h"
#include "ttf.h"
#include "menu.h"

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

    srand(time(NULL));
    char ordinateurX;
    char ordinateurY;

    Morpion morpion;
    //memset(morpion, 0, sizeof(Morpion));
    morpion.sdl2.window = NULL;
    morpion.sdl2.renderer = NULL;
    morpion.tour = 0;
    morpion.joueur = 1;
    morpion_initialiserGrille(&morpion);

    gui_init(&morpion.sdl2);

    
    switch(menu(&morpion.sdl2)) {
        case MENU_DEUX_JOUEUR:
            morpion.nbrJoueur = 2;
            break;
        case MENU_ORDINATEUR:
            morpion.nbrJoueur = 1;
            break;
        case MENU_QUIT:
            gui_destroy(&morpion.sdl2);
            SDL_Quit();
            return 0;
            break;
    }

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
                        //SDL_Delay(1000);
                        break;
                    }
                    if (morpion.nbrJoueur == 1) {

                        printf("L'ordinateur joue\n");
                        do {
                            ordinateurX = rand() % 3;
                            ordinateurY = rand() % 3;
                        }
                        while (!(morpion_caseValide(&morpion, ordinateurY, ordinateurX)));
                        morpion_jouerCoup(&morpion, ordinateurY, ordinateurX);
                    }
                    if (morpion_verifierFinPartie(&morpion)) {
                        running = false;
                        //SDL_Delay(1000);
                        break;
                    }
                }
                break;
            }
        }

        morpion_dessinePlateau(&morpion);
        SDL_Delay(10); // Limite la vitesse d'affichage
    }


    printf("joueur %d a gagné\n", morpion.joueur);
    SDL_Delay(1000);
    gui_destroy(&morpion.sdl2);

    SCORE score;
    score.ttf.font = NULL;
    score.sdl2.renderer = NULL;
    score.sdl2.window = NULL;

    gui_init(&score.sdl2);

    gui_displayBMP(&score.sdl2, "Big_Rigs_Over_the_Road_Racing_trophy.bmp");

    ttf_init(&score.ttf);
    if (morpion.joueur == 0) {
        sprintf(score.ttf.textes, "egaliter\n");
    }
    else {
        sprintf(score.ttf.textes, "joueur %d a gagne \n", morpion.joueur);
    }
    ttf_renderTexts(&score.ttf, &score.sdl2);

    SDL_Delay(50000);

    gui_destroy(&score.sdl2);

    ttf_destroy(&score.ttf);

    SDL_Quit();

    return 0;
}
