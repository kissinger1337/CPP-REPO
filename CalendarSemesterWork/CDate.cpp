#include "CDate.h"

std::ostream &operator<<(std::ostream &os, const CDate &date) {
    os << " DD/MM/YYYY | HH:MM\n\t\t\t" << std::setw(2) << std::setfill('0') << date.m_Day << "/" <<
        std::setw(2) << std::setfill('0') << date.m_Month << "/"
        << date.m_Year << " | " << std::setw(2) << std::setfill('0') << date.m_Hour << ":" <<
        std::setw(2) << std::setfill('0') << date.m_Minute ;
    return os;
}

CDate operator+(const CDate & date,int hours) {
    CDate tmp (date);
    tmp.m_Hour += hours;
    if(tmp.m_Hour > 23){
        tmp.m_Day += 1;
        tmp.m_Hour = tmp.m_Hour-24;
    }
    //--------------------
    if(tmp.m_Day > CAppParameters::m_Days[tmp.m_Month]) {
        if (tmp.m_Month == 2) {
            if (tmp.isLeapYear() && tmp.m_Day == 29) {
                tmp.m_Day = 29;
            }
            if (tmp.isLeapYear() && tmp.m_Day == 30) {
                tmp.m_Day = 1;
                tmp.m_Month += 1;
            }
            if (!tmp.isLeapYear() && tmp.m_Day == 29) {
                tmp.m_Day = 1;
                tmp.m_Month += 1;
            }
        }
        else{
            tmp.m_Day = 1;
            tmp.m_Month += 1;
        }
    }
    //--------------------
    if(tmp.m_Month>12){
        tmp.m_Month = 1;
        tmp.m_Year += 1;
    }
    if(tmp.m_Year > CAppParameters::m_MaxYear || tmp.m_Year < CAppParameters::m_MinYear){
        throw std::invalid_argument ("You are trying to use year that is out of bounds");
    }
    return tmp;
}

bool operator< (const CDate & date, const CDate & date2) {
    if(date.m_Year < date2.m_Year){
        return true;
    }
    if(date.m_Year > date2.m_Year){
        return false;
    }
    if(date.m_Month < date2.m_Month){
        return true;
    }
    if(date.m_Month > date2.m_Month){
        return false;
    }
    if(date.m_Day < date2.m_Day){
        return true;
    }
    if(date.m_Day > date2.m_Day){
        return false;
    }
    if(date.m_Hour < date2.m_Hour){
        return true;
    }
    if(date.m_Hour > date2.m_Hour){
        return false;
    }
    if(date.m_Minute < date2.m_Minute){
        return true;
    }
    if(date.m_Minute > date2.m_Minute){
        return false;
    }
    return false;
}

bool operator== (const CDate & date, const CDate & date2) {
    if(date.m_Year == date2.m_Year && date.m_Month == date2.m_Month && date.m_Day == date2.m_Day
       && date.m_Hour == date2.m_Hour && date.m_Minute == date2.m_Minute){
        return true;
    }
    return false;
}

CDate::CDate(int minute, int hour, int day, int month, int year) :
        m_Day(day),
        m_Month(month),
        m_Year(year),
        m_Hour(hour),
        m_Minute(minute){}

CDate CDate::todayDate() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return {ltm->tm_min,ltm->tm_hour, ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year};
}

int CDate::getFirstDayOfMonth() const{
    if (m_Month < 1 || m_Month > 12) {
        throw std::invalid_argument("Invalid month!");
        return -1;
    }

    if (m_Year < CAppParameters::m_MinYear || m_Year > CAppParameters::m_MaxYear) {
        throw std::invalid_argument("Invalid year!");
        return -1;
    }

    int a = (14 - m_Month) / 12;
    int y = m_Year - a;
    int m = m_Month + 12 * a - 2;

    // Zeller's Congruence algorithm
    int weekday = (1 + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;

    return weekday;
}

bool CDate::isLeapYear() const{
    if (m_Year % 4 == 0) {
        if (m_Year % 100 == 0) {
            if (m_Year % 400 == 0) {
                return true;  // Divisible by 400, so it's a leap year
            } else {
                return false; // Divisible by 100 but not by 400, not a leap year
            }
        } else {
            return true;  // Divisible by 4 but not by 100, so it's a leap year
        }
    } else {
        return false;  // Not divisible by 4, not a leap year
    }
}

bool CDate::checkDate() const{
    if (m_Day == 31 && (m_Month == 2 || m_Month == 4 || m_Month == 6 || m_Month == 9 || m_Month == 11)) {
        return false;
    }
    if (m_Day == 30 && (m_Month == 1 || m_Month == 3 || m_Month == 5 || m_Month == 7 || m_Month == 8 || m_Month == 10)){
        return false;
    }
    if(m_Day > 31 || m_Day < 1){
        return false;
    }
    if (m_Day == 30 && m_Month == 2) {
        return false;
    }
    if (m_Day == 29 && m_Month == 2 && !isLeapYear()) {
        return false;
    }
    if(m_Day > CAppParameters::m_Days[m_Month] && m_Day != 29){
        return false;
    }
    if(m_Hour > 23 || m_Hour < 0){
        return false;
    }
    if(m_Minute > 59 || m_Minute < 0){
        return false;
    }
    if(m_Year < CAppParameters::m_MinYear || m_Year > CAppParameters::m_MaxYear){
        return false;
    }
    if(m_Month < 1 || m_Month > 12){
        return false;
    }
    return true;
}


void CDate::getFromUser() {
    bool running = true;
    while(running) {
        CDate tmp{};
        std::cout << "Enter the minute: ";
        tmp.m_Minute = CIntegerGetter::getFromUser(0, 59);
        std::cout << "Enter the hour: ";
        tmp.m_Hour = CIntegerGetter::getFromUser(0, 24);
        std::cout << "Enter the day: ";
        tmp.m_Day = CIntegerGetter::getFromUser(1, 31);
        std::cout << "Enter the month: ";
        tmp.m_Month = CIntegerGetter::getFromUser(1, 12);
        std::cout << "Enter the year: ";
        tmp.m_Year = CIntegerGetter::getFromUser(CAppParameters::m_MinYear, CAppParameters::m_MaxYear);
        if (tmp.checkDate()){
            *this = tmp;
            running = false;
        }
        else{
            std::cout << "Invalid date! Try again." << std::endl;
        }
    }
}

int CDate::getDayOfWeek(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }

    int century = year / 100;
    int yearOfCentury = year % 100;

    int dayOfWeek = (day + (13 * (month + 1) / 5) + yearOfCentury + (yearOfCentury / 4) + (century / 4) - (2 * century)) % 7;

    // Adjust the result to have Monday as the first day of the week (0-indexed)
    dayOfWeek = (dayOfWeek + 6) % 7;

    // Adjust the result to have Sunday as the seventh day of the week (0-indexed)
    if (dayOfWeek == 0)
        dayOfWeek = 7;

    return dayOfWeek;
}

