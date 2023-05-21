#pragma once
#include "CEvent.h"
#include "CAppParameters.h"
#include <iostream>

class COneTimeEvent : public CEvent{
public:


    COneTimeEvent() = default;

    COneTimeEvent(std::string & eventName, CDate & date, int duration,
                    const std::string & place = "", const std::string & description = "",
                    const std::vector<std::string> & participants = {}, const std::vector<std::string> & tags = {})
            : CEvent(eventName, date, duration, place, description, participants, tags) {}

    void print() const override;
};
