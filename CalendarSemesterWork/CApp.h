#pragma once
#include <exception>
#include "CUserInterface.h"
#include <iostream>

class CApp{
public:
    CApp();
    CUserInterface m_UserInterface;
    std::shared_ptr<CCalendar> calendar;
    void run();
};