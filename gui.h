#pragma once
/**
* @file gui.h
* @author a.brouzes
*/

#if defined(__unix__) 
#include <SDL2/SDL.h>
#endif
#if defined(WIN32)
#include <SDL.h>
#endif


#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 480
#define CELL_SIZE 160

/**
* @struct SDL2
*
*/
typedef struct {
    SDL_Window * window;
    SDL_Renderer* renderer;
} SDL2;


void gui_init(SDL2* sdl2);
void gui_destroy(SDL2* sdl2);
void gui_displayBMP(SDL2* sdl2, const char file[]);
