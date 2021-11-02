#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(10000, 10000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
sf::Texture texture1;
texture1.loadFromFile("electricity.jpg");
sf::Sprite background(texture1);
int flag = 0;
int c = 0;
window.draw(background);
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
        
if (0 < event.mouseButton.x && event.mouseButton.x < 100 && event.type == sf::Event::MouseButtonPressed && flag == 0) {
    shape.move(10, 10);
    flag++;
}
if (0 < event.mouseButton.x && event.mouseButton.x < 100 && event.type == sf::Event::MouseButtonReleased && flag == 1) {
    flag--;
}

        window.draw(shape);
        window.display();
    }

    return 0;
}