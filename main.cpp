#include <SFML/Graphics.hpp>
#include "key_control.h"
#include "missile.h"
#include "indicator.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
    //sf::CircleShape shape(100.f);
    Key_control key_con;
    Missile missile1;
    //shape.setFillColor(sf::Color::Green);
    sf::Texture texture1;
    Bar hp_bar;
    
    texture1.loadFromFile("electricity.jpg");
    sf::Sprite background(texture1);
    int flag = 0;
    int c = 0;
    window.draw(background);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                hp_bar.set_max_val(1000);
                hp_bar.set_cur_val(300);
                hp_bar.set_pos(0, 400);
                hp_bar.set_size(30, 15);
                hp_bar.draw_bar(window, sf::Color::White, sf::Color::Red);

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
                        printf("pressed_up\n");
                        break;
                    case Pressed_right:
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

        window.display();
    }

    return 0;
}