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
};

enum dir{
    LEFT,
    RIGHT
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
    int flag = 0, other = 0, state = MOVE;
    int c = 0, player_dir = LEFT;
    float power_delta = 5, angle_delta = 3, power = 0, angle = 0;
    const sf::Time show_time = sf::seconds(0.05f);
    GameMap m;
    GamePlayer p;
    m.LoadBackgorund(window);
    m.SetMapdata(window);
    p.LoadCharacter();
    p.SetPlayerPosition(800, 200, 1);
    Bar hp_bar1;
    Bar power_bar;
    Key_control key_con;
    Missile missile1;
    Arrow fire_dir;
    
    hp_bar1.set_size(30, 5);
    hp_bar1.set_cur_val(60);
    hp_bar1.set_max_val(100);

    power_bar.set_size(100, 30);
    power_bar.set_cur_val(0);
    power_bar.set_max_val(100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                /*hp_bar.set_max_val(1000);
                hp_bar.set_cur_val(300);
                hp_bar.set_pos(800, 400);
                hp_bar.set_size(30, 15);
                hp_bar.draw_bar(window, sf::Color::White, sf::Color::Red);*/
                //arrow1.draw_arrow(window, sf::Color::White);
                //arrow1.rotate_arrow(10);
                //window.clear();
                
                //missile1.set_missile(window, 0, 400, Arc);
                //missile1.launch_missile(background, window, 100, 45);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    vector <int> player_pos = p.GetPlayerPosition();
                    //printf("player_pos!\n");
                    if(state == WAIT_ANGLE){
                        missile1.set_missile(player_pos[0], player_pos[1], power, angle, Arc);
                        state = FIRE;
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    if(state == MOVE) {
                        state = WAIT_POWER;

                        power = 0;
                    }
                    else if(state == WAIT_POWER) {
                        vector <int> player_pos = p.GetPlayerPosition();
                        state = WAIT_ANGLE;

                        if(player_pos[2] == -1) {
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && state == MOVE) {//key_con.get_cur_state() == Pressed_right
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveRight();
            other = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && state == MOVE) {//sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveLeft();
            other = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && state == MOVE) {//sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveJump();
        }
        

        std::vector<int> position = p.GetPlayerPosition();
        if (other == 1) {
            int change = m.CheckGradient(position.at(0) + 10, position.at(1) + 30, position.at(2));
            if (change == -1) {
                if (position.at(2) == 1) p.SetPlayerPosition(position.at(0) - 1, position.at(1), position.at(2));
                else p.SetPlayerPosition(position.at(0) + 1, position.at(1), position.at(2));
            }
            else p.SetPlayerPosition(position.at(0), change - 29, position.at(2));
        }

        position = m.CheckCollision(position.at(0) + 10, position.at(1) + 30);
        if (position.at(0) == 0) {
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.Gravity();
        }

        position = p.GetPlayerPosition();
        int change = m.CheckGradient(position.at(0) + 10, position.at(1) + 30, position.at(2));
        if (change == -1) {
            if (position.at(2) == 1) p.SetPlayerPosition(position.at(0) - 1, position.at(1), position.at(2));
            else p.SetPlayerPosition(position.at(0) + 1, position.at(1), position.at(2));
        }
        else p.SetPlayerPosition(position.at(0), change - 29, position.at(2));

        if(state == FIRE){
            missile1.update_missile();
            //printf("pos_x : %d pos_y : %d\n", missile1.get_pos_x(), missile1.get_pos_y());
            position = m.CheckCollision(missile1.get_pos_x(), missile1.get_pos_y());
            if (position.at(0) == 1) {
                state = MOVE;
                m.DestroyMap(window, missile1.get_pos_x(), position.at(1));
                m.LoadMapdata(window, 1);
            }
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
        position = p.GetPlayerPosition();

        hp_bar1.set_pos(position.at(0), position.at(1) - 20);
        hp_bar1.draw_bar(window, sf::Color::White, sf::Color::Red);

        if(state == WAIT_POWER){
            power_bar.set_pos(700, 450);
            power_bar.draw_bar(window, sf::Color::White, sf::Color::Black);
        }

        if(state == WAIT_ANGLE){
            fire_dir.set_arrow(position.at(0), position.at(1) + 20, angle);
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
    
        p.DrawPlayerPosition(window);
        window.display();
        //sf::sleep(show_time);
    }

    return 0;
}