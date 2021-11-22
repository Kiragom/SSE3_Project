#include "weapon.h"
#include <cmath>
#include "param.h"

void GameWeapon::SetWeapon(float _posx, float _posy, float _power, float _angle, int _type, int _vrange, int _drange) {
    posx = _posx;
    posy = _posy;
    power = _power;
    angle = _angle;
    type = _type;
    valid_range = _vrange;
    destroy_range = _drange;
}

void GameWeapon::SetDamage(float _damage) {
    damage = _damage;
}

float GameWeapon::GetDamage() {
    return damage;
}

int GameWeapon::GetValidRange() {
    return valid_range;
}

int GameWeapon::GetDestroyRange() {
    return destroy_range;
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