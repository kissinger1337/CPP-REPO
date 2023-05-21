#include "CApp.h"

CApp::CApp()
{
    CDate tmpDate;
    std::vector<std::shared_ptr<CEvent>> tmpEvent;
    calendar = std::make_shared<CDayCalendar> (tmpEvent, tmpDate);
}

void CApp::run() {
    m_UserInterface.begin();
    bool isRunning = true;
    while(isRunning){
        try{
            isRunning = m_UserInterface.printInterface(calendar);
        }
        catch (std::exception& e){
            std::cout << "\n" << std::endl;
            std::cout << e.what() << std::endl;
            isRunning = false;
            std::cout << "Caught exception in CApp" << std::endl;
        }
    }
}