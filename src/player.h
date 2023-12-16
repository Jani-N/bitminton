#define TILE_ATLAS_PLAYER_COL 7
#define TILE_ATLAS_PLAYER_ROW 0

#define PLAYER_SPEED 80

#define TILE_ATLAS_PLAYER_RANGE_COL 6
#define TILE_ATLAS_PLAYER_RANGE_ROW 0

#define PLAYER_RANGE_FACTOR 1.7f

typedef struct Player_Input {
    unsigned int up;
    unsigned int down;
    unsigned int left;
    unsigned int right;
    // hitting the schuttle
    unsigned int action;
} Player_Input;

