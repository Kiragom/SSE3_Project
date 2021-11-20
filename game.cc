#include "game.h"
#include "param.h"
#include "player.h"

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

    sf::Color color_list[3] = {sf::Color::Red, sf::Color::Blue};

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
            worm->SetHpBarColor(color_list[j]);
            worms.push_back(worm);
        }
    }

    map.LoadBackgorund(*window);
    map.SetMapdata(*window);

    power_bar.set_size(100, 15);
    power_bar.set_cur_val(0);
    power_bar.set_max_val(100);
    power_bar.set_color(sf::Color::Cyan);

    stamina_bar.set_size(30, 5);
    stamina_bar.set_cur_val(MAX_STAMINA);
    stamina_bar.set_max_val(MAX_STAMINA);
    stamina_bar.set_color(sf::Color::Yellow);

    FLAG_END = 0;
}

bool Game::IsOpen() {
    if (window->isOpen()) return true;
    else return false;
}

void Game::DamagePlayers(int pos_x, int pos_y, float damage, GamePlayer* cur_worm) {
    int player_x, player_y, player_dir, cur_team_id, cur_worm_id;

    cur_worm->GetTeamId(cur_team_id, cur_worm_id);

    for(int i=0; i<Nteam*Nworm; i++){
        int target_team_id, target_worm_id;
        worms[i]->GetTeamId(target_team_id, target_worm_id);
        if(cur_team_id == target_team_id) continue;

        worms[i]->GetPlayerPosition(player_x, player_y, player_dir);
        int dis = (pos_x - player_x) * (pos_x - player_x) + (pos_y - player_y) * (pos_y - player_y);
        if(dis <= 1600){
            float total_damage = ((float)dis / 1600) * damage;
            printf("total damage : %lf\n", MIN_DAMAGE + total_damage);
            worms[i]->GetDamage(MIN_DAMAGE + total_damage);
        }
    }
}

void Game::IsEnd() {
    int alive_team[Nteam], team, id;
    for (int i = 0;i < Nteam;i++) alive_team[i] = 0;

    for(int i=0; i<Nteam*Nworm; i++){
        if (!worms[i]->IsDeath()) {
            worms[i]->GetTeamId(team, id);
            alive_team[team]++;
        }
    }

    int cnt = 0;
    for (int i = 0;i < Nteam;i++) {
        if (alive_team[i]) {
            cnt++;
            //team = i;
        }
    }

    if (cnt == 1) FLAG_END = 1;
}

