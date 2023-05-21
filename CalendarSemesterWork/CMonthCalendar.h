#pragma once

#include "CDate.h"
#include "CCalendar.h"
#include <iostream>
#include <iomanip>

class CMonthCalendar : public CCalendar{
public:
    CMonthCalendar(const CDate & date);
    void printCalendar() const override;
    //void printEvents(std::vector<CEvent> & events) const override; TODO

};
