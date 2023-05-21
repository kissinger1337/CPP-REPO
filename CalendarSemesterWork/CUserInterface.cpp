#include "CUserInterface.h"

bool CUserInterface::endAndStartAgain() {
    m_State = 0;
    return false;
}

CUserInterface::CUserInterface() : m_State(0) {

}

void CUserInterface::begin(){
    std::cout << "Welcome to the program!" << std::endl;
}

bool CUserInterface::printInterface(std::shared_ptr<CCalendar> calendar) {
        int numOfOptions = 3;
        std::cout << "+###########################################################+" << std::endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1. Draw a calendar" << std::endl;
        std::cout << "2. Add an event" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "+###########################################################+" << std::endl;
        int choice = CIntegerGetter::getFromUser(1, numOfOptions);
        m_State = choice;

        if(m_State == 1){
            numOfOptions = 3;
            std::cout << "+###########################################################+" << std::endl;
            std::cout << "Please select an option:" << std::endl;
            std::cout << "1. Draw a month calendar (not yet implemented)" << std::endl;
            std::cout << "2. Draw a week calendar  (not yet implemented)" << std::endl;
            std::cout << "3. Draw a day calendar" << std::endl;
            std::cout << "+###########################################################+" << std::endl;
            
            choice = CIntegerGetter::getFromUser(1, numOfOptions);
            switch (choice) {
                case 1:
                {
                    std::cout << "NOT YET IMPLEMENTED" << std::endl;
                    //TODO IMPLEMENT
                    endAndStartAgain();
                    break;
                }
                case 2:
                {
                    std::cout << "NOT YET IMPLEMENTED" << std::endl;
                    //TODO IMPLEMENT
                    endAndStartAgain();
                    break;
                }
                case 3:
                {
                    CDate date{};
                    date.getFromUser();
                    calendar = std::make_shared<CDayCalendar> (calendar->m_Events, date);
                    calendar -> printCalendar();
                    endAndStartAgain();
                    break;
                }
                default:
                    endAndStartAgain();
                    break;
            }
            
            m_State = 0;
            return true;
        }
        else if(m_State == 2){
            calendar->addEvent();
            //m_Calendar.printEvents(); for debugging
            return true;
        }
        else if(m_State == 3){
            return false;
        }
        std::cout << std::endl;
    return false;
}

