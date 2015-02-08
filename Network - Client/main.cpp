#include "managerLibs.hpp"
#include "connector.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Network - Client", sf::Style::Close);

    rha::cServerInfo server;
    server.setData("localhost", 7405);

    rha::cClient client;
    client.connect();
    /*cPlayer player;
    client.setPlayer(&player);*/

    sf::Event event;
    while(window.isOpen()){
        rha::checkEvent(&window, &event);


        window.clear();
        //...

        window.display();
    }
    return 0;
}
