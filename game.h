#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "indicator.h"
#include "key_control.h"
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
    bool IsOpen();
    void Display();
    void StartGame();
    void GameLoop();
    void DamagePlayers(int pos_x, int pos_y, float damage, GamePlayer* cur_worm);
    void IsEnd();
    void EndGame();
};