/**
* @file ttf.c
* @author a.brouzes
*/


#include"ttf.h"

/**
* @param TTF 
*/
char ttf_init(TTF *ttf) {
    
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return -1;
    }

    ttf->font = TTF_OpenFont("Blue_Style.ttf", 24); // Change to the path of your font file
    if (ttf->font == NULL) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
       
        return -1;
    }

    return 0;
}	

/**
* @param TTF
*/
void ttf_destroy(TTF* ttf) {
    TTF_CloseFont(ttf->font);
    TTF_Quit();
}

/**
* @param TTF
* @param SDL2
*/
void ttf_renderTexts(TTF* ttf, SDL2 *sdl2) {

    if (ttf->font == NULL) {
        printf("Error: Font not loaded.\n");
        return;
    }

    // Check if the text is not empty
    if (ttf->textes == NULL || ttf->textes[0] == '\0') {
        printf("Error: Empty text.\n");
        return;
    }

    //SDL_Surface* playerScoreSurface = TTF_RenderText_Solid(ttf->font, ttf->textes, (SDL_Color) { 255, 255, 255, 255 });
    SDL_Surface* playerScoreSurface = TTF_RenderUTF8_Solid(ttf->font, ttf->textes, (SDL_Color) { 255, 255, 255, 255 });

    
    if (playerScoreSurface == NULL) {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_FreeSurface(playerScoreSurface);  // Free the surface to avoid memory leaks
        return;
    }

    SDL_Texture* playerScoreTexture = SDL_CreateTextureFromSurface(sdl2->renderer, playerScoreSurface);
    if (playerScoreTexture == NULL) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(playerScoreTexture);  // Free the surface to avoid memory leaks
        return;
    }

    SDL_Rect playerScoreRect = { 10, 10, WINDOW_WIDTH, 200 };
    SDL_RenderCopy(sdl2->renderer, playerScoreTexture, NULL, &playerScoreRect);
    SDL_RenderPresent(sdl2->renderer);

}

