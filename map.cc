#include "map.h"
#include "param.h"
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

void GameMap::DestroyMap(sf::RenderWindow &window, int posx, int posy, int drange) {
    int distance;
    for (int x = posx - drange;x <= posx + drange;x++) {
        for (int y = posy - drange;y <= posy + drange;y++) {
            if (x < 0 || x > MAX_MAP_POSX) continue;
            if (y < 0 || y > MAX_MAP_POSY) continue;
            if (!mapdata[x][y]) continue;

            distance = (x - posx)*(x - posx) + (y - posy)*(y - posy);
            if (distance <= drange*drange) {
                mapdata[x][y] = 0;
            }
        }
    }

    sf::CircleShape c(drange);
    c.setFillColor(sf::Color::Transparent);
    c.setPosition(posx-drange, posy-drange);
    screen.draw(c, sf::BlendNone);
}

void GameMap::InitWater(){
    water_image.loadFromFile(WATER_FILE);
    water.setTexture(&water_image);
}

void GameMap::FillWater(sf::RenderWindow &window){
    water.setPosition(sf::Vector2f(0, MAX_MAP_POSY - water_height));
    water.setSize(sf::Vector2f(MAX_MAP_POSX, water_height));
    window.draw(water);
}

void GameMap::IncWaterHeight(void){
    water_height += WATER_INC;
}

int GameMap::GetWaterHeight(void){
    return water_height;
}

bool GameMap::CheckCollision(int& x, int& y, int &xdelta, int &ydelta, int vrange) {
    bool collision = false, out_of_map = false;
    int startx = x, starty = y;
    int endx = x + xdelta, endy = y + ydelta;
    int unitx = (xdelta < 0) ? -1 : 1;
    int unity = (ydelta < 0) ? -1 : 1;
    float lean, gradient;
    if (startx != endx && starty != endy) lean = (float)(endy - starty) / (float)(endx - startx);

    while(startx != endx || starty != endy) {
        if(startx < 0 || startx > MAX_MAP_POSX || starty < 0 || starty > MAX_MAP_POSY) out_of_map = true;
        if (startx == endx && starty != endy) starty += unity;
        else if (startx != endx && starty == endy) startx += unitx;
        else {
            float gradient = (float)(endy - starty) / (float)(endx - startx);
            if (gradient <= lean) starty += unity;
            else startx += unitx;
        }

        for (int x = startx-vrange;x < startx+vrange;x++) {
            for (int y = starty-vrange;y < starty+vrange;y++) {
                if(x < 0 || x >= MAX_MAP_POSX || y < 0 || y > MAX_MAP_POSY) continue;
                if (mapdata[x][y]) {
                    collision = true;
                    break;
                }
            }
            if (collision) break;
        }
        if (collision) break;
    }
    
    if(!out_of_map){
        xdelta = startx - x;
        ydelta = starty - y;
    }

    return collision;
}

bool GameMap::CheckCollisionGravity(int& x, int& y, int &xdelta, int &ydelta) {
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

        if (mapdata[startx][starty - PLAYER_Y_BOUND]) {
            collision = true;
            break;
        }
    }

    xdelta = startx - x;
    ydelta = starty - y;

    return collision;
}

void GameMap::CheckGradient(int& x, int& y, int& xdelta, int& ydelta) {
    int startx = x, starty = y;
    int endx = x + xdelta, endy = y + ydelta;
    int unitx = (xdelta < 0) ? -1 : 1;
    int unity = (ydelta < 0) ? -1 : 1;
    int cnt, check;

    while(startx != endx) {
        startx += unitx;
        cnt = 0;
        check = -1;

        while(cnt < 2) {
            if (mapdata[startx][endy - cnt] == 0 && mapdata[startx][endy - PLAYER_Y_BOUND - cnt] == 0) {
                check = cnt;
                break;
            }
            else cnt++;
        }

        if (check == -1) {
            startx -= unitx;
            break;
        }
        else endy -= cnt;
    }

    while(endy != y) {
        if (mapdata[startx][endy - PLAYER_BASE_POSY]) endy++;
        else break;
    }

    xdelta = startx - x;
    ydelta = endy - y;
}
