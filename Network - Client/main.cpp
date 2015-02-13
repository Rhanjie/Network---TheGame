#include "managerLibs.hpp"
#include "connector.hpp"

int main(){
    rha::cGameManager manager(sf::Vector2i(800,600), "Hammerfall");
    manager.runApp(); //while - main loop

    return 0;
}
