#include "CStringGetter.h"

 std::string CStringGetter::getFromUser(const std::string & message, std::ostream & out) {
    out << message;
    std::string input;
    std::getline(std::cin, input);
     if(std::cin.eof()){
         std::cin.clear();
         throw std::invalid_argument("EOF before exit detected.\n");
     }
    return input;
}
