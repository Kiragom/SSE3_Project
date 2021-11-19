#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"

class GameMap {
    private:
    sf::Image map_image;
    sf::Texture background_image;
    sf::RenderTexture screen;
    sf::Sprite background;
    sf::Texture screen_image;
    sf::Sprite sprite;
    char mapdata[MAX_MAP_POSX][MAX_MAP_POSY];

    public:
    void LoadBackgorund(sf::RenderWindow &window);
    void SetMapdata(sf::RenderWindow &window);
    void LoadMapdata(sf::RenderWindow &window, int aaaa);
    void DestroyMap(sf::RenderWindow &window, int x, int y);
    bool CheckCollision(int& x, int& y, int& xdelta, int& ydelta);
    bool CheckCollisionP(int& x, int& y, int &xdelta, int &ydelta);
    void CheckGradient(int &x, int &y, int& xdelta, int& ydelta);

    friend class GamePlayer;
};