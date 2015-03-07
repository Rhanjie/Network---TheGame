#include "managerLibs.hpp"
#include "gameManager.hpp"

int main(){
    rha::cGameManager manager(sf::Vector2i(800,600), "Hammerfall"); //todo - only for me, normal is 1024x768
    manager.runApp(); //while - main loop

    return 0;
}
