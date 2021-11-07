#include <SFML/Graphics.hpp>
#include <cmath>
#include "missile.h"

#define MAX_DIST 100
#define PI 3.1415926535

void Missile::update_pos(float delta_x, float delta_y){
    pos_x = pos_x + delta_x;
    pos_y = pos_y - delta_y;
}

void Missile::launch_missile(sf::Sprite background, sf::RenderWindow &window, float power_, float angle_){
    sf::Clock clock;
    sf::Clock timer;

    state = Flight;
    float interval = 0, limit = 2;
    const sf::Time ai_time = sf::seconds(0.05f);

    power = power_; angle = angle_;
    init_x_v = MAX_DIST * (power / 100) * cos((angle_ * PI) / 180);
    init_y_v = MAX_DIST * (power / 100) * sin((angle_ * PI) / 180);

    while(1){
        //초단위로 경과시간을 구함
        //밀리초는 asMilliseconds(), 마이크로초의 asMicroseconds()메소드 이용
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
 
        interval += time;
 
        //0.5초 마다 timer 재시작
        if (timer.getElapsedTime() > ai_time){
            timer.restart();
            float delta_x = init_x_v;
            float delta_y = init_y_v - 74 * interval;
            window.clear();
            window.draw(background);
            update_pos(delta_x, delta_y);
            draw_missile(window);
            window.display();
        }

        if(interval > limit) break;
    }

    state = Explosion;
}

void Missile::set_missile(sf::RenderWindow &window, float pos_x_, float pos_y_){
    sf::CircleShape shape(5.0f);
    shape.setFillColor(sf::Color::White);
    state = Ready;
    pos_x = pos_x_; pos_y = pos_y_;

    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    window.draw(shape);
}

void Missile::draw_missile(sf::RenderWindow &window){
    sf::CircleShape shape(5.0f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    window.draw(shape);
}