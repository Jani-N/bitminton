#define COURT_X 0
#define COURT_Y 0

#define COURT_MAP_COL_COUNT  11

/*
* A map of the court
*/

// C-T--T--T-C
// | |  |  | |
// T-X--X--X-T
// | |  |  | |
// | |  |  | |
// | |  |  | |
// | |  |  | |
// T-X--T--X-T
// | |     | |
// | |     | |
// -----------
// | |     | |
// | |     | |
// T-X--T--X-T
// | |  |  | |
// | |  |  | |
// | |  |  | |
// | |  |  | |
// T-X--X--X-T
// | |  |  | |
// C-T--T--T-C

#define CORNER_EAST_SOUTH 1
#define CORNER_EAST_NORTH 2
#define CORNER_WEST_SOUTH 3
#define CORNER_WEST_NORTH 4

#define LINE_WEST_EAST 5
#define LINE_NORTH_SOUTH 6

#define T_WEST_SOUTH_EAST 7
#define T_WEST_NORTH_EAST 8
#define T_NORTH_EAST_SOUTH 9
#define T_NORTH_WEST_SOUTH 10

#define CROSS 11

const int court[] = {
    CORNER_EAST_SOUTH,  LINE_WEST_EAST, T_WEST_SOUTH_EAST,  LINE_WEST_EAST, LINE_WEST_EAST, T_WEST_SOUTH_EAST,  LINE_WEST_EAST, LINE_WEST_EAST, T_WEST_SOUTH_EAST,  LINE_WEST_EAST, CORNER_WEST_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    T_NORTH_EAST_SOUTH, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, T_NORTH_WEST_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    T_NORTH_EAST_SOUTH, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, LINE_WEST_EAST, T_WEST_NORTH_EAST,  LINE_WEST_EAST, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, T_NORTH_WEST_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             -1,                 -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             -1,                 -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    // net
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             -1,                 -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             -1,                 -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    T_NORTH_EAST_SOUTH, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, LINE_WEST_EAST, T_WEST_SOUTH_EAST,  LINE_WEST_EAST, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, T_NORTH_WEST_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    T_NORTH_EAST_SOUTH, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, LINE_WEST_EAST, CROSS,              LINE_WEST_EAST, T_NORTH_WEST_SOUTH,
    LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             -1,             LINE_NORTH_SOUTH,   -1,             LINE_NORTH_SOUTH,
    CORNER_EAST_NORTH,  LINE_WEST_EAST, T_WEST_NORTH_EAST,  LINE_WEST_EAST, LINE_WEST_EAST, T_WEST_NORTH_EAST,  LINE_WEST_EAST, LINE_WEST_EAST, T_WEST_NORTH_EAST,  LINE_WEST_EAST, CORNER_WEST_NORTH
};

#define TILE_ATLAS_COURT_LINE_NORTH_SOUTH_COL 0
#define TILE_ATLAS_COURT_LINE_NORTH_SOUTH_ROW 0

#define TILE_ATLAS_COURT_LINE_WEST_EAST_COL 1
#define TILE_ATLAS_COURT_LINE_WEST_EAST_ROW 0

#define TILE_ATLAS_COURT_CORNER_WEST_NORTH_COL 2
#define TILE_ATLAS_COURT_CORNER_WEST_NORTH_ROW 0

#define CORNER_ANGLE_EAST_NORTH 90
#define CORNER_ANGLE_EAST_SOUTH 180
#define CORNER_ANGLE_WEST_SOUTH 270

#define TILE_ATLAS_COURT_T_SHAPE_WEST_NORTH_EAST_COL 3
#define TILE_ATLAS_COURT_T_SHAPE_WEST_NORTH_EAST_ROW 0

#define T_SHAPE_ANGLE_NORTH_EAST_SOUTH 90
#define T_SHAPE_ANGLE_WEST_SOUTH_EAST 180
#define T_SHAPE_ANGLE_NORTH_WEST_SOUTH 270

#define TILE_ATLAS_COURT_CROSS_COL 4
#define TILE_ATLAS_COURT_CROSS_ROW 0
