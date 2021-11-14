#include <SFML/Graphics.hpp>
#include "key_control.h"
#include "missile.h"
#include "indicator.h"
#include <iostream>

#include "map.h"
#include "player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
int flag = 0, other = 0;
int c = 0;

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

                switch(key_con.get_cur_state()){
                    case Pressed_up_right:
                        printf("pressed_up_right\n");
                        break;
                    case Pressed_up_left:
                        printf("pressed_up_left\n");
                        break;
                    case Pressed_up:
                        arrow1.rotate_arrow(5);
                        arrow1.draw_arrow(window, sf::Color::White);
                        printf("pressed_up\n");
                        break;
                    case Pressed_right:
                    arrow1.rotate_arrow(-5);
                        arrow1.draw_arrow(window, sf::Color::White);
                        printf("pressed_right\n");
                        break;
                    case Pressed_left:
                        printf("pressed_left\n");
                        break;
                    case Pressed_esc:
                        printf("pressed_esc\n");
                        break;
                    case Pressed_a:
                        printf("pressed_a\n");
                        break;
                    case Pressed_s:
                        printf("pressed_s\n");
                        break;
                    case Pressed_space:
                        printf("pressed_space\n");
                        break;
                }
            }
        }
/*if (flag == 0) {
    flag = 1;
    
    //std::cout << "check\n";
}
else {
    if (c == 10) {
        flag = 0;
        background.move(-10, -10);
        c = 0;
    }
    if (c == 5) {
        shape.move(10, 10);
        //c = c + 1;
    }
    else {
        c = c + 1;
        //std::cout << c << "\n";
    }
}*/

        
        
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    //window.clear();
    //m.LoadMapdata(window, 0);
    p.MoveRight();
    other = 1;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    //window.clear();
    //m.LoadMapdata(window, 0);
    p.MoveLeft();
    other = 1;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
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


       
        p.DrawPlayerPosition(window);
        window.display();
    }

    return 0;
}