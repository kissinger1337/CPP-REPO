#include "CDayCalendar.h"


void CDayCalendar::printCalendar() const{
    std::cout << "\n\n\n\n\n";
    std::cout << "calendar for: " << m_AppParameters.m_NamesOfDays[CDate::getDayOfWeek(day,month,year)] << " " << day << "." << month << "." << year << std::endl;

    std::cout << "Events: " << std::endl;

    for(auto &event : m_Events){
        if(event->m_Date.m_Day == day && event->m_Date.m_Month == month
        && event->m_Date.m_Year == year) event->print();
    }
    std::cout << "\n\n";
}


