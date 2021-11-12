#include "map.h"

void GameMap::LoadBackgorund(sf::RenderWindow &window) {
    background_image.loadFromFile(BACKGROUND_FILE);
    //background = sf::Sprite(background_image);
    background.setTexture(background_image);

    screen.create(1600,800);
    screen.clear();
    screen.draw(background);
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
                screen.draw(&vertex, 1, sf::Points);
            }
        }
    }

    screen.display();
    screen_image = screen.getTexture();
    //sprite = sf::Sprite(screen_image);
    sprite.setTexture(screen_image);
    window.draw(sprite);
}

void GameMap::LoadMapdata(sf::RenderWindow &window, int DELETE) {
    if (DELETE) {
        screen.clear();
        screen.draw(background);

        sf::Vertex vertex;
        for (int x = 0;x <= 1600;x++) {
            for (int y = 0;y <= 800;y++) {
                if (mapdata[x][y]) {
                    vertex.position = sf::Vector2f(x, y);
                    vertex.color = sf::Color::Green;
                    screen.draw(&vertex, 1, sf::Points);
                }
            }
        }

        screen.display();
        screen_image = screen.getTexture();
        //sprite = sf::Sprite(screen_image);
        sprite.setTexture(screen_image);
        window.draw(sprite);
    }

    else window.draw(sprite);
}

void GameMap::DestroyMap(sf::RenderWindow &window, int posx, int posy) {
    int distance;

    for (int x = posx - 40;x <= posx + 40;x++) {
        for (int y = posy - 40;y <= posy + 40;y++) {
            if (x < 0 || x > MAX_MAP_POSX) continue;
            if (y < 0 || y > MAX_MAP_POSY) continue;
            if (!mapdata[x][y]) continue;

            distance = (x - posx)*(x - posx) + (y - posy)*(y - posy);
            if (distance <= 1600) {
                mapdata[x][y] = 0;
            }
        }
    }
}