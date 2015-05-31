#include "managerLibs.hpp"
#include "gameManager.hpp"

int main(){
    srand(time(NULL));

    rha::cGameManager manager(sf::Vector2i(800,600), "Hammerfall"); //todo - global option
    manager.manageApp(); //while - main loop

    return 0;
}
