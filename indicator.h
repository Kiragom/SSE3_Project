#include <SFML/Graphics.hpp>
#ifndef INDICATOR
#define INDICATOR

class Bar{
    public:
        void dec_val(float damage);
        void inc_val(float heal);
        float get_max_val();
        float get_cur_val();
        void set_max_val(float max_val_);
        void set_cur_val(float cur_val_);
        void draw_bar(sf::RenderWindow &window, const sf::Color back_color, const sf::Color front_color);
        void set_pos(float pos_x_, float pos_y_);
        void set_size(float bar_width_, float bar_height_);

    private:
        float max_val, cur_val, pos_x, pos_y, bar_width, bar_height;
};

#endif