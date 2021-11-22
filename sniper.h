#include <SFML/Graphics.hpp>
#include "weapon.h"

#ifndef SNIPER
#define SNIPER

class Sniper : public GameWeapon {
    private:
    sf::Texture object_image;
    sf::Sprite object;

    public:
    void SetMovement() override;
    void UpdateMovement() override;
    void DrawWeaponMovement(sf::RenderWindow &window) override;
    void SetObject();
};

#endif