#ifndef HELPER_HPP_INCLUDED
#define HELPER_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    void checkEvent(sf::Window* window, sf::Event* event); //deprecated
    bool checkPhrase(std::string text, std::string phrase);
    std::string varToString(int variable, std::string text="");
        //provisional function, removed after using c++14

    //...
}

#endif // HELPER_HPP_INCLUDED
