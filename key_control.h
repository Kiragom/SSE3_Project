#include <SFML/Graphics.hpp>
#ifndef KEY_CONTROL
#define KEY_CONTROL

enum pressed_key{
    Default,
    Pressed_up,
    Pressed_right,
    Pressed_left,
    Pressed_esc,
    Pressed_a,
    Pressed_s,
    Pressed_space,
};

class Key_control{
    private:
        int state = Default;
        bool check_up_key();
        bool check_right_key();
        bool check_left_key();
        bool check_esc_key();
        bool check_a_key();
        bool check_s_key();
        bool check_space_key();

    public:
        int get_cur_state();
};

#endif