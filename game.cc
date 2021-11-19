#include "game.h"

Game::Game(int _xlength, int _ylength) {
    xlength = _xlength;
    ylength = _ylength;
    window = new sf::RenderWindow(sf::VideoMode(xlength, ylength), "WORMS SHOOTING GAME");
}

void Game::Display() {
    window->display();
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
            GamePlayer *worm = new GamePlayer;
            worm->SetTeamId(team_id_shuffle[j], worm_id_shuffle[i]);
            worm->SetPlayerPosition(create_position(g), 50, -1);
            worm->SetPlayerMovement(0, 0);
            worm->LoadCharacter();
            worms.push_back(worm);
        }
    }

    map.LoadBackgorund(*window);
    map.SetMapdata(*window);

    power_bar.set_size(100, 15);
    power_bar.set_cur_val(0);
    power_bar.set_max_val(100);

    stamina_bar.set_size(30, 5);
    stamina_bar.set_cur_val(MAX_STAMINA);
    stamina_bar.set_max_val(MAX_STAMINA);

    FLAG_END = 0;
}

bool Game::IsOpen() {
    if (window->isOpen()) return true;
    else return false;
}

void Game::GameLoop() {
    if (FLAG_END) {

    }

    else {
        GamePlayer *master_worm = worms.at(0);
        GamePlayer *tmp;
        int x, y, dir, xdelta, ydelta;

        while(window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
            }

            window->clear();
            map.LoadMapdata(*window, 0);

            for (int i = 0;i < Nteam * Nworm;i++) {
                tmp = worms[i];
                tmp->Gravity();
                tmp->GetPlayerPosition(x, y, dir);
                tmp->GetPlayerMovement(xdelta, ydelta);
                if (map.CheckCollisionGravity(x, y, xdelta, ydelta)) tmp->SetPlayerMovement(xdelta, ydelta - 1);
                tmp->PlayerMove();
                tmp->DrawPlayerPosition(*window);
            }

            window->display();
        }
    }
}