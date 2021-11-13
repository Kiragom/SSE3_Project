#include <SFML/Graphics.hpp>
#include <vector>
#include "param.h"

class GamePlayer {
    private:
    sf::Texture player_alive_image;
    sf::Texture player_death_image;
    sf::Sprite character_alive;
    sf::Sprite character_death;
    int posx;
    int posy;
    int team;
    int death;
    int turn;
    int direction;

    public:
    void LoadCharacter();
    void SetPlayerPosition(int x, int y);
    std::vector<int> GetPlayerPosition();
    void MoveRight();
    void MoveLeft();
    void MoveJump();
    int Gravity();
    void DrawPlayerPosition(sf::RenderWindow &window);
};