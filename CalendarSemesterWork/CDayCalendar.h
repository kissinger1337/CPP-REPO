#pragma once
#include "CCalendar.h"
#include "CDate.h"
#include <chrono>
#include <iomanip>
#include <iostream>

class CDayCalendar : public CCalendar {
public:
    int day;
    int month;
    int year;

    CDayCalendar(std::vector<std::shared_ptr<CEvent>> & m_Events, CDate & date) :
    CCalendar(m_Events),
    day(date.m_Day), month(date.m_Month), year(date.m_Year) {}

    void printCalendar() const override;
};
