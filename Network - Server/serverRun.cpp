#include "serverManager.hpp"

void rha::cServerManager::sRunning(){
    sf::TcpListener listener;

    sf::Clock clock; //for fixed step loop
    sf::Time time, timeOfUpdate=sf::Time::Zero;
    const sf::Time timeStep=sf::seconds(1/60.f);

    std::thread connectThread, receiveThread;
    bool run=true, stop1=false, stop2=false;


    server.listening(&listener, 7415);
    gui.loadWidgetsFromFile("media/runForm.RhAf");

    connectThread=std::thread(&rha::cServer::findNewConnection, &server, &gui, &run, &stop1);
    receiveThread=std::thread(&rha::cServer::receiveData, &server, &gui, &run, &stop2);

    while(state==RUN){
        time=clock.restart();

        timeOfUpdate+=time;
        while(timeOfUpdate>timeStep){
            timeOfUpdate-=timeStep;

            if(stop1&&stop2){server.releaseResources(); state=WAIT;}
            while(window.pollEvent(event))
              gui.handleEvent(event);

            while(gui.pollCallback(callback)){
                switch(callback.id)
                 case 1:{
                   run=false;
                    connectThread.detach();
                    receiveThread.detach();
                   break;
                }
            }

            server.serveClients();
        }

        window.clear();
        gui.draw();

        window.display();
    }
}
