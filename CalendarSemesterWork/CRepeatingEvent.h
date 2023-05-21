#pragma once
#include "CEvent.h"
#include <iostream>

class CRepeatingEvent : public CEvent{

public:
    CRepeatingEvent() = default;

    CRepeatingEvent(std::string & eventName, CDate & date, int duration,
                    const std::string & place = "", const std::string & description = "",
                    const std::vector<std::string> & participants = {}, const std::vector<std::string> & tags = {})
                    : CEvent(eventName, date, duration, place, description, participants, tags) {}

    void print() const override;
};