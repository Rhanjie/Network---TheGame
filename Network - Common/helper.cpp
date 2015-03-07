#include "helper.hpp"

bool rha::checkPhrase(std::string text, std::string phrase){
    size_t searched_phrase=text.find(phrase);
    if(searched_phrase==std::string::npos){
        return false;
    }else return true;
}

std::string varToString(int variable, std::string text=""){
    std::ostringstream helper;

    helper<<text<<variable;
    return helper.str();
}
