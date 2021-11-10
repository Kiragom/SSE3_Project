#include <SFML/Graphics.hpp>
#ifndef MISSILE
#define MISSILE

enum missile_state{
    Ready,
    Flight,
    Explosion
};

enum fire_shape{
    Arc,
    Bounce
};

class Missile{
    private:
        int state = Ready;
        int fire_mode = Arc;
        float pos_x, pos_y;
        float power, angle, init_x_v, init_y_v, cur_x_v, cur_y_v;
        void update_pos(float delta_x, float delta_y);
        void draw_missile(sf::RenderWindow &window);

    public:
        void launch_missile(sf::Sprite background, sf::RenderWindow &window, float power_, float angle_);
        void set_missile(sf::RenderWindow &window, float pos_x_, float pos_y_, int fire_mode_);
};

#endif