#include "map.h"

void GameMap::LoadBackgorund(sf::RenderWindow &window) {
    background_image.loadFromFile(BACKGROUND_FILE);
    background = sf::Sprite(background_image);
    window.draw(background);
}

void GameMap::SetMapdata(sf::RenderWindow &window) {
    for (int x = 0;x <= 1600;x++) {
        for (int y = 0;y <= 800;y++) {
            if (y < 400) mapdata[x][y] = 0;
            else mapdata[x][y] = 1;
        }
    }

    sf::Vertex vertex;
    for (int x = 0;x <= 1600;x++) {
        for (int y = 0;y <= 800;y++) {
            if (mapdata[x][y]) {
                vertex.position = sf::Vector2f(x, y);
                vertex.color = sf::Color::Green;
                window.draw(&vertex, 1, sf::Points);
            }
        }
    }
}

void GameMap::LoadMapdata(sf::RenderWindow &window) {
    sf::Vertex vertex;
    for (int x = 0;x <= 1600;x++) {
        for (int y = 0;y <= 800;y++) {
            if (mapdata[x][y]) {
                vertex.position = sf::Vector2f(x, y);
                vertex.color = sf::Color::Green;
                window.draw(&vertex, 1, sf::Points);
            }
        }
    }
}

void GameMap::DestroyMap(sf::RenderWindow &window, int posx, int posy) {
    int distance;
    sf::Vertex vertex;
    sf::CircleShape shape(25);
    shape.setPosition(posx-25, posy-25);
    shape.setTexture(&background_image);
    shape.setTextureRect(sf::IntRect(posx-25, posy-25, posx+25, posy+25));

    for (int x = posx - 50;x < posx + 50;x++) {
        for (int y = posy - 50;y < posy + 50;y++) {
            if (x < 0 || x > MAX_MAP_POSX) continue;
            if (y < 0 || y > MAX_MAP_POSY) continue;
            if (!mapdata[x][y]) continue;

            distance = (x - posx)*(x - posx) + (y - posy)*(y - posy);
            if (distance <= 2500) {
                mapdata[x][y] = 0;
                //vertex.position = sf::Vector2f(x, y);
                //vertex.color = sf::Color::White;
                //window.draw(&vertex, 1, sf::Points);
            }
        }
    }

    window.draw(shape);
}