#include "map.h"
#include <cstdlib>
#include <fstream>

void GameMap::LoadBackgorund(sf::RenderWindow &window) {
    background_image.loadFromFile(BACKGROUND_FILE);
    background.setTexture(background_image);
    map_image.loadFromFile("test.jpg");

    screen.create(1600, 800);
    screen.clear();
    screen.draw(background);
}

void GameMap::SetMapdata(sf::RenderWindow &window) {
    int data;
    std::ifstream fin;
    fin.open("map1.txt");

    for (int x = 0;x <= 1600;x++) {
        for (int y = 0;y <= 800;y++) {
            fin >> data;
            mapdata[x][y] = data;
        }
    }
    fin.close();

    sf::Vertex vertex;
    for (int x = 0;x <= 1600;x++) {
        for (int y = 0;y <= 800;y++) {
            if (mapdata[x][y]) {
                vertex.position = sf::Vector2f(x, y);
                vertex.color = map_image.getPixel(x, y);
                screen.draw(&vertex, 1, sf::Points, sf::BlendNone);
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
        screen.display();
        screen_image = screen.getTexture();
        sprite.setTexture(screen_image);
        window.draw(sprite);
    }

    else {
        window.draw(background);
        window.draw(sprite);
    }
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

    sf::CircleShape c(40);
    c.setFillColor(sf::Color::Transparent);
    c.setPosition(posx-40, posy-40);
    screen.draw(c, sf::BlendNone);
}

bool GameMap::CheckCollision(int& x, int& y, int &xdelta, int &ydelta) {
    bool collision = false;
    int startx = x, starty = y;
    int endx = x + xdelta, endy = y + ydelta;
    int unitx = (xdelta < 0) ? -1 : 1;
    int unity = (ydelta < 0) ? -1 : 1;
    float lean, gradient;
    if (startx != endx && starty != endy) lean = (float)(endy - starty) / (float)(endx - startx);

    while(startx != endx || starty != endy) {
        if (startx == endx && starty != endy) starty += unity;
        else if (startx != endx && starty == endy) startx += unitx;
        else {
            float gradient = (float)(endy - starty) / (float)(endx - startx);
            if (gradient <= lean) starty += unity;
            else startx += unitx;
        }

        if (mapdata[startx][starty]) {
            collision = true;
            break;
        }
    }

    xdelta = startx - x;
    ydelta = starty - y;

    return collision;

    /*if (mapdata[x][y] == 0) {
        position.push_back(0);
        return position;
    }
    else {
        position.push_back(1);

        int posy = y;
        while(mapdata[x][posy]) {
            posy--;
            if (posy <= 0) break;
        }
        position.push_back(posy);

        return position;
    }*/
}

void GameMap::CheckGradient(int& x, int& y, int& xdelta, int& ydelta) {
    if (ydelta == 0) return;
    if (xdelta == 0) return;

    int startx = x, starty = y;
    int endx = x + xdelta;
    int unitx = (xdelta < 0) ? -1 : 1;
    int cnt, check;

    while(startx != endx) {
        startx += unitx;
        cnt = 0;
        check = -1;

        while(cnt < 2) {
            if (mapdata[startx][starty + cnt] == 0) {
                check = cnt;
                break;
            }
            cnt++;
        }

        if (check == -1) {
            startx -= unitx;
            break;
        }
        else starty += cnt;
    }

    xdelta = startx - x;
    ydelta = starty - y;



    /*int cnt = 0;
    while(cnt < 3) {
        if (mapdata[x][y] == 0) return y;
        cnt++;
        y--;
    }*/
}