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
        void check_up_key();
        void check_right_key();
        void check_left_key();
        void check_esc_key();
        void check_a_key();
        void check_s_key();
        void check_space_key();

    public:
        int get_cur_key();
};

#endif