#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class CAppParameters {
public:
    //TODO napsat funkci, která načte všechne tyto parametry z konfiguráku sem
    const static int m_MaxDuration = 23;
    const static int m_MinDuration = 0;
    //const static int m_MAX_CHARS = 5;
    const static int m_MinYear = 1900;
    const static int m_MaxYear = 2100;
    //const std::string m_Separator = "########################################";
    const std::string m_NamesOfDays[8] = {"nothing", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    constexpr const static int m_Days[13] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const std::string m_MonthList[13] = {"nothing","January", "February", "March", "April", "May", "June",
                                   "July", "August", "September", "October", "November", "December"};
    const std::string mailEnding = "@fit.cvut.cz";
};