#include "managerLibs.hpp"
#include "connector.hpp"

int main(){
    rha::cGameManager manager(sf::Vector2i(800,600), "Network - Client");
    manager.runGame(); //while - main loop

    return 0;
}
