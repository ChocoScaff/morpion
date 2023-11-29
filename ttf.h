#pragma once
/**
* @file ttf.h
* @author a.brouzes
*/

#if defined _TTF

#include <SDL_ttf.h>
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

#endif
