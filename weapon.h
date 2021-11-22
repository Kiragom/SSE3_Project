#include <SFML/Graphics.hpp>

#ifndef WEAPON
#define WEAPON

class GameWeapon {
    protected:
    int id;
    int type;
    int range;
    float damage;
    float posx;
    float posy;
    float movex;
    float movey;
    float power;
    float angle;
    int count;
    sf::Sprite weapon_icon;

    public:
    virtual void UpdateMovement() = 0;
    void SetWeapon(float _posx, float _posy, float _power, float _angle, int _type);
    void SetDamage(float _damage);
    float GetDamage();
    void GetDelta(int &delta_x, int &delta_y);
    int GetPosX();
    int GetPosY();
    virtual void DrawWeaponMovement(sf::RenderWindow &window) = 0;
};

#endif