#include "CDate.h"
/*#include "CDayCalendar.h"
#include "CWeekCalendar.h"
#include "CMonthCalendar.h"*/
#include "CApp.h"
#include <cassert>

int main() {

    //TODO Mám myslet při načítání na něco, co není v UTF-8? Budou se při obhajobě testovat vícebajtové znaky
    // musí to fungovat, když zadávám třeba ruštinu?

    //hour day month year
    CDate test1 {0,23, 28, 2, 2000};
    CDate test2 {0,0, 29, 2, 2000};
    assert(test1 + 1 == test2);
    assert(test1 < test2);
    CDate test3 {1,0, 28, 2, 2000};
    CDate test4 {1,23, 28, 2, 2000};
    assert(test3 + 23 == test4);
    assert(test3 < test4);
    CDate test5 {20, 10, 29, 2, 2000};
    CDate test6 {20, 1, 1, 3, 2000};
    assert(test5 + 15 == test6);
    assert(test5 < test6);
    CDate test7 {15, 23, 28, 2, 1999};
    CDate test8 {15, 0, 1, 3, 1999};
    assert(test7 + 1 == test8);
    assert(test7 < test8);
    assert(!(test7 + 2 == test8));
    assert(!(test7 + 0 == test8));
    CDate test9  {59, 23, 31, 12, 1999};
    CDate test10 {59, 0, 1, 1, 2000};
    assert(test9 + 1 == test10);
    assert(test9 < test10);
    CDate test11 {21, 23, 31, 1, 1999};
    CDate test12 {21, 0, 1, 2, 1999};
    assert(test11 + 1 == test12);
    assert(test11 < test12);
    CDate test13 {30, 23, 31, 1, 2000};
    CDate test14 {30, 0, 1, 2, 2000};
    assert(test13 + 1 == test14);
    assert(test13 < test14);
    CDate test15 {8, 0, 1, 1, 2000};
    CDate test16 {8, 0, 2, 1, 2000};
    assert(test15 + 24 == test16);
    assert(test15 < test16);
    CDate test17 {11,5, 28, 2, 2000};
    CDate test18 {11,5, 29, 2, 2000};
    assert(test17 + 24 == test18);
    assert(test17 < test18);
    CDate test19 {58,23, 31, 12, 2000};
    CDate test20 {58,23, 1, 1, 2001};
    assert(test19 + 24 == test20);
    assert(test19 < test20);

    assert(CDate::getDayOfWeek(28,2,2000)==1);
    assert(CDate::getDayOfWeek(29,2,2000)==2);
    assert(CDate::getDayOfWeek(1,3,2000)==3);
    assert(CDate::getDayOfWeek(11,11,2000)==6);
    assert(CDate::getDayOfWeek(12,11,2000)==7);
    assert(CDate::getDayOfWeek(13,11,2000)==1);
    assert(CDate::getDayOfWeek(14,11,2000)==2);
    assert(CDate::getDayOfWeek(15,11,2000)==3);
    assert(CDate::getDayOfWeek(16,11,2000)==4);
    assert(CDate::getDayOfWeek(17,11,2000)==5);
    assert(CDate::getDayOfWeek(18,11,2000)==6);
    assert(CDate::getDayOfWeek(19,11,2000)==7);
    assert(CDate::getDayOfWeek(20,11,2000)==1);
    assert(CDate::getDayOfWeek(21,11,2000)==2);
    assert(CDate::getDayOfWeek(22,11,2000)==3);
    assert(CDate::getDayOfWeek(23,11,2000)==4);
    assert(CDate::getDayOfWeek(24,11,2000)==5);
    assert(CDate::getDayOfWeek(25,11,2000)==6);
    assert(CDate::getDayOfWeek(26,11,2000)==7);
    assert(CDate::getDayOfWeek(27,11,2000)==1);
    assert(CDate::getDayOfWeek(28,11,2000)==2);
    assert(CDate::getDayOfWeek(29,11,2000)==3);
    assert(CDate::getDayOfWeek(30,11,2000)==4);
    assert(CDate::getDayOfWeek(1,12,2000)==5);
    assert(CDate::getDayOfWeek(2,12,2000)==6);

    CDate test21{60,1,1,1,2000};
    assert(test21.checkDate()==false);
    CDate test22{59,23,31,1,2000};
    assert(test22.checkDate()==true);
    CDate test23{59,23,29,2,2023};
    assert(test23.checkDate()==false);
    CDate test24{59,23,30,2,2023};
    assert(test24.checkDate()==false);
    CDate test25{59,23,30,2,2000};
    assert(test25.checkDate()==false);
    CDate test26{59,23,1,2,CAppParameters::m_MaxYear+1};
    assert(test26.checkDate()==false);
    CDate test27{59,23,1,2,CAppParameters::m_MinYear-1};
    assert(test27.checkDate()==false);
    CDate test28{0,0,1,2,2000};
    assert(test28.checkDate()==true);
    CDate test29{0,0,0,2,2000};
    assert(test29.checkDate()==false);
    CDate test30{0,0,1,13,2000};
    assert(test30.checkDate()==false);
    CDate test31{0,0,1,0,2000};
    assert(test31.checkDate()==false);
    CDate test32{0,0,31,4,2000};
    assert(test32.checkDate()==false);

    CDate test33{0,0,31,4,2000};
    CDate test34{1,0,31,4,2000};
    assert(test33 < test34);
    CDate test35{0,0,31,4,2000};
    CDate test36{0,1,31,4,2000};
    assert(test35 < test36);

    CApp app;
    try {
        app.run();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "Caught exception in main.cpp" << std::endl;
        return -1;
    }

    //TODO Musim zobrazovat udalosti v kalendari
    //TODO Musim pridat virtualni funkci list calendar
    //TODO Musim smazat rocni kalendar, musim mit jenom denni, tydenni a mesicni


    return 0;
}