/**
* @file gui.c
* @author a.brouzes
*/
#include "gui.h"

/**
* @param SDL2
*/
void gui_init(SDL2 *sdl2) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    sdl2->window = SDL_CreateWindow("Morpion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (sdl2->window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    sdl2->renderer = SDL_CreateRenderer(sdl2->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdl2->renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(sdl2->window);
        SDL_Quit();
        return 1;
    }
}

/**
* @param SDL2
*/
void gui_destroy(SDL2* sdl2) {
    SDL_DestroyRenderer(sdl2->renderer);
    SDL_DestroyWindow(sdl2->window);
}


void gui_displayBMP(SDL2* sdl2, const char file[]) {
    SDL_Surface* surface = SDL_LoadBMP(file);
    if (NULL == surface)
    {
        printf("Erreur SDL_LoadBMP : %s", SDL_GetError());
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl2->renderer, surface);
    if (NULL == texture)
    {
       printf("Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
    }
    SDL_Rect playerScoreRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy(sdl2->renderer, texture, NULL, NULL);
    SDL_RenderPresent(sdl2->renderer);

    SDL_FreeSurface(surface); /* On libère la surface, on n’en a plus besoin */

}
