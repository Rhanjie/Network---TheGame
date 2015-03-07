#include "serverManager.hpp"

int main(){
    rha::cServerManager manager(sf::Vector2i(1024, 768), "Hammerfall - server"); //800x600
    manager.runApp(); //while, main loop

    return 0;
}
