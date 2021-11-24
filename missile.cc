#include "missile.h"
#include <cmath>
#include "param.h"

void Missile::SetMovement() {
    movex = MAX_DIST * (power / 100) * cos((angle * PI) / 180);
    movey = MAX_DIST * (power / 100) * sin((angle * PI) / 180);
}

void Missile::UpdateMovement() {
    posx = posx + movex;
    posy = posy - movey;
    movey -= GRAVITY * 0.1;
}

void Missile::DrawWeaponMovement(sf::RenderWindow &window) {
    sf::CircleShape shape(5.0f);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(sf::Vector2f(posx, posy));
    window.draw(shape);
}

void Missile::SetWeaponIcon() {
    weapon_image.loadFromFile(MISSILE_ICON_FILE);
    weapon_icon.setSize(sf::Vector2f(40, 40));
    weapon_icon.setTexture(&weapon_image);
}