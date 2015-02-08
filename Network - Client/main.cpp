#include "managerLibs.hpp"
#include "helper.hpp" //todo

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Network - Client", sf::Style::Close);

    sf::Event event;
    while(window.isOpen()){
        rha::checkEvent(&window, &event);


        window.clear();
        //...

        window.display();
    }
    return 0;
}
