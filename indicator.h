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
        void draw_bar(sf::RenderWindow &window);
        void set_pos(float pos_x_, float pos_y_);
        void set_size(float bar_width_, float bar_height_);
        void set_color(sf::Color bar_color_);
        Bar& operator+= (float rhs);
        Bar& operator--(int);

    private:
        float max_val, cur_val, pos_x, pos_y, bar_width, bar_height;
        sf::Color bar_color;
};

class Arrow{
    public:
        void set_arrow(float pos_x_, float pos_y_, float angle_);
        void draw_arrow(sf::RenderWindow &window, const sf::Color color);

    private:
        float pos_x, pos_y, angle;
};

class Aim {
    public:
    void SetAim(int _posx, int _posy);
    void GetAim(int &_posx, int &_posy);
    void DrawAim(sf::RenderWindow &window);

    private:
    int posx, posy;
};

#endif