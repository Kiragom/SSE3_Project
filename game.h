#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "indicator.h"
#include "key_control.h"
#include "map.h"
#include "missile.h"
#include "player.h"
#include "param.h"

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
    Arrow angle_arrow;
    int FLAG_END;

    public:
    Game(int _xlength, int _ylength);
    bool IsOpen();
    void Display();
    void StartGame();
    void GameLoop();
    void EndGame();
};