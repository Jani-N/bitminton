#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

unsigned short game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

unsigned short initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
            );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return FALSE;
    }
    renderer = SDL_CreateRenderer(
            window,
            -1, // default display driver
            0
            );
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void process_input() {

}

void update() {

}

void render() {

}

int main() {
    game_is_running = initialize_window(); 

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    return 0;
}
