#include <SFML/Graphics.hpp>
#include <iostream>

#include "map.h"
#include "player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
//sf::Texture texture1;
//texture1.loadFromFile("electricity.jpg");
//sf::Sprite background(texture1);
int flag = 0, other = 0;
int c = 0;
//window.draw(background);

GameMap m;
GamePlayer p;
m.LoadBackgorund(window);
m.SetMapdata(window);
p.LoadCharacter();
p.SetPlayerPosition(800, 200, 1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
/*if (flag == 0) {
    flag = 1;
    
    //std::cout << "check\n";
}
else {
    if (c == 10) {
        flag = 0;
        background.move(-10, -10);
        c = 0;
    }
    if (c == 5) {
        shape.move(10, 10);
        //c = c + 1;
    }
    else {
        c = c + 1;
        //std::cout << c << "\n";
    }
}*/

        
        
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    //window.clear();
    //m.LoadMapdata(window, 0);
    p.MoveRight();
    other = 1;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    //window.clear();
    //m.LoadMapdata(window, 0);
    p.MoveLeft();
    other = 1;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    //window.clear();
    //m.LoadMapdata(window, 0);
    p.MoveJump();
}

std::vector<int> position = p.GetPlayerPosition();
if (other == 1) {
    int change = m.CheckGradient(position.at(0) + 10, position.at(1) + 30, position.at(2));
    if (change == -1) {
        if (position.at(2) == 1) p.SetPlayerPosition(position.at(0) - 1, position.at(1), position.at(2));
        else p.SetPlayerPosition(position.at(0) + 1, position.at(1), position.at(2));
    }
    else p.SetPlayerPosition(position.at(0), change - 29, position.at(2));
}

position = m.CheckCollision(position.at(0) + 10, position.at(1) + 30);
if (position.at(0) == 0) {
    //window.clear();
    //m.LoadMapdata(window, 0);
    p.Gravity();
}

position = p.GetPlayerPosition();
int change = m.CheckGradient(position.at(0) + 10, position.at(1) + 30, position.at(2));
if (change == -1) {
    if (position.at(2) == 1) p.SetPlayerPosition(position.at(0) - 1, position.at(1), position.at(2));
    else p.SetPlayerPosition(position.at(0) + 1, position.at(1), position.at(2));
}
else p.SetPlayerPosition(position.at(0), change - 29, position.at(2));


 window.clear();
    m.LoadMapdata(window, 0);

if (event.type == sf::Event::MouseButtonPressed && flag == 0) {
    window.clear();
    m.DestroyMap(window, event.mouseButton.x, event.mouseButton.y);
    m.LoadMapdata(window, 1);
    flag++;
}
if (event.type == sf::Event::MouseButtonReleased && flag == 1) {
    flag--;
}


       
        p.DrawPlayerPosition(window);
        window.display();
    }

    return 0;
}