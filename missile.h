#include <SFML/Graphics.hpp>
#ifndef MISSILE
#define MISSILE

enum fire_shape{
    Arc,
    Bounce
};

class Missile{
    private:
        int fire_mode = Arc;
        float pos_x, pos_y;
        float power, angle, init_x_v, init_y_v, cur_x_v, cur_y_v;

    public:
        void update_missile();
        void set_missile(float pos_x_, float pos_y_, float power_, float angle_, int fire_mode_);
        void draw_missile(sf::RenderWindow &window);
        int get_pos_x();
        int get_pos_y();
};

#endif