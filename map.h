#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"

#ifndef MAP
#define MAP

class GameMap {
    private:
    sf::Image map_image;
    sf::Texture background_image;
    sf::RenderTexture screen;
    sf::Sprite background;
    sf::Texture screen_image;
    sf::Sprite sprite;
    char mapdata[MAX_MAP_POSX][MAX_MAP_POSY];
    int water_height = 0;
    sf::RectangleShape water;
    sf::Texture water_image;
    
    public:
    void LoadBackgorund(sf::RenderWindow &window);
    void SetMapdata(sf::RenderWindow &window);
    void LoadMapdata(sf::RenderWindow &window, int DELETE);
    
    void InitWater();
    void FillWater(sf::RenderWindow &window);
    void IncWaterHeight(void);
    int  GetWaterHeight(void);

    void DestroyMap(sf::RenderWindow &window, int x, int y, int drange);
    bool CheckCollision(int& x, int& y, int& xdelta, int& ydelta, int vrange);
    bool CheckCollisionGravity(int& x, int& y, int &xdelta, int &ydelta);
    void CheckGradient(int &x, int &y, int& xdelta, int& ydelta);
};

#endif