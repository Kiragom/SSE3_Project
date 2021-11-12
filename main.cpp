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
int flag = 0;
int c = 0;
//window.draw(background);

GameMap m;
GamePlayer p;
m.LoadBackgorund(window);
m.SetMapdata(window);
p.LoadCharacter();
p.SetPlayerPosition(800, 400);

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

        
        
if (event.type == sf::Event::KeyPressed && flag == 0) {
    window.clear();
    //m.LoadBackgorund(window);
    m.LoadMapdata(window, 0);
    p.test();
    flag++;
}
if (event.type == sf::Event::KeyReleased && flag == 1) {
    flag--;
}

if (event.type == sf::Event::MouseButtonPressed && flag == 0) {
    window.clear();
    //m.LoadBackgorund(window);
    m.DestroyMap()
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