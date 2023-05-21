#pragma once
#include <iostream>
#include <limits>
#include "CAppParameters.h"


class CStringGetter {
public:
    static std::string getFromUser(const std::string & message = "", std::ostream & out = std::cout) ;
    static bool checkEOF();

};
