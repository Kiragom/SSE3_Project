#ifndef PARAM
#define PARAM

#define MAX_MAP_POSX    1601
#define MAX_MAP_POSY    801

#define BACKGROUND_FILE         "electricity.jpg"
#define MAP_FILE                "test.jpg"
#define PLAYER_FILE_ALIVE       "player_character_alive.png"
#define PLAYER_FILE_DEATH       "player_character_death.png"
#define FONT_FILE               "example_font.ttf"

#define PLAYER_BASE_POSX        11
#define PLAYER_BASE_POSY        30
#define PLAYER_BASE_DIR         23
#define PLAYER_X_BOUND          15
#define PLAYER_Y_BOUND          35

#define TIME_LIMIT  15000000
#define MAX_STAMINA 250
#define MAX_HP  100
#define MAX_JUMP_CNT 15

#define MAX_DIST 100
#define PI 3.1415926535
#define GRAVITY 74
#define MISSILE_DAMAGE 25
#define MIN_DAMAGE 100

#define BAR_WIDTH 30
#define BAR_HEIGHT 5
#define ARROW_LEN 15

#define POWER_DELTA 1.5
#define ANGLE_DELTA 1.5

#define LEFT -1
#define RIGHT 1

enum cur_state{
    FIRE,
    MOVE,
    WAIT_POWER,
    WAIT_ANGLE,
    STOP,
    JUMP,
    FALL
};

#endif