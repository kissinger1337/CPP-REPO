#pragma once
#include <iostream>
#include "CDate.h"
#include "CIntegerGetter.h"
#include "CCalendar.h"
#include "CMonthCalendar.h"
#include "CDayCalendar.h"


class CUserInterface{
public:

    CAppParameters m_AppParameters;

    int m_State;

    CUserInterface();

    bool printInterface(std::shared_ptr<CCalendar> calendar);

    bool endAndStartAgain();

    void begin();
};
