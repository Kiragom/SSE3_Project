#include <SFML/Graphics.hpp>
#include "weapon.h"

#ifndef MISSILE
#define MISSILE

class Missile : public GameWeapon {
    public:
    void UpdateMovement() override;
    void DrawWeaponMovement(sf::RenderWindow &window) override;
};

#endif