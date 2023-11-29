#pragma once

#include "gui.h"
#include "ttf.h"
#include <stdbool.h>

/**
* @struct MenuItem
*/
typedef struct {
    SDL_Rect rect;
    const char* text;
    SDL_Color textColor;
    bool selected;
} MenuItem;

/**
* @struct Menu
*/
typedef struct {
    MenuItem items[3];  // Assuming a menu with 3 items
    int selectedItem;
} Menu;

/**
* @enum E_MENU
*/
typedef enum {
    MENU_DEUX_JOUEUR,
    MENU_ORDINATEUR,
    MENU_QUIT
}E_MENU;

int menu(SDL2* sdl2);
void renderMenuItem(SDL2* sdl2, MenuItem* item, TTF *ttf);
bool handleMenuEvents(Menu* menu, SDL_Event* event);