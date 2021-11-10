#include <SFML/Graphics.hpp>
#include "param.h"

class GamePlayer {
    private:
    sf::Texture player_image;
    sf::Sprite character;
    int posx;
    int posy;

    public:
    void LoadCharacter();
    void SetPlayerPosition(int x, int y);
    void DrawPlayerPosition(sf::RenderWindow &window);
    void test();
};