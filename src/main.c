#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./constants.h"
#include "./player_constants.h"

unsigned short game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* tile_atlas_texture;

int last_frame_time = 0;

struct player {
    float x;
    float y;
    unsigned int direction;
    SDL_Rect tile;
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

unsigned int setup(void) {
    SDL_Surface* tile_atlas_surface = IMG_Load("resources/tile_atlas.png");
    if (!tile_atlas_surface) {
        fprintf(stderr, "Error creating tile atlas surface.\n");
        return FALSE;
    }

    tile_atlas_texture = SDL_CreateTextureFromSurface(renderer, tile_atlas_surface);
    SDL_FreeSurface(tile_atlas_surface);
    if (!tile_atlas_texture) {
        fprintf(stderr, "Error creating tile atlas texture.\n");
        return FALSE;
    }

    SDL_Rect player_tile_rect;
    player_tile_rect.x = TILE_ATLAS_PLAYER_COL * TILE_SIZE;
    player_tile_rect.y = TILE_ATLAS_PLAYER_ROW * TILE_SIZE;
    player_tile_rect.w = TILE_SIZE;
    player_tile_rect.h = TILE_SIZE;

    player.x = 20;
    player.y = 20;
    player.direction = 0;
    player.tile = player_tile_rect;

    return TRUE;
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
            if (event.key.keysym.sym == SDLK_UP) {
                player.direction = SDLK_UP;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                player.direction = SDLK_DOWN;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                player.direction = SDLK_LEFT;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                player.direction = SDLK_RIGHT;
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
    int x_velocity = 0;
    int y_velocity = 0;

    if (player.direction == SDLK_UP
            && player.direction != SDLK_DOWN) {
        y_velocity = -PLAYER_SPEED;
    }
    if (player.direction == SDLK_DOWN
            && player.direction != SDLK_UP) {
        y_velocity = PLAYER_SPEED;
    }
    if (player.direction == SDLK_LEFT
            && player.direction != SDLK_RIGHT) {
        x_velocity = -PLAYER_SPEED;
    }
    if (player.direction == SDLK_RIGHT
            && player.direction != SDLK_LEFT) {
        x_velocity = PLAYER_SPEED;
    }

    player.x += x_velocity * delta_time;
    player.y += y_velocity * delta_time;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect player_rect = {
        (int) player.x,
        (int) player.y,
        (int) player.tile.w,
        (int) player.tile.h
    };
    SDL_RenderCopy(
            renderer,
            tile_atlas_texture,
            &player.tile,
            &player_rect
            );

    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    SDL_DestroyTexture(tile_atlas_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    game_is_running = initialize_window() && setup(); 

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
