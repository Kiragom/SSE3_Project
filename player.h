#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"
#include "indicator.h"
#include "weapon.h"

#ifndef PLAYER
#define PLAYER

class GamePlayer {
    private:
    sf::Texture player_alive_image;
    sf::Texture player_death_image;
    sf::Sprite character_alive;
    sf::Sprite character_death;
    Bar hp_bar;

    int posx;
    int posy;
    int movex;
    int movey;
    int team;
    int id;
    int death = 0;
    int direction;

    public:
    void LoadCharacter();
    void SetPlayerPosition(int x, int y, int dir);
    void GetPlayerPosition(int& x, int& y, int& dir);
    void SetPlayerMovement(int xdelta, int ydelta);
    void GetPlayerMovement(int& xdelta, int& ydelta);
    void SetTeamId(int _team, int _id);
    void GetTeamId(int& _team, int& _id);
    void SetHpBarColor(sf::Color bar_color);
    void SetHpBarPos(float pos_x, float pos_y);
    void GetDamage(float damage);
    bool IsDeath();
    void PlayerMove();
    void MoveRight();
    void MoveLeft();
    void MoveJump();
    int Gravity();
    void DrawHpBar(sf::RenderWindow &window);
    void DrawPlayerPosition(sf::RenderWindow &window);
};

#endif