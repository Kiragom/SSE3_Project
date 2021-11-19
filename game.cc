#include "game.h"

Game::Game(int _xlength, int _ylength) {
    xlength = _xlength;
    ylength = _ylength;
    window.create(sf::VideoMode(1600, 800), "WORMS SHOOTNG GAME\n");
    //sf::RenderWindow w(sf::VideoMode(1600, 800), "SFML works!");
}

void Game::StartGame() {
    Nteam = 2;
    Nworm = 3;

    std::vector<int> team_id_shuffle;
    for (int i = 0;i < Nteam;i++) team_id_shuffle.push_back(i);
    std::vector<int> worm_id_shuffle;
    for (int i = 0;i < Nworm;i++) worm_id_shuffle.push_back(i);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(team_id_shuffle.begin(), team_id_shuffle.end(), g);
    std::shuffle(worm_id_shuffle.begin(), worm_id_shuffle.end(), g);

    std::uniform_int_distribution<int> create_position(350, 1250);
    for (int i = 0;i < Nworm;i++) {
        for (int j = 0;j < Nteam;j++) {
            class GamePlayer *worm = new 
        }
    }
    
}