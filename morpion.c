/**
* @file morpion.c
* @author a.brouzes
*/

#include "morpion.h"

/**
* @param Morpion
*
*/
void morpion_initialiserGrille(Morpion* morpion) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            morpion->grille[i][j] = ' ';
        }
    }
}

/**
* @param Morpion
*/
void morpion_dessinePlateau(Morpion* morpion) {
    SDL_SetRenderDrawColor(morpion->sdl2.renderer, 0, 0, 0, 255);
    SDL_RenderClear(morpion->sdl2.renderer);

    SDL_SetRenderDrawColor(morpion->sdl2.renderer, 255, 255, 255, 255);
    for (int i = 1; i < 3; ++i) {
        SDL_RenderDrawLine(morpion->sdl2.renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_HEIGHT);
        SDL_RenderDrawLine(morpion->sdl2.renderer, 0, i * CELL_SIZE, WINDOW_WIDTH, i * CELL_SIZE);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (morpion->grille[i][j] == 'X') {
                SDL_SetRenderDrawColor(morpion->sdl2.renderer, 255, 0, 0, 255); // Couleur rouge pour 'X'
                SDL_RenderDrawLine(morpion->sdl2.renderer, j * CELL_SIZE + 10, i * CELL_SIZE + 10, (j + 1) * CELL_SIZE - 10, (i + 1) * CELL_SIZE - 10);
                SDL_RenderDrawLine(morpion->sdl2.renderer, j * CELL_SIZE + 10, (i + 1) * CELL_SIZE - 10, (j + 1) * CELL_SIZE - 10, i * CELL_SIZE + 10);
            }
            else if (morpion->grille[i][j] == 'O') {
                SDL_SetRenderDrawColor(morpion->sdl2.renderer, 0, 255, 0, 255); // Couleur bleue pour 'O'
                int centerX = j * CELL_SIZE + CELL_SIZE / 2;
                int centerY = i * CELL_SIZE + CELL_SIZE / 2;
                int radius = CELL_SIZE / 2 - 10;
                for (int k = 0; k <= 360; k += 10) {
                    double angle = k * 3.14159265 / 180.0;
                    int x = centerX + (int)(radius * cos(angle));
                    int y = centerY + (int)(radius * sin(angle));
                    SDL_RenderDrawPoint(morpion->sdl2.renderer, x, y);
                }
            }
        }
    }

    SDL_RenderPresent(morpion->sdl2.renderer);
}

/**
*
* @param Morpion
* @param ligne
* @param colonne
*
* @return true if case valide
*/
bool morpion_caseValide(Morpion* morpion, int ligne, int colonne) {
    if (morpion->grille[ligne][colonne] != ' ') {
        printf("Déja selectionner ! \n");
        return false;
    }
    else {
        return true;
    }
}

/**
*
* @return true if fin de partie
*
* @param Morpion
*
*/
bool morpion_verifierFinPartie(Morpion* morpion) {
    // Vérification des lignes pour un gagnant
    for (int i = 0; i < 3; i++) {
        if (morpion->grille[i][0] != ' ' && morpion->grille[i][0] == morpion->grille[i][1] && morpion->grille[i][1] == morpion->grille[i][2]) {
            return true; // Un joueur a gagné
        }
    }

    // Vérification des colonnes pour un gagnant
    for (int i = 0; i < 3; i++) {
        if (morpion->grille[0][i] != ' ' && morpion->grille[0][i] == morpion->grille[1][i] && morpion->grille[1][i] == morpion->grille[2][i]) {
            return true; // Un joueur a gagné
        }
    }

    // Vérification des diagonales pour un gagnant
    if (morpion->grille[0][0] != ' ' && morpion->grille[0][0] == morpion->grille[1][1] && morpion->grille[1][1] == morpion->grille[2][2]) {
        return true; // Un joueur a gagné
    }
    if (morpion->grille[0][2] != ' ' && morpion->grille[0][2] == morpion->grille[1][1] && morpion->grille[1][1] == morpion->grille[2][0]) {
        return true; // Un joueur a gagné
    }

    // Vérification de match nul
    int casesRemplies = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (morpion->grille[i][j] != ' ') {
                casesRemplies++;
            }
        }
    }
    if (casesRemplies == 9) {
        return true; // Match nul
    }

    if (morpion->joueur == 0) {
        morpion->joueur = 1;
    }
    else {
        morpion->joueur = 1;
    }

    return false; // La partie continue
}


/**
*
* @param Morpion
* @param ligne
* @param colonne
*
*/
void morpion_jouerCoup(Morpion* morpion, int ligne, int colonne) {
    char joueur = (morpion->tour % 2 == 0) ? 'X' : 'O';
    if (morpion_caseValide(morpion, ligne, colonne)) {
        morpion->grille[ligne][colonne] = joueur;
        morpion->tour++;
    }
}