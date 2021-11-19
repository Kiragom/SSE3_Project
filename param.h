#define MAX_MAP_POSX    1601
#define MAX_MAP_POSY    801

#define BACKGROUND_FILE         "electricity.jpg"
#define MAP_FILE                "test.jpg"
#define PLAYER_FILE_ALIVE       "player_character_alive.png"
#define PLAYER_FILE_DEATH       "player_character_death.png"

#define PLAYER_BASE_POSX        11
#define PLAYER_BASE_POSY        30
#define PLAYER_BASE_DIR         23
#define PLAYER_X_BOUND          15
#define PLAYER_Y_BOUND          35

#define TIME_LIMIT  10000000
#define MAX_STAMINA 250
#define MAX_JUMP_CNT 15

enum _GAMESTATE {
    START,
    PLAYING,
    END
};
