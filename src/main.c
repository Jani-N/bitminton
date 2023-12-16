#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./game.h"
#include "./player.h"
#include "./court.h"

unsigned short game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* tile_atlas_texture;

int last_frame_time = 0;

struct court_tiles {
    SDL_Rect line_north_south;
    SDL_Rect line_west_east;
    SDL_Rect corner_west_north;
    SDL_Rect t_shape_west_north_east;
    SDL_Rect cross;
} court_tiles;

struct player {
    float x;
    float y;
    Player_Input input;
    SDL_Rect tile;
    SDL_Rect range_tile;
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

SDL_Rect setup_tile_rect(
        int rect_x,
        int rect_y,
        unsigned int rect_w,
        unsigned int rect_h) {
    SDL_Rect rect;
    rect.x = rect_x;
    rect.y = rect_y;
    rect.w = rect_w;
    rect.h = rect_h;
    return rect;
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

    SDL_Rect court_tile_line_north_south = setup_tile_rect(
            TILE_ATLAS_COURT_LINE_NORTH_SOUTH_COL * TILE_SIZE,
            TILE_ATLAS_COURT_LINE_NORTH_SOUTH_ROW * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
            );
    SDL_Rect court_tile_line_west_east = setup_tile_rect(
            TILE_ATLAS_COURT_LINE_WEST_EAST_COL * TILE_SIZE,
            TILE_ATLAS_COURT_LINE_WEST_EAST_ROW * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
            );
    SDL_Rect court_tile_corner_west_north = setup_tile_rect(
            TILE_ATLAS_COURT_CORNER_WEST_NORTH_COL * TILE_SIZE,
            TILE_ATLAS_COURT_CORNER_WEST_NORTH_ROW * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
            );
    SDL_Rect court_tile_t_shape_west_north_east = setup_tile_rect(
            TILE_ATLAS_COURT_T_SHAPE_WEST_NORTH_EAST_COL * TILE_SIZE,
            TILE_ATLAS_COURT_T_SHAPE_WEST_NORTH_EAST_ROW * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
            );
    SDL_Rect court_tile_cross = setup_tile_rect(
            TILE_ATLAS_COURT_CROSS_COL * TILE_SIZE,
            TILE_ATLAS_COURT_CROSS_ROW * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
            );

    court_tiles.line_north_south = court_tile_line_north_south;
    court_tiles.line_west_east = court_tile_line_west_east;
    court_tiles.corner_west_north = court_tile_corner_west_north;
    court_tiles.t_shape_west_north_east = court_tile_t_shape_west_north_east;
    court_tiles.cross = court_tile_cross;

    SDL_Rect player_tile_rect = setup_tile_rect(
            TILE_ATLAS_PLAYER_COL * TILE_SIZE,
            TILE_ATLAS_PLAYER_ROW * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
            );

    SDL_Rect player_range_tile_rect = setup_tile_rect(
            TILE_ATLAS_PLAYER_RANGE_COL * TILE_SIZE,
            TILE_ATLAS_PLAYER_RANGE_ROW * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
            );

    player.x = 20;
    player.y = 20;

    player.input.up = FALSE;
    player.input.down = FALSE;
    player.input.left = FALSE;
    player.input.right = FALSE;
    player.input.action = FALSE;

    player.tile = player_tile_rect;

    player.range_tile = player_range_tile_rect;

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
                player.input.up = TRUE;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                player.input.down = TRUE;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                player.input.left = TRUE;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                player.input.right = TRUE;
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP) {
                player.input.up = FALSE;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                player.input.down = FALSE;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                player.input.left = FALSE;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                player.input.right = FALSE;
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

    if (player.input.up && !player.input.down) {
        y_velocity = -PLAYER_SPEED;
    }
    if (player.input.down && !player.input.up) {
        y_velocity = PLAYER_SPEED;
    }
    if (player.input.left && !player.input.right) {
        x_velocity = -PLAYER_SPEED;
    }
    if (player.input.right && !player.input.left) {
        x_velocity = PLAYER_SPEED;
    }

    player.x += x_velocity * delta_time;
    player.y += y_velocity * delta_time;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    // render top left corner of court
    SDL_Rect court_0_0 = {
        COURT_X,
        COURT_Y,
        court_tiles.corner_west_north.w,
        court_tiles.corner_west_north.h
    };
    SDL_RenderCopyEx(
            renderer,
            tile_atlas_texture,
            &court_tiles.corner_west_north,
            &court_0_0,
            180,
            NULL,
            SDL_FLIP_NONE
            );

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

    unsigned int player_range_tile_width =
        player.range_tile.w * PLAYER_RANGE_FACTOR;
    unsigned int player_range_tile_height =
        player.range_tile.h * PLAYER_RANGE_FACTOR;
    // move player range rect so the player rect is in its center
    int player_range_tile_x =
        player.x - (int) (player_range_tile_width - player.tile.w) / 2; 
    int player_range_tile_y =
        player.y - (int) (player_range_tile_height - player.tile.h) / 2; 

    SDL_Rect player_range_rect = {
        (int) player_range_tile_x,
        (int) player_range_tile_y,
        (int) player_range_tile_width,
        (int) player_range_tile_height
    };
    SDL_RenderCopy(
            renderer,
            tile_atlas_texture,
            &player.range_tile,
            &player_range_rect
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
