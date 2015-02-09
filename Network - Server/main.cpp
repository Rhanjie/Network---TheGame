#include <managerLibs.hpp>
#include <helper.hpp> //todo

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Network - Server", sf::Style::Close);

    /** TODO, because must put in my class **/
    sf::TcpListener listener;
    std::vector<sf::TcpSocket*>clients;
    sf::SocketSelector selector;

    listener.listen(7415);
    selector.add(listener);

    sf::Event event;
    while(window.isOpen()){
        rha::checkEvent(&window, &event);
        if(selector.wait(sf::seconds(0.02))){
            if(selector.isReady(listener)){
                sf::TcpSocket* newUser=new sf::TcpSocket;
                listener.accept(*newUser);
                clients.push_back(newUser);
                selector.add(*newUser);

                std::cout<<"New Client is connected!\n";
            }
            if(!clients.empty()){
                for(short i=0; i<clients.size(); ++i){
                    if(selector.isReady(*clients[i])){
                        //... todo - receive packets.
                    }
                }
            }
        }

        window.clear();
        //...

        window.display();
    }
    return 0;
}
