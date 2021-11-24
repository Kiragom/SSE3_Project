#include "game.h"

int main() {
    Game WORMS(1600, 800);
    WORMS.StartGame();

    while(WORMS.IsOpen()) {
        WORMS.GameLoop();
    }

    return 0;
}