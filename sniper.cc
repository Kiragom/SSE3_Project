#include "sniper.h"
#include "param.h"

void Sniper::SetMovement() {
    movex = 0;
    movey = 100;
}

void Sniper::UpdateMovement() {
    posx = posx + movex;
    posy = posy + movey;
}

void Sniper::DrawWeaponMovement(sf::RenderWindow &window) {
    object.setPosition(sf::Vector2f(posx - SNIPER_X_TRANS, posy));
    window.draw(object);
}

void Sniper::SetObject() {
    object_image.loadFromFile(WEAPON_SNIPER_FILE);
    object.setTexture(object_image);
    object.setScale(0.4, 0.4);
}