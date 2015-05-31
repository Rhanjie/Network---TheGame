#include "serverManager.hpp"

int main(){
    rha::cServerManager manager(sf::Vector2i(1024, 768), "Hammerfall - server");
    manager.manageApp(); //while, main loop

    return 0;
}