void Game::GameLoop() {
    if (FLAG_END) {
        window->clear();
        window->display();
    }

    else {
        GamePlayer *master_worm = worms.at(0);
        GamePlayer *tmp;
        Missile missile;
        float power_delta = POWER_DELTA, angle_delta = ANGLE_DELTA, power = 0, angle = 0;
        int x, y, prev_x, prev_y, dir, xdelta, ydelta, player_dir = LEFT, jump_cnt = 0;
        int state = FALL;

        stamina_bar.set_cur_val(MAX_STAMINA);
        power_bar.set_cur_val(0);
        missile.set_damage(MISSILE_DAMAGE);

        if(master_worm->IsDeath()){
            worms.erase(worms.begin());
            worms.push_back(master_worm);
            return;
        }

        while(window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();

                if (event.type == sf::Event::KeyPressed){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        master_worm->GetPlayerPosition(x, y, dir);
                        if(state == WAIT_ANGLE){
                            if(dir==-1)
                                missile.set_missile(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY, power, angle, Arc);
                            else
                                missile.set_missile(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, y - PLAYER_BASE_POSY, power, angle, Arc);
                            state = FIRE;
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        if(state == MOVE || state == STOP) {
                            state = WAIT_POWER;
                            power_bar.set_cur_val(0);
                            power = 0;
                        }
                        else if(state == WAIT_POWER) {
                            master_worm->GetPlayerPosition(x, y, dir);
                            state = WAIT_ANGLE;

                            if(dir == LEFT) {
                                player_dir = LEFT;
                                angle = 180;
                            }
                            else {
                                player_dir = RIGHT;
                                angle = 0;
                            }
                        }
                    }
                }
            }

            master_worm->GetPlayerPosition(x, y, dir);
            prev_x = x; prev_y = y;

            if(stamina_bar.get_cur_val() == 0){
                if(state == MOVE){
                    state = STOP;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    dir = RIGHT;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    dir = LEFT;
                }

                master_worm->SetPlayerPosition(x, y, dir);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (state == MOVE || state == JUMP || state == FALL)) {
                master_worm->MoveRight();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (state == MOVE || state == JUMP || state == FALL)) {
                master_worm->MoveLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && state == MOVE) {
                master_worm->MoveJump();
                jump_cnt = 0;
                state = JUMP;
            }

            if(state == JUMP){
                if(jump_cnt <= MAX_JUMP_CNT){
                    jump_cnt++;
                    master_worm->MoveJump();
                }
                else {
                    state = FALL;
                }
            }

            master_worm->GetPlayerPosition(x, y, dir);
            master_worm->GetPlayerMovement(xdelta, ydelta);
            map.CheckGradient(x, y, xdelta, ydelta);
            master_worm->SetPlayerMovement(xdelta, ydelta);
            master_worm->PlayerMove();

            master_worm->GetPlayerPosition(x, y, dir);
            if(x != prev_x || y != prev_y) {
                stamina_bar.dec_val(1);
            }

            if(state == FIRE){
                x = missile.get_pos_x();
                y = missile.get_pos_y();
                int delta_x, delta_y;
                missile.get_delta(delta_x, delta_y);

                if (map.CheckCollision(x, y, delta_x, delta_y) || (y >= MAX_MAP_POSY)) {
                    map.DestroyMap(*window, x + delta_x, y + delta_y);
                    map.LoadMapdata(*window, 1);
                    DamagePlayers(x + delta_x, y + delta_y, missile.get_damage(), master_worm);
                    break;
                }
                else{
                    missile.update_missile();
                }
                unsigned int cnt = 0;
                while(cnt != TIME_LIMIT) cnt++;
            }

            if(state == WAIT_POWER){
                power += power_delta;
                if(power_delta >= 0) power_bar.inc_val(power_delta);
                else power_bar.dec_val(-power_delta);

                if(power >= 100) {
                    power = 100;
                    power_delta = -power_delta;
                }
                else if(power <= 0){
                    power = 0;
                    power_delta = -power_delta;
                }
            }

            if(state == WAIT_ANGLE){
                if(player_dir == LEFT){
                    angle -= angle_delta;
                    if(angle <= 90) {
                        angle = 90;
                        angle_delta = -angle_delta;
                    }
                    else if(angle >= 180){
                        angle = 180;
                        angle_delta = -angle_delta;
                    }
                }
                else{
                    angle += angle_delta;
                    if(angle <= 0) {
                        angle = 0;
                        angle_delta = -angle_delta;
                    }
                    else if(angle >= 90){
                        angle = 90;
                        angle_delta = -angle_delta;
                    }
                }
            }

            window->clear();
            map.LoadMapdata(*window, 0);

            master_worm->GetPlayerPosition(x, y, dir);
        
            master_worm->SetHpBarPos(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY - 10);
            master_worm->DrawHpBar(*window);

            stamina_bar.set_pos(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY - 10 - 7);
            stamina_bar.draw_bar(*window);

            if(state == WAIT_POWER){
                if(dir==-1)
                    power_bar.set_pos(x - PLAYER_BASE_POSX - 30, y - PLAYER_BASE_POSY + 40);
                else
                    power_bar.set_pos(x - PLAYER_BASE_POSX - 35, y - PLAYER_BASE_POSY + 40);
                power_bar.draw_bar(*window);
            }

            if(state == WAIT_ANGLE){
                if(dir == LEFT)
                    angle_arrow.set_arrow(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY, angle);
                else
                    angle_arrow.set_arrow(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, y - PLAYER_BASE_POSY, angle);
                angle_arrow.draw_arrow(*window, sf::Color::White);
            }

            if(state == FIRE) missile.draw_missile(*window);


            master_worm->Gravity();
            master_worm->GetPlayerPosition(x, y, dir);
            master_worm->GetPlayerMovement(xdelta, ydelta);
            if (map.CheckCollisionGravity(x, y, xdelta, ydelta)) {
                master_worm->SetPlayerMovement(xdelta, ydelta - 1);
                if(state == FALL) state = MOVE;
            }
            master_worm->PlayerMove();
            master_worm->DrawPlayerPosition(*window);

            for (int i = 0;i < Nteam * Nworm;i++) {
                tmp = worms[i];
                if(tmp == master_worm) continue;

                tmp->Gravity();
                tmp->GetPlayerPosition(x, y, dir);
                tmp->GetPlayerMovement(xdelta, ydelta);
                if (map.CheckCollisionGravity(x, y, xdelta, ydelta)) tmp->SetPlayerMovement(xdelta, ydelta - 1);
                tmp->PlayerMove();
                tmp->DrawPlayerPosition(*window);
                if(!tmp->IsDeath()){
                    tmp->SetHpBarPos(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY - 10);
                    tmp->DrawHpBar(*window);
                }
            }

            window->display();
        }

        worms.erase(worms.begin());
        worms.push_back(master_worm);
        IsEnd();
    }
}