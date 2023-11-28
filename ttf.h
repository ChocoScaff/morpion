#pragma once
/**
* @file ttf.h
* @author a.brouzes
*/

#include <SDL_ttf.h>
#include "gui.h"

/**
* 
*/
typedef struct {
	TTF_Font* font;
	char textes[50];
}TTF;


char ttf_init(TTF* ttf);
void ttf_destroy(TTF* ttf);
