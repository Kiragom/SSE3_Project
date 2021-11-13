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
            if (y < 400 || x < 400 || x > 1200) mapdata[x][y] = 0;
            else mapdata[x][y] = 1;
            if (y >= 400 && ((6*x + y > 2800)) && x < 400) mapdata[x][y] = 1;
        }
    }

    sf::Vertex vertex;
    sf::Sprite a;
    //a.
    //test_image.loadFromFile("test.jpg");
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

std::vector<int> GameMap::CheckCollision(int x, int y) const {
    std::vector<int> position;

    if (mapdata[x][y] == 0) {
        position.push_back(0);
        return position;
    }
    else {
        position.push_back(1);

        int posy = y;
        while(mapdata[x][posy]) {
            posy++;
            if (posy > MAX_MAP_POSY) break;
        }
        position.push_back(posy);

        return position;
    }
}

int GameMap::CheckGradient(int x, int y, int direction) const {
    int cnt = 0;
    while(cnt < 3) {
        if (mapdata[x][y] == 0) return y;
        cnt++;
        y--;
    }

    return -1;
}