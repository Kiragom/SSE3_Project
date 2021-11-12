#include <SFML/Graphics.hpp>
#include "param.h"

class GameMap {
    private:
    sf::Texture background_image;
    sf::RenderTexture rtexture;
    sf::Sprite background;
    sf::Texture tmp;
    sf::Sprite SS;
    char mapdata[MAX_MAP_POSX][MAX_MAP_POSY];

    public:
    void LoadBackgorund(sf::RenderWindow &window);
    void SetMapdata(sf::RenderWindow &window);
    void LoadMapdata(sf::RenderWindow &window, int option);
    void DestroyMap(sf::RenderWindow &window, int x, int y);
};