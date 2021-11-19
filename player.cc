#include "player.h"

void GamePlayer::LoadCharacter() {
    player_alive_image.loadFromFile(PLAYER_FILE_ALIVE);
    player_death_image.loadFromFile(PLAYER_FILE_DEATH);
    character_alive = sf::Sprite(player_alive_image);
    character_death = sf::Sprite(player_death_image);
    character_alive.setScale(0.1, 0.1);
    character_death.setScale(0.04, 0.04);
}

void GamePlayer::SetPlayerPosition(int x, int y, int dir) {
    posx = x;
    posy = y;
    direction = dir;
} 

void GamePlayer::GetPlayerPosition(int& x, int& y, int& dir) {
    x = posx;
    y = posy;
    dir = direction;
}

void GamePlayer::SetPlayerMovement(int xdelta, int ydelta) {
    movex = xdelta;
    movey = ydelta;
}

void GamePlayer::GetPlayerMovement(int& xdelta, int& ydelta) {
    xdelta = movex;
    ydelta = movey;
}

void GamePlayer::DrawPlayerPosition(sf::RenderWindow &window) {
    if (death) {
        if (direction == -1) character_death.setPosition(posx - PLAYER_BASE_POSX, posy - PLAYER_BASE_POSY);
        else character_death.setPosition(posx - PLAYER_BASE_POSX + PLAYER_BASE_DIR, posy - PLAYER_BASE_POSY);
        window.draw(character_death);
    }
    else {
        if (direction == -1) character_alive.setPosition(posx - PLAYER_BASE_POSX, posy - PLAYER_BASE_POSY);
        else character_alive.setPosition(posx - PLAYER_BASE_POSX + PLAYER_BASE_DIR, posy - PLAYER_BASE_POSY);
        window.draw(character_alive);
    }
}

void GamePlayer::PlayerMove() {
    posx = posx + movex;
    posy = posy + movey; 
    movex = 0;
    movey = 0;
}

void GamePlayer::MoveRight() {
    movex += 1;
    if (posx + movex > MAX_MAP_POSX - PLAYER_X_BOUND) movex = MAX_MAP_POSX - PLAYER_X_BOUND - posx;
    if (direction == -1) character_alive.setScale(-0.1, 0.1);
    direction = 1;
}

void GamePlayer::MoveLeft() {
    movex -= 1;
    if (posx + movex < PLAYER_X_BOUND) movex = PLAYER_X_BOUND - posx;
    if (direction == 1) character_alive.setScale(0.1, 0.1);
    direction = -1;
}

void GamePlayer::MoveJump() {
    movey -= 5;
    if (posy + movey < PLAYER_Y_BOUND) movey = PLAYER_Y_BOUND - posy;
}

int GamePlayer::Gravity() {
    movey += 2;
    if (posy + movey > MAX_MAP_POSY + PLAYER_Y_BOUND) {
        movey = 0;
        death = 1;
    }
}