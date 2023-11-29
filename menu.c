
#include "menu.h"

int menu(SDL2 *sdl2) {

    Menu menu;
    TTF ttf;
    ttf_init(&ttf);
    
    menu.items[0].text = "2 Joueurs";
    menu.items[1].text = "Ordinateur";
    menu.items[2].text = "Quit";

    for (int i = 0; i < 3; ++i) {
        menu.items[i].rect.x = WINDOW_WIDTH / 2 - 100;
        menu.items[i].rect.y = 150 + i * 50;
        menu.items[i].rect.w = 200; 
        menu.items[i].rect.h = 40;
        menu.items[i].textColor = (SDL_Color){ 255, 255, 255, 255 };
        menu.items[i].selected = false;
    }

    menu.selectedItem = 0;
    menu.items[menu.selectedItem].selected = true;

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                menu.selectedItem = MENU_QUIT;
                quit = true;
            }
            else
                quit = handleMenuEvents(&menu, &event);
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(sdl2->renderer, 0, 0, 0, 255);
        SDL_RenderClear(sdl2->renderer);

        // Render menu items
        for (int i = 0; i < 3; ++i) {
            if (menu.items[i].selected) {
                menu.items[i].textColor = (SDL_Color){ 255, 0, 0, 255 };  // Highlight selected item
            }
            else {
                menu.items[i].textColor = (SDL_Color){ 255, 255, 255, 255 };
            }
            renderMenuItem(sdl2, &menu.items[i], &ttf);
        }

        // Update the screen
        SDL_RenderPresent(sdl2->renderer);

        SDL_Delay(10);  // Add a small delay to avoid high CPU usage
    }
    return menu.selectedItem;
}

void renderMenuItem(SDL2* sdl2, MenuItem* item, TTF *ttf) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(ttf->font, item->text, item->textColor);
    if (textSurface == NULL) {
        printf("Error rendering text: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl2->renderer, textSurface);
    if (textTexture == NULL) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_RenderCopy(sdl2->renderer, textTexture, NULL, &item->rect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

bool handleMenuEvents(Menu* menu, SDL_Event* event) {
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {
        case SDLK_UP:
            menu->items[menu->selectedItem].selected = false;
            menu->selectedItem = (menu->selectedItem - 1 + 3) % 3;  // Wrap around menu items
            menu->items[menu->selectedItem].selected = true;
            break;
        case SDLK_DOWN:
            menu->items[menu->selectedItem].selected = false;
            menu->selectedItem = (menu->selectedItem + 1) % 3;  // Wrap around menu items
            menu->items[menu->selectedItem].selected = true;
            break;
        case SDLK_RETURN:
            // Handle menu item selection
            printf("Selected Item: %s\n", menu->items[menu->selectedItem].text);
            return true;
            break;
        }
        break;
    }
    return false;
}