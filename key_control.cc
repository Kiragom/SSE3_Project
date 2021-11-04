#include <SFML/Graphics.hpp>
#include "key_control.h"

void Key_control::check_up_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        state = Pressed_up;
    }
}

void Key_control::check_right_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        state = Pressed_right;
    }
}

void Key_control::check_left_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        state = Pressed_left;
    }
}

void Key_control::check_esc_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        state = Pressed_esc;
    }
}

void Key_control::check_a_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        state = Pressed_a;
    }
}

void Key_control::check_s_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        state = Pressed_s;
    }
}

void Key_control::check_space_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        state = Pressed_space;
    }
}

int Key_control::get_cur_key(){
    state = Default;

    check_up_key();
    check_right_key();
    check_left_key();
    check_esc_key();
    check_a_key();
    check_s_key();
    check_space_key();

    return state;
}