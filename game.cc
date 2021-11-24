#include "game.h"
#include "param.h"

Game::Game(int _xlength, int _ylength) {
    xlength = _xlength;
    ylength = _ylength;
    window = new sf::RenderWindow(sf::VideoMode(xlength, ylength), "WORMS SHOOTING GAME");
}

Game::~Game(void) {
    delete window;
    for(int i=0; i<Nteam*Nworm; i++){
        delete worms[i];
    }
}

void Game::Display() {
    window->display();
}

void Game::StartGame() {
    Nteam = NTEAM;
    Nworm = NWORM;

    sf::Color color_list[4] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};

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
            worm->SetHpBarColor(color_list[team_id_shuffle[j]]);
            worms.push_back(worm);
        }
    }

    map.LoadBackgorund(*window);
    map.SetMapdata(*window);
    map.InitWater();

    power_bar.set_size(100, 15);
    power_bar.set_cur_val(0);
    power_bar.set_max_val(100);
    power_bar.set_color(sf::Color::Cyan);

    stamina_bar.set_size(30, 5);
    stamina_bar.set_cur_val(MAX_STAMINA);
    stamina_bar.set_max_val(MAX_STAMINA);
    stamina_bar.set_color(sf::Color::Yellow);

    sniper.SetObject();

    FLAG_END = NOT_END;
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
        if(dis <= 14400){ //////////////////////////////////
            float total_damage = MIN_DAMAGE + (((float)dis / 14400) * damage);
            printf("total damage : %lf\n", total_damage);
            worms[i]->GetDamage(total_damage);
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

    int cnt = 0, winner_team;
    for (int i = 0;i < Nteam;i++) {
        if (alive_team[i]) {
            cnt++;
            winner_team = i;
        }
    }

    if (cnt == 1) FLAG_END = winner_team;
    else if(cnt == 0) FLAG_END = DRAW;
}

void Game::CheckWaterDeath(){
    for(int i=0; i<Nteam * Nworm; i++){
        GamePlayer * tmp = worms[i];
        int x, y, dir;
        tmp->GetPlayerPosition(x, y, dir);
        if(y > MAX_MAP_POSY - map.GetWaterHeight())
            tmp->GetDamage(MAX_HP);
    }
    IsEnd();
    if (FLAG_END != -1) {
        EndGame();
    }
}

void Game::GameLoop() {
    if (FLAG_END != NOT_END) {
        EndGame();
    }

    else {
        GamePlayer *master_worm = worms.at(0);
        GamePlayer *tmp;
        Missile missile;
        int x, y, prev_x, prev_y, dir, xdelta, ydelta, player_dir = LEFT, jump_cnt = 0;
        int state = FALL;
        bool initial_fall = true;
        float power_delta = POWER_DELTA, angle_delta = ANGLE_DELTA, power = 0, angle = 0;
        float turn_timer = 0;
        sf::Clock clock;

        if(turn_cnt > Nworm * 3){
            map.IncWaterHeight();
            CheckWaterDeath();
        }
        
        stamina_bar.set_cur_val(MAX_STAMINA);
        power_bar.set_cur_val(0);
        missile.SetDamage(MISSILE_DAMAGE);
        sniper.SetDamage(MISSILE_DAMAGE); //////////////////////////

        if(master_worm->IsDeath()){
            worms.erase(worms.begin());
            worms.push_back(master_worm);
            return;
        }

        while(window->isOpen()) {
            sf::Event event;

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();

            if(state != FIRE) turn_timer += time;

            if((!initial_fall) && (turn_timer >= TURN_LIMIT)) break;
            if(master_worm->IsDeath()) break;

            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window->close();
                }

                if (event.type == sf::Event::KeyPressed){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        master_worm->GetPlayerPosition(x, y, dir);
                        if(state == WAIT_ANGLE){
                            if(dir==LEFT) sniper.SetWeapon(x - PLAYER_BASE_POSX, -500, power, angle, 0, 40, 120);
                                //missile.SetWeapon(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY, power, angle, 0);
                            else sniper.SetWeapon(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, -500, power, angle, 0, 40, 120);
                                //missile.SetWeapon(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, y - PLAYER_BASE_POSY, power, angle, 0);
                            sniper.SetMovement();
                            //missile.SetMovement();
                            state = FIRE;
                            break;
                        }
                        else if (state == WAIT_POINT) {
                            int aim_x, aim_y;
                            aim.GetAim(aim_x, aim_y);
                            if(dir==LEFT) sniper.SetWeapon(aim_x - PLAYER_BASE_POSX, -500, power, angle, 0, 40, 120);
                                //missile.SetWeapon(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY, power, angle, 0);
                            else sniper.SetWeapon(aim_x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, -500, power, angle, 0, 40, 120);
                                //missile.SetWeapon(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, y - PLAYER_BASE_POSY, power, angle, 0);
                            sniper.SetMovement();
                            //missile.SetMovement();
                            state = FIRE;
                            break;
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        if(state == MOVE || state == STOP) {
                            state = WAIT_POINT;
                            master_worm->GetPlayerPosition(x, y, dir);
                            aim.SetAim(x, y);
                            //state = WAIT_POWER;
                            power_bar.set_cur_val(0);
                            power = 0;
                            break;
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

                            break;
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }
            }

            master_worm->GetPlayerPosition(x, y, dir);
            prev_x = x; prev_y = y;

            if(stamina_bar.get_cur_val() == 0){
                if(state == MOVE || state == FALL){
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
                stamina_bar--;
            }

            if(state == FIRE){
                x = sniper.GetPosX();
                y = sniper.GetPosY(); y += SNIPER_Y_TRANS;
                //x = missile.GetPosX();
                //y = missile.GetPosY();
                int delta_x, delta_y;
                sniper.GetDelta(delta_x, delta_y);
                delta_y *= -1;
                //missile.GetDelta(delta_x, delta_y);

                if (map.CheckCollision(x, y, delta_x, delta_y, sniper.GetValidRange()) || (y >= MAX_MAP_POSY)) {
                    map.DestroyMap(*window, x + delta_x, y + delta_y, sniper.GetDestroyRange());
                    //map.DestroyMap(*window, x + delta_x, y + delta_y);
                    map.LoadMapdata(*window, 1);
                    DamagePlayers(x + delta_x, y + delta_y, sniper.GetDamage(), master_worm);
                    //DamagePlayers(x + delta_x, y + delta_y, missile.GetDamage(), master_worm);
                    break;
                }
                else{
                    sniper.UpdateMovement();
                    //missile.UpdateMovement();
                }
                unsigned int cnt = 0;
                while(cnt != TIME_LIMIT) cnt++;
            }

            if(state == WAIT_POWER){
                power += power_delta;
                power_bar += power_delta;

                if(power >= 100) {
                    power = 100;
                    power_delta = -power_delta;
                }
                else if(power <= 0){
                    power = 0;
                    power_delta = -power_delta;
                }
            }

            if (state == WAIT_POINT) {
                int aim_x, aim_y;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    aim.GetAim(aim_x, aim_y);
                    aim.SetAim(aim_x - 5, aim_y);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    aim.GetAim(aim_x, aim_y);
                    aim.SetAim(aim_x + 5, aim_y);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    aim.GetAim(aim_x, aim_y);
                    aim.SetAim(aim_x, aim_y - 5);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    aim.GetAim(aim_x, aim_y);
                    aim.SetAim(aim_x, aim_y + 5);
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
            map.FillWater(*window);
            master_worm->GetPlayerPosition(x, y, dir);
            sf::Text text;
            sf::Font font;
            sf::Vector2f pos;
            std::string remain_time = std::to_string((TURN_LIMIT - (int)turn_timer));

            // select the font
            font.loadFromFile(FONT_FILE);
            text.setFont(font); // font is a sf::Font
            text.setPosition(x - PLAYER_BASE_POSX, y);
            // set the string to display
            text.setString(remain_time);

            // set the character size
            text.setCharacterSize(30); // in pixels, not points!

            // set the color
            text.setFillColor(sf::Color::Black);

            // set the text style
            text.setStyle(sf::Text::Bold);
            if(!initial_fall) window->draw(text);

    
            master_worm->SetHpBarPos(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY - 10);
            master_worm->DrawHpBar(*window);

            stamina_bar.set_pos(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY - 10 - 7);
            stamina_bar.draw_bar(*window);

            if(state == WAIT_POWER){
                if(dir == LEFT)
                    power_bar.set_pos(x - PLAYER_BASE_POSX - 30, y - PLAYER_BASE_POSY + 40);
                else
                    power_bar.set_pos(x - PLAYER_BASE_POSX - 35, y - PLAYER_BASE_POSY + 40);
                power_bar.draw_bar(*window);
            }

            if (state == WAIT_POINT) aim.DrawAim(*window);

            if(state == WAIT_ANGLE){
                if(dir == LEFT)
                    angle_arrow.set_arrow(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY, angle);
                else
                    angle_arrow.set_arrow(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, y - PLAYER_BASE_POSY, angle);
                angle_arrow.draw_arrow(*window, sf::Color::White);
            }

            //if(state == FIRE) missile.DrawWeaponMovement(*window);
            if(state == FIRE) sniper.DrawWeaponMovement(*window);

            master_worm->Gravity();
            master_worm->GetPlayerPosition(x, y, dir);
            master_worm->GetPlayerMovement(xdelta, ydelta);
            if (map.CheckCollisionGravity(x, y, xdelta, ydelta)) {
                master_worm->SetPlayerMovement(xdelta, ydelta - 1);
                if(state == FALL) state = MOVE;
                if(initial_fall){
                    initial_fall = false;
                    turn_timer = 0;
                }
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

            CheckWaterDeath();
            window->display();
        }

        turn_cnt++;
        worms.erase(worms.begin());
        worms.push_back(master_worm);
        IsEnd();
    }
}

void Game::EndGame() {
    sf::Text text, winner;
    sf::Font font;
    sf::Vector2f pos;

    font.loadFromFile(FONT_FILE); // select the font
    text.setFont(font); // font is a sf::Font
    text.setPosition(630, 210); // set the string to display
    text.setString("Game Over");
    text.setCharacterSize(70); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    winner.setFont(font);
    winner.setPosition(390, 400);
    switch(FLAG_END) {
        case RED_WIN: {
            winner.setString("Red Team Win!");
            winner.setFillColor(sf::Color::Red);
        } break;
        case BLUE_WIN: {
            winner.setString("Blue Team Win!");
            winner.setFillColor(sf::Color::Blue);
        } break;
        case GREEN_WIN: {
            winner.setString("Green Team Win!");
            winner.setFillColor(sf::Color::Green);
        } break;
        case YELLOW_WIN: {
            winner.setString("Yellow Team Win!");
            winner.setFillColor(sf::Color::Yellow);
        }
        case DRAW: {
            winner.setPosition(660, 400);
            winner.setString("Draw!");
            winner.setFillColor(sf::Color::White);
        }
    }
    winner.setCharacterSize(120);
    winner.setStyle(sf::Text::Bold);

    while(window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }
        }

        window->clear();  
        window->draw(text);
        window->draw(winner);

        window->display();
    }
}