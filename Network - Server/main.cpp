#include "serverManager.hpp"

int main(){
    rha::cServerManager manager(sf::Vector2i(800, 600), "Hammerfall - server");
    manager.runApp(); //while, main loop

    return 0;
}
