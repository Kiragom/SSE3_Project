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
    WAIT
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
    int flag = 0, other = 0, state = WAIT;
    int c = 0;
    const sf::Time show_time = sf::seconds(0.05f);
    GameMap m;
    GamePlayer p;
    m.LoadBackgorund(window);
    m.SetMapdata(window);
    p.LoadCharacter();
    p.SetPlayerPosition(800, 200, 1);

    Key_control key_con;
    Missile missile1;
    Arrow arrow1;
    Bar hp_bar;
    
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

                if(flag == 0) arrow1.set_arrow(800, 400, 0);
                flag = 1;
                //arrow1.draw_arrow(window, sf::Color::White);
                //arrow1.rotate_arrow(10);
                //window.clear();
                
                //missile1.set_missile(window, 0, 400, Arc);
                //missile1.launch_missile(background, window, 100, 45);

                
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {//key_con.get_cur_state() == Pressed_right
                    //window.clear();
                    //m.LoadMapdata(window, 0);
                    p.MoveRight();
                    other = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {//sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveLeft();
            other = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {//sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            //window.clear();
            //m.LoadMapdata(window, 0);
            p.MoveJump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            vector <int> player_pos = p.GetPlayerPosition();
            //printf("player_pos!\n");
            if(state == WAIT){
                 missile1.set_missile(player_pos[0], player_pos[1], 50, 45, Arc);
                 state = FIRE;
            }
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

        if(state == FIRE){
            missile1.update_missile();
            //printf("pos_x : %d pos_y : %d\n", missile1.get_pos_x(), missile1.get_pos_y());
            position = m.CheckCollision(missile1.get_pos_x(), missile1.get_pos_y());
            if (position.at(0) == 1) {
                state = WAIT;
                m.DestroyMap(window, missile1.get_pos_x(), position.at(1));
                m.LoadMapdata(window, 1);
            }
            //sf::sleep(show_time);
        }

        position = p.GetPlayerPosition();
        int change = m.CheckGradient(position.at(0) + 10, position.at(1) + 30, position.at(2));
        if (change == -1) {
            if (position.at(2) == 1) p.SetPlayerPosition(position.at(0) - 1, position.at(1), position.at(2));
            else p.SetPlayerPosition(position.at(0) + 1, position.at(1), position.at(2));
        }
        else p.SetPlayerPosition(position.at(0), change - 29, position.at(2));


        window.clear();
        m.LoadMapdata(window, 0);

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