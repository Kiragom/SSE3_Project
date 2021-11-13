#include "player.h"

void GamePlayer::LoadCharacter() {
    player_alive_image.loadFromFile(PLAYER_FILE_ALIVE);
    player_death_image.loadFromFile(PLAYER_FILE_DEATH);
    character_alive = sf::Sprite(player_alive_image);
    character_death = sf::Sprite(player_death_image);
    character_alive.setScale(0.1, 0.1);
    character_death.setScale(0.04, 0.04);


}

void GamePlayer::SetPlayerPosition(int x, int y) {
    posx = x;
    posy = y;
    direction = 1;
} 

std::vector<int> GamePlayer::GetPlayerPosition() {
    std::vector<int> position;
    position.push_back(posx);
    position.push_back(posy);

    return position;
}

void GamePlayer::DrawPlayerPosition(sf::RenderWindow &window) {
    character_alive.setPosition(posx, posy);
    window.draw(character_alive);
}

void GamePlayer::MoveRight() {
    posx += 5;
    if (posx > MAX_MAP_POSX - 20) posx = MAX_MAP_POSX - 20;
    direction = 1;
}

void GamePlayer::MoveLeft() {
    posx -= 5;
    if (posx < 0) posx = 0;
    direction = -1;
}

void GamePlayer::MoveJump() {
    posy -= 5;
    if (posy < 0) posy = 0;
}

int GamePlayer::Gravity() {
    posy += 2;
}