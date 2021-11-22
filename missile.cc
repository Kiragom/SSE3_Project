#include "missile.h"
#include "param.h"

void Missile::UpdateMovement() {
    posx = posx + movex;
    posy = posy - movey;
    movey -= GRAVITY * 0.1;
}

void Missile::DrawWeaponMovement(sf::RenderWindow &window) {
    sf::CircleShape shape(5.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2f(posx, posy));
    window.draw(shape);
}