#define TILE_ATLAS_PLAYER_COL 0
#define TILE_ATLAS_PLAYER_ROW 1

#define PLAYER_SPEED 80

#define TILE_ATLAS_PLAYER_RANGE_COL 1
#define TILE_ATLAS_PLAYER_RANGE_ROW 2

#define PLAYER_RANGE_FACTOR 1.7f

typedef struct Player_Input {
    unsigned int up;
    unsigned int down;
    unsigned int left;
    unsigned int right;
    // hitting the schuttle
    unsigned int action;
} Player_Input;

