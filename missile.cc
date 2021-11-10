#include <SFML/Graphics.hpp>
#include <cmath>
#include "missile.h"

#define MAX_DIST 100
#define PI 3.1415926535
#define GRAVITY 74

void Missile::update_pos(float delta_x, float delta_y){
    pos_x = pos_x + delta_x;
    pos_y = pos_y - delta_y;
}

void Missile::launch_missile(sf::Sprite background, sf::RenderWindow &window, float power_, float angle_){
    sf::Clock clock;
    sf::Clock timer;

    state = Flight;
    float interval = 0, limit = 4, check_point = 0;
    const sf::Time show_time = sf::seconds(0.1f);

    power = power_; angle = angle_;
    cur_x_v = MAX_DIST * (power / 100) * cos((angle_ * PI) / 180);
    cur_y_v = MAX_DIST * (power / 100) * sin((angle_ * PI) / 180);
    while(1){
        //초단위로 경과시간을 구함
        //밀리초는 asMilliseconds(), 마이크로초의 asMicroseconds()메소드 이용
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
 
        interval += time;
 
        //0.5초 마다 timer 재시작
        if (timer.getElapsedTime() > show_time){
            timer.restart();
            if(fire_mode == Arc){
                cur_y_v -= GRAVITY * (interval - check_point);
            }
            else{
                if((pos_x < 0 && pos_y >= 0) || (pos_x >= 1600 && pos_y >= 0)){
                    cur_x_v = -cur_x_v;
                }
                else if((pos_x >= 0 && pos_y < 0) || (pos_x >= 0 && pos_y >= 800)){
                    cur_y_v = -cur_y_v;
                }
            }
            window.clear();
            window.draw(background);
            update_pos(cur_x_v, cur_y_v);
            draw_missile(window);
            window.display();
            check_point = interval;
        }

        if(interval > limit) break;
    }

    state = Explosion;
}

void Missile::set_missile(sf::RenderWindow &window, float pos_x_, float pos_y_, int fire_mode_){
    sf::CircleShape shape(5.0f);
    shape.setFillColor(sf::Color::White);
    state = Ready;
    pos_x = pos_x_; pos_y = pos_y_;
    fire_mode = fire_mode_;

    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    window.draw(shape);
}

void Missile::draw_missile(sf::RenderWindow &window){
    sf::CircleShape shape(5.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    window.draw(shape);
}