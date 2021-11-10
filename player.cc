#include "player.h"

void GamePlayer::LoadCharacter() {
    player_image.loadFromFile(PLAYER_FILE);
    character = sf::Sprite(player_image);
    character.setScale(0.1, 0.1);
}

void GamePlayer::SetPlayerPosition(int x, int y) {
    posx = x;
    posy = y;
} 

void GamePlayer::DrawPlayerPosition(sf::RenderWindow &window) {
    character.setPosition(posx, posy);
    window.draw(character);
}

void GamePlayer::test() {
    posx+=5;
}