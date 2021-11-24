#include <SFML/Graphics.hpp>

#ifndef WEAPON
#define WEAPON

class GameWeapon {
    protected:
    int id;
    int type;
    int valid_range;
    int destroy_range;
    float damage;
    float posx;
    float posy;
    float movex;
    float movey;
    float power;
    float angle;
    int count;
    sf::Texture weapon_image;
    sf::RectangleShape weapon_icon;

    public:
    virtual void UpdateMovement() = 0;
    virtual void SetMovement() = 0;
    virtual void DrawWeaponMovement(sf::RenderWindow &window) = 0;
    void SetWeapon(float _posx, float _posy, float _power, float _angle, int _type, int _vrange, int _drange);
    void SetDamage(float _damage);
    float GetDamage();
    int GetValidRange();
    int GetDestroyRange();
    void GetDelta(int &delta_x, int &delta_y);
    int GetPosX();
    int GetPosY();
    virtual void SetWeaponIcon() = 0;
    void DrawWeaponIcon(sf::RenderWindow &window, int posx, int posy);
};

#endif