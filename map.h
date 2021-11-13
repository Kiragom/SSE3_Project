#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"

class GameMap {
    private:
    sf::Texture background_image;
    sf::RenderTexture screen;
    sf::Sprite background;
    sf::Texture screen_image;
    sf::Sprite sprite;
    char mapdata[MAX_MAP_POSX][MAX_MAP_POSY];

    sf::Texture test_image;

    public:
    void LoadBackgorund(sf::RenderWindow &window);
    void SetMapdata(sf::RenderWindow &window);
    void LoadMapdata(sf::RenderWindow &window, int aaaa);
    void DestroyMap(sf::RenderWindow &window, int x, int y);
    std::vector<int> CheckCollision(int x, int y) const;

    friend class GamePlayer;
};