#pragma once
/**
* @file ttf.h
* @author a.brouzes
*/

#if defined (__unix__)
#include <SDL2/SDL_ttf.h>
#endif
#if defined (WIN32)
#include <SDL_ttf.h>
#endif
#include "gui.h"

/**
* @struct TTF
*/
typedef struct {
	TTF_Font* font;
	char textes[100];
}TTF;


char ttf_init(TTF* ttf);
void ttf_destroy(TTF* ttf);

