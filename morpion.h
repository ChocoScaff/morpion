#pragma once
/**
* @file morpion.h
* @author a.brouzes
*/

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "gui.h"

/**
* @struct Morpion
*
*/
typedef struct {
    char grille[3][3]; // Grille 3x3
    int tour;
    char joueur;

    SDL2 sdl2;
}Morpion;


void morpion_initialiserGrille(Morpion* morpion);
void morpion_dessinePlateau(Morpion * morpion);
bool morpion_caseValide(Morpion* morpion, int ligne, int colonne);
bool morpion_verifierFinPartie(Morpion* morpion);
void morpion_jouerCoup(Morpion * morpion, int ligne, int colonne);
