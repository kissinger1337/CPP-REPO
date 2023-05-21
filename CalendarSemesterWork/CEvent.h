#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "CDate.h"
#include "CAppParameters.h"

class CEvent {
public:

    CEvent() = default;
    //virtual ~CEvent() = default;

    CEvent(std::string &eventName, CDate &date, int duration,
           const std::string &place = "", const std::string &description = "",
           const std::vector<std::string> &participants = {}, const std::vector<std::string> &tags = {});

    virtual void print() const = 0;

    CAppParameters m_Parameters;
    std::string m_EventName;
    CDate m_Date;
    int m_Duration;
    std::string m_Place;
    std::string m_Description;
    std::vector<std::string> m_Participants;
    std::vector<std::string> m_Tags;
};

