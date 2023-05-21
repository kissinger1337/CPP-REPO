#pragma once
#include "CDate.h"
#include "CAppParameters.h"
#include "CEvent.h"
#include "COneTimeEvent.h"
#include "CRepeatingEvent.h"
#include "CStringGetter.h"
#include "CIntegerGetter.h"
#include <vector>
#include <memory>

class CCalendar{
public:
    CCalendar() = default;

    CCalendar(std::vector<std::shared_ptr<CEvent>> & events);

    const CAppParameters m_AppParameters;
    std::vector<std::shared_ptr<CEvent>> m_Events;

    virtual void printCalendar() const = 0;
    //virtual void listCalendar() const = 0; TODO
    //std::vector<CEvent> findEvents() const; TODO

    CDate m_Date;

    void printEvents() const;

    std::string getMonthName(int num) const;

    bool addEvent();


};
