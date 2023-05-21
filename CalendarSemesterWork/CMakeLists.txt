cmake_minimum_required(VERSION 3.24)
project(Semester_work)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Semester_work
        CApp.h
        CAppParameters.h
        CCalendar.cpp
        CCalendar.h
        CConfigFile.h
        CDate.cpp
        CDate.h
        CDayCalendar.cpp
        CDayCalendar.h
        CEvent.h
        CMonthCalendar.cpp
        CMonthCalendar.h
        CUserInterface.h
        main.cpp CApp.cpp CUserInterface.cpp CIntegerGetter.cpp CIntegerGetter.h CStringGetter.h CRepeatingEvent.h COneTimeEvent.h CRepeatingEvent.cpp COneTimeEvent.cpp CWeekCalendar.h CEvent.cpp CWeekCalendar.cpp CStringGetter.cpp CAppParameters.cpp)
