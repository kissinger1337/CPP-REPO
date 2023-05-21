#include "CRepeatingEvent.h"

void CRepeatingEvent::print() const {
    std::cout << "----------------------------" << std::endl;
    std::cout << "                 Name: " << m_EventName << std::endl;
    std::cout << "Date of the beginning: " << m_Date << std::endl;
    std::cout << "          Ending date: " << m_Date + m_Duration << std::endl;
    std::cout << "    City of the event: " << m_Place << std::endl;
    for(auto & participant : m_Participants){
        std::cout << "          Participant: " << participant << " "<< participant << m_Parameters.mailEnding << std::endl;
    }
    for(auto & tag : m_Tags){
        std::cout << "                  Tag: " << tag << " " << std::endl;
    }
    std::cout << "          Description: " << m_Description << std::endl;
    std::cout << "           Repetition: Every day " << std::endl;
    std::cout << "----------------------------" << std::endl;
}
