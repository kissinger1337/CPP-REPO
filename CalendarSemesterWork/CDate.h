#pragma once
#include <ctime>
#include <iostream>
#include "CIntegerGetter.h"
#include "CStringGetter.h"
#include "CAppParameters.h"
class CDate{
public:
    int m_Day;
    int m_Month;
    int m_Year;
    int m_Hour;
    int m_Minute;

    CDate() = default;

    CDate(const CDate &other) : m_Day(other.m_Day), m_Month(other.m_Month), m_Year(other.m_Year), m_Hour(other.m_Hour), m_Minute(other.m_Minute) {}

    CDate(int minute, int hour, int day, int month, int year);

    friend std::ostream &operator<<(std::ostream &os, const CDate &date);

    friend CDate operator+(const CDate & date,int hours);

    friend bool operator< (const CDate & date, const CDate & date2);

    friend bool operator== (const CDate & date, const CDate & date2);

    static CDate todayDate();

    int getFirstDayOfMonth() const;

    bool isLeapYear() const;

    bool checkDate() const;

    void getFromUser();

    static int getDayOfWeek(int day, int month, int year);
};

