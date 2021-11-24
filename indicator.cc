#include <SFML/Graphics.hpp>
#include <cmath>
#include "indicator.h"
#include "param.h"

void Bar:: dec_val(float damage){
    cur_val -= damage;
    if(cur_val < 0) cur_val = 0;
}

void Bar:: inc_val(float heal){
    cur_val += heal;
    if(cur_val > max_val) cur_val = max_val;
}

float Bar::get_max_val(){
    return max_val;
}

float Bar::get_cur_val(){
    return cur_val;
}

void Bar::set_max_val(float max_val_){
    max_val = max_val_;
}

void Bar::set_cur_val(float cur_val_){
    cur_val = cur_val_;
}

void Bar::draw_bar(sf::RenderWindow &window){
    sf::RectangleShape max_bar;
    sf::RectangleShape cur_bar;

    max_bar.setPosition(sf::Vector2f(pos_x, pos_y));
    max_bar.setSize(sf::Vector2f(bar_width, bar_height));
    max_bar.setFillColor(sf::Color::White);

    cur_bar.setPosition(sf::Vector2f(pos_x, pos_y));
    cur_bar.setSize(sf::Vector2f(bar_width * (cur_val / max_val), bar_height));
    cur_bar.setFillColor(bar_color);

    window.draw(max_bar);
    window.draw(cur_bar);
}

void Bar::set_pos(float pos_x_, float pos_y_){
    pos_x = pos_x_; pos_y = pos_y_;
}

void Bar::set_size(float bar_width_, float bar_height_){
    bar_width = bar_width_; bar_height = bar_height_;
}

void Bar::set_color(sf::Color bar_color_){
    bar_color = bar_color_;
}

Bar& Bar::operator+=(float rhs){
    if(rhs >= 0) inc_val(rhs);
    else dec_val(-rhs);
    
    return (*this);
}

Bar& Bar::operator--(int){
    dec_val(1);
    return (*this);
}

void Arrow::set_arrow(float pos_x_, float pos_y_, float angle_){
    pos_x = pos_x_; pos_y = pos_y_; angle = angle_;
}

void Arrow::draw_arrow(sf::RenderWindow &window, const sf::Color color){
    sf::RectangleShape bar;

    bar.setPosition(sf::Vector2f(pos_x + ARROW_LEN * cos(((angle) * PI) / 180), pos_y - ARROW_LEN * sin(((angle) * PI) / 180)));
    bar.setRotation(-angle);
    bar.setSize(sf::Vector2f(80, 5));
    bar.setFillColor(color);

    window.draw(bar);
}

void SetAim(int _posx, int _posy);
    void GetAim(int &_posx, int &_posy);
    void DrawAim(sf::RenderWindow &window);

void Aim::SetAim(int _posx, int _posy) {
    posx = _posx;
    posy = _posy;
}

void Aim::GetAim(int &_posx, int &_posy) {
    _posx = posx;
    _posy = posy;
}

void Aim::DrawAim(sf::RenderWindow &window) {
    sf::RectangleShape line1, line2;
    sf::CircleShape circle(2);

    line1.setPosition(posx - 6, posy);
    line1.setSize(sf::Vector2f(13, 1));
    line1.setFillColor(sf::Color::Black);
    line2.setPosition(posx, posy - 6);
    line2.setSize(sf::Vector2f(1, 13));
    line2.setFillColor(sf::Color::Black);
    circle.setPosition(posx - 2, posy - 2);
    circle.setFillColor(sf::Color::Black);

    window.draw(line1);
    window.draw(line2);
    window.draw(circle);
}