#include <SFML/Graphics.hpp>
#include "key_control.h"
#include "missile.h"
#include "indicator.h"
#include <iostream>
#include <vector>

#include "map.h"
#include "player.h"

using namespace std;

enum cur_state{
    FIRE,
    MOVE,
    WAIT_POWER,
    WAIT_ANGLE,
    STOP,
    JUMP,
    FALL
};

enum dir{
    LEFT,
    RIGHT
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
    int flag = 0, other = 0, state = MOVE, jump_cnt = 0;
    int c = 0, player_dir = LEFT, prev_x, prev_y;
    float power_delta = 1.5, angle_delta = 1.5, power = 0, angle = 0;
    const sf::Time show_time = sf::seconds(0.05f);
    GameMap m;
    GamePlayer p;
    m.LoadBackgorund(window);
    m.SetMapdata(window);
    p.LoadCharacter();
    p.SetPlayerPosition(800, 500, -1);
    Bar hp_bar1, power_bar, stamina_bar1;
    Key_control key_con;
    Missile missile1;
    Arrow fire_dir;
    
    hp_bar1.set_size(30, 5);
    hp_bar1.set_cur_val(100);
    hp_bar1.set_max_val(100);

    power_bar.set_size(100, 15);
    power_bar.set_cur_val(0);
    power_bar.set_max_val(100);

    stamina_bar1.set_size(30, 5);
    stamina_bar1.set_cur_val(MAX_STAMINA);
    stamina_bar1.set_max_val(MAX_STAMINA);

    int x, y, dir, xdelta, ydelta;
    std::vector<int> position;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    p.GetPlayerPosition(x, y, dir);
                    //printf("%d\n", y);
                    if(state == WAIT_ANGLE){
                        if(dir==-1)
                            missile1.set_missile(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY, power, angle, Arc);
                        else
                            missile1.set_missile(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, y - PLAYER_BASE_POSY, power, angle, Arc);
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
                        p.GetPlayerPosition(x, y, dir);
                        state = WAIT_ANGLE;

                        if(dir == -1) {
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

        p.GetPlayerPosition(x, y, dir);
        prev_x = x; prev_y = y;

        if(stamina_bar1.get_cur_val() == 0){
            if(state == MOVE){
                state = STOP;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dir = 1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                dir = -1;
            }
            p.SetPlayerPosition(x, y, dir);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (state == MOVE || state == JUMP || state == FALL)) {
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveRight();
            other = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (state == MOVE || state == JUMP || state == FALL)) {
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveLeft();
            other = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && state == MOVE) {
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveJump();
            jump_cnt = 0;
            state = JUMP;
        }

        if(state == JUMP){
            if(jump_cnt <= MAX_JUMP_CNT){
                jump_cnt++;
                p.MoveJump();
            }
            else {
                state = FALL;
            }
        }

        p.GetPlayerPosition(x, y, dir);
        p.GetPlayerMovement(xdelta, ydelta);
        m.CheckGradient(x, y, xdelta, ydelta);
        p.SetPlayerMovement(xdelta, ydelta);
        p.PlayerMove();

        p.GetPlayerPosition(x, y, dir);
        if(x != prev_x || y != prev_y) {
            stamina_bar1.dec_val(1);
            printf("stamina : %lf\n", stamina_bar1.get_cur_val());
        }
        /*if(state == FIRE){
            missile1.update_missile();
            position = m.CheckCollision(missile1.get_pos_x(), missile1.get_pos_y());
            if (position.at(0) == 1) {
                state = WAIT;
                m.DestroyMap(window, missile1.get_pos_x(), position.at(1));*/

            
        if(state == FIRE){
            //printf("pos_x : %d pos_y : %d\n", missile1.get_pos_x(), missile1.get_pos_y());
            x = missile1.get_pos_x();
            y = missile1.get_pos_y();
            int delta_x, delta_y;
            missile1.get_delta(delta_x, delta_y);

            if (m.CheckCollision(x, y, delta_x, delta_y) || ((x < 0 || x >= MAX_MAP_POSX) && (y <0 || y >= MAX_MAP_POSY))) {
                state = MOVE;
                m.DestroyMap(window, x + delta_x, y + delta_y);
                m.LoadMapdata(window, 1);
            }
            else{
                missile1.update_missile();
            }
            unsigned int cnt = 0;
            while(cnt != TIME_LIMIT) cnt++;
            //sf::sleep(show_time);
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

        window.clear();
        m.LoadMapdata(window, 0);
        p.GetPlayerPosition(x, y, dir);
        
        hp_bar1.set_pos(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY - 10);
        hp_bar1.draw_bar(window, sf::Color::White, sf::Color::Red);

        stamina_bar1.set_pos(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY - 10 - 5);
        stamina_bar1.draw_bar(window, sf::Color::White, sf::Color::Green);

        if(state == WAIT_POWER){
            if(dir==-1)
                power_bar.set_pos(x - PLAYER_BASE_POSX - 30, y - PLAYER_BASE_POSY + 40);
            else
                power_bar.set_pos(x - PLAYER_BASE_POSX - 35, y - PLAYER_BASE_POSY + 40);
            power_bar.draw_bar(window, sf::Color::White, sf::Color::Black);
        }

        if(state == WAIT_ANGLE){
            if(dir==-1)
                fire_dir.set_arrow(x - PLAYER_BASE_POSX, y - PLAYER_BASE_POSY, angle);
            else
                fire_dir.set_arrow(x - PLAYER_BASE_POSX + PLAYER_BASE_DIR, y - PLAYER_BASE_POSY, angle);
            fire_dir.draw_arrow(window, sf::Color::White);
        }

        if (event.type == sf::Event::MouseButtonPressed && flag == 0) {
            window.clear();
            m.DestroyMap(window, event.mouseButton.x, event.mouseButton.y);
            m.LoadMapdata(window, 1);
            flag++;
        }
        if (event.type == sf::Event::MouseButtonReleased && flag == 1) {
            flag--;
        }

        if(state == FIRE) missile1.draw_missile(window);


        p.Gravity();
        p.GetPlayerPosition(x, y, dir);
        p.GetPlayerMovement(xdelta, ydelta);
        if (m.CheckCollisionGravity(x, y, xdelta, ydelta)) {
            p.SetPlayerMovement(xdelta, ydelta - 1);
            if(state == FALL) state = MOVE;
        }
        p.PlayerMove();
        p.DrawPlayerPosition(window);
        window.display();
    }

    return 0;
}

#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    Game WORMS(1600, 800);
    WORMS.StartGame();

    while(WORMS.IsOpen()) {
        WORMS.GameLoop();
    }

    return 0;
}