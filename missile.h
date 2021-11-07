#include <SFML/Graphics.hpp>
#ifndef MISSILE
#define MISSILE

enum missile_state{
    Ready,
    Flight,
    Explosion
};

class Missile{
    private:
        int state = Ready;
        float pos_x, pos_y;
        float power, angle, init_x_v, init_y_v;
        void update_pos(float delta_x, float delta_y);
        void draw_missile(sf::RenderWindow &window);

    public:
        void launch_missile(sf::Sprite background, sf::RenderWindow &window, float power_, float angle_);
        void set_missile(sf::RenderWindow &window, float pos_x_, float pos_y_);
};

#endif