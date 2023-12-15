#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

unsigned short game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct player {
    float x;
    float y;
    float width;
    float height;
} player;

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

void setup(void) {
    player.x = 20;
    player.y = 20;
    player.width = 15;
    player.height = 15;
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game_is_running = FALSE;
            }
            break;
    }
}

void update(void) {
    // Lock execution
    int time_to_wait = FRAME_TARGET_TIME - SDL_GetTicks() - last_frame_time;
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    // Delta time in seconds to update objects
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

    player.x += 70 * delta_time;
    player.y += 50 * delta_time;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect player_rect = {
        (int) player.x,
        (int) player.y,
        (int) player.width,
        (int) player.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &player_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    game_is_running = initialize_window(); 

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
