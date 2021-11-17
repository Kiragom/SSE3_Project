#include <SFML/Graphics.hpp>
#include <cmath>
#include "indicator.h"

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

void Bar::draw_bar(sf::RenderWindow &window, const sf::Color back_color, const sf::Color front_color){
    sf::RectangleShape max_bar;
    sf::RectangleShape cur_bar;

    max_bar.setPosition(sf::Vector2f(pos_x, pos_y));
    max_bar.setSize(sf::Vector2f(bar_width, bar_height));
    max_bar.setFillColor(back_color);

    cur_bar.setPosition(sf::Vector2f(pos_x, pos_y));
    cur_bar.setSize(sf::Vector2f(bar_width * (cur_val / max_val), bar_height));
    cur_bar.setFillColor(front_color);

    window.draw(max_bar);
    window.draw(cur_bar);
}

void Bar::set_pos(float pos_x_, float pos_y_){
    pos_x = pos_x_; pos_y = pos_y_;
}

void Bar::set_size(float bar_width_, float bar_height_){
    bar_width = bar_width_; bar_height = bar_height_;
}

void Arrow::set_arrow(float pos_x_, float pos_y_, float angle_){
    pos_x = pos_x_; pos_y = pos_y_; angle = angle_;
}

void Arrow::rotate_arrow(float angle_){
    angle += angle_;
    if(angle > 180) angle = 180;
    if(angle < 0) angle = 0;
}

void Arrow::draw_arrow(sf::RenderWindow &window, const sf::Color color){
    sf::RectangleShape bar;
    sf::RectangleShape bar1;
    sf::RectangleShape bar2;

    const float PI = 3.1415926535;

    bar.setPosition(sf::Vector2f(pos_x + 50 * cos(((angle) * PI) / 180), pos_y - 50 * sin(((angle) * PI) / 180)));
    bar.setRotation(-angle);
    bar.setSize(sf::Vector2f(80, 5));
    bar.setFillColor(color);

    /*bar1.setPosition(sf::Vector2f(pos_x + 100 * cos(((angle + 0.5) * PI) / 180), pos_y - 100 * sin(((angle + 0.5) * PI) / 180)));
    bar1.setRotation(135 - angle);
    bar1.setSize(sf::Vector2f(30, 5));
    bar1.setFillColor(sf::Color::Black);
    
    bar2.setPosition(sf::Vector2f(pos_x + 100 * cos(((angle + 0.5) * PI) / 180), pos_y - 100 * sin(((angle + 0.5) * PI) / 180)));
    bar2.setRotation(-(135 + angle));
    bar2.setSize(sf::Vector2f(30, 5));
    bar2.setFillColor(sf::Color::Black);*/

    window.draw(bar);
    window.display();
}