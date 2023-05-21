#include "CCalendar.h"

CCalendar::CCalendar(std::vector<std::shared_ptr<CEvent>> & events) : m_Events(events) {}

std::string CCalendar::getMonthName(int num) const {
    return m_AppParameters.m_MonthList[num];
}

bool CCalendar::addEvent() {
    //get event name
    std::string eventName = "";
    while(true) {
        eventName = CStringGetter::getFromUser("Input name of the event: ");
        if(eventName.empty() || eventName[0] == ' ') {
            std::cout << "Event name cannot be empty or start with whitespace!" << std::endl;
        }
        else break;
    }
    //---------------------------------------
    //get date
    std::cout << "Input date of the event: " << std::endl;
    CDate date{};
    date.getFromUser(); //Looped until user inputs correct date. see getFromUser for details.
    //---------------------------------------
    //get duration in hours
    std::cout << "Input duration of the event: " << std::endl;
    int duration = CIntegerGetter::getFromUser(CAppParameters::m_MinDuration,CAppParameters::m_MaxDuration);
    //---------------------------------------
    //doest it repeat every day?
    std::cout << "Is this a repeating event? Input 1 if it is, 0 if it is not:" << std::endl;
    bool isEveryDay = CIntegerGetter::getFromUser(0,1);
    //---------------------------------------
    //Get place. Can be Empty.
    std::string place = CStringGetter::getFromUser("Input place of the event and press enter. Just Press enter if there is no place: ");
    //---------------------------------------
    //get description
    std::string description = CStringGetter::getFromUser("Input description of the event and press enter. Just Press enter if there is no description: ");
    //---------------------------------------
    //get participants
    std::vector<std::string> participants;
    std::cout << "Input participants of the event. Input 0 to stop." << std::endl;
    std::string participant = "";
    while (true) {
        participant = CStringGetter::getFromUser("Input participant of the event: ");
        if (participant == "0") {
            break;
        }
        if (participant.empty() || participant[0] == ' ') {
            std::cout << "Participant name cannot be empty or start with whitespace!" << std::endl;
            continue;
        }
        participants.push_back(participant);
    }
    //---------------------------------------
    //get tags
    std::vector<std::string> tags;
    std::cout << "Input tags of the event. Input 0 to stop." << std::endl;
    std::string tag;
    while (true) {
        tag = CStringGetter::getFromUser("Input tag of the event: ");
        if (tag == "0") {
            break;
        }
        if (tag.empty() || tag[0] == ' ') {
            std::cout << "Tag name cannot be empty or start with whitespace!" << std::endl;
            continue;
        }
        tags.push_back(tag);
    }
    //---------------------------------------
    //add event to the calendar
    if(!isEveryDay){
        m_Events.push_back(std::make_shared<COneTimeEvent>(eventName, date, duration, place,
                                                           description, participants, tags));
    }
    else {
        m_Events.push_back(std::make_shared<CRepeatingEvent>(eventName, date, duration, place,
                                                             description, participants, tags));
    }
    //---------------------------------------
    return true;
}

void CCalendar::printEvents() const {
    for (auto & m_Event : m_Events) {
        m_Event->print();
    }
}

/*void CCalendar::printCalendar() const {
    std::cout << "ERR";
}*/

