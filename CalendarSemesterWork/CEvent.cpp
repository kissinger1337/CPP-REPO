#include "CEvent.h"

CEvent::CEvent(std::string &eventName, CDate &date, int duration,
               const std::string &place, const std::string &description,
               const std::vector<std::string> &participants, const std::vector<std::string> &tags) :
        m_EventName(eventName),
        m_Date(date),
        m_Duration(duration),
        m_Place(place),
        m_Description(description),
        m_Participants(participants),
        m_Tags(tags) {}