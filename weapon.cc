#include <cmath>
#include "weapon.h"
#include "param.h"

void GameWeapon::SetWeapon(float _posx, float _posy, float _power, float _angle, int _type) {
    posx = _posx;
    posy = _posy;
    power = _power;
    angle = _angle;
    type = _type;

    movex = MAX_DIST * (power / 100) * cos((angle * PI) / 180);
    movey = MAX_DIST * (power / 100) * sin((angle * PI) / 180);
}

void GameWeapon::SetDamage(float _damage) {
    damage = _damage;
}

float GameWeapon::GetDamage() {
    return damage;
}

void GameWeapon::GetDelta(int &delta_x, int &delta_y) {
    delta_x = (int)round(movex);
    delta_y = (int)round(movey);
    delta_y *= -1;
}

int GameWeapon::GetPosX() {
    return (int)round(posx);
}

int GameWeapon::GetPosY() {
    return (int)round(posy);
}