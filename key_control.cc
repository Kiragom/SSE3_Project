#include <SFML/Graphics.hpp>
#include "key_control.h"

bool Key_control::check_up_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        return 1;
    }
    else return 0;
}

bool Key_control::check_right_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        return 1;
    }
    else return 0;
}

bool Key_control::check_left_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        return 1;
    }
    else return 0;
}

bool Key_control::check_esc_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        return 1;
    }
    else return 0;
}

bool Key_control::check_a_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        return 1;
    }
    else return 0;
}

bool Key_control::check_s_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        return 1;
    }
    else return 0;
}

bool Key_control::check_space_key(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        return 1;
    }
    else return 0;
}

int Key_control::get_cur_state(){
    state = Default;

    if(check_up_key() && check_right_key()){
        state = Pressed_up_right;
    }
    else if(check_up_key() && check_left_key()){
        state = Pressed_up_left;
    }
    else if(check_up_key()){
        state = Pressed_up;
    }
    else if(check_right_key()){
        state = Pressed_right;
    }
    else if(check_left_key()){
        state = Pressed_left;
    }
    else if(check_esc_key()){
        state = Pressed_esc;
    }
    else if(check_a_key()){
        state = Pressed_a;
    }
    else if(check_s_key()){
        state = Pressed_s;
    }
    else if(check_space_key()){
        state = Pressed_space;
    }
    else state = Default;

    return state;
}