#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "indicator.h"
#include "map.h"
#include "weapon.h"
#include "missile.h"
#include "sniper.h"
#include "player.h"

class Game {
    private:
    sf::RenderWindow *window;
    unsigned int xlength;
    unsigned int ylength;
    int Nteam;
    int team_id;
    int Nworm;
    int worm_id;
    int turn_cnt = 0;
    int weapon_select;
    GameMap map;
    std::vector<class GamePlayer *> worms;
    Bar power_bar;
    Bar stamina_bar;
    Missile missile;
    Sniper sniper;
    Arrow angle_arrow;
    Aim aim;
    int FLAG_END;

    public:
    Game(int _xlength, int _ylength);
    ~Game();
    bool IsOpen();
    void Display();
    void StartGame();
    void GameLoop();
    void CheckWaterDeath();
    void DamagePlayers(int pos_x, int pos_y, float damage, GamePlayer* cur_worm);
    void IsEnd();
    void EndGame();
};