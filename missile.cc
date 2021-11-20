#include <SFML/Graphics.hpp>
#include <cmath>
#include "missile.h"
#include "param.h"

void Missile::update_missile(void){
    pos_x = pos_x + cur_x_v;
    pos_y = pos_y - cur_y_v;
    cur_y_v -= GRAVITY * 0.1;
}

int Missile::get_pos_x(void){
    return (int)round(pos_x);
}

int Missile::get_pos_y(void){
    return (int)round(pos_y);
}

void Missile::get_delta(int& delta_x, int& delta_y){
    delta_x = (int)round(cur_x_v);
    delta_y = (int)round(cur_y_v);
    delta_y *= -1;
}

void Missile::set_damage(float damage_){
    damage = damage_;
}

float Missile::get_damage(void){
    return damage;
}
/*void Missile::launch_missile(sf::RenderWindow &window, float power_, float angle_){
    sf::Clock clock;
    sf::Clock timer;

    float interval = 0, limit = 4, check_point = 0;
    const sf::Time show_time = sf::seconds(0.05f);

    
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
            draw_missile(window);
            window.display();
            check_point = interval;
        }

        if(interval > limit) break;
    }
}*/

void Missile::set_missile(float pos_x_, float pos_y_, float power_, float angle_, int fire_mode_){
    //sf::CircleShape shape(5.0f);
    //shape.setFillColor(sf::Color::White);
    pos_x = pos_x_; pos_y = pos_y_;
    fire_mode = fire_mode_;
    power = power_; angle = angle_;

    cur_x_v = MAX_DIST * (power / 100) * cos((angle_ * PI) / 180);
    cur_y_v = MAX_DIST * (power / 100) * sin((angle_ * PI) / 180);
    //shape.setPosition(sf::Vector2f(pos_x, pos_y));
    //window.draw(shape);
}

void Missile::draw_missile(sf::RenderWindow &window){
    sf::CircleShape shape(5.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    window.draw(shape);
}