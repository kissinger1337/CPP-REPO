CXX=g++
LD=g++
CFLAGS = -Wall -pedantic -std=c++17
directory = .

all: clean main
main: $(directory)/main.o $(directory)/CUserInterface.o $(directory)/CStringGetter.o $(directory)/CRepeatingEvent.o $(directory)/COneTimeEvent.o $(directory)/CMonthCalendar.o $(directory)/CIntegerGetter.o $(directory)/CEvent.o $(directory)/CDayCalendar.o $(directory)/CDate.o $(directory)/CCalendar.o $(directory)/CAppParameters.o $(directory)/CApp.o
	$(LD) $(directory)/main.o $(directory)/CUserInterface.o $(directory)/CStringGetter.o $(directory)/CRepeatingEvent.o $(directory)/COneTimeEvent.o $(directory)/CMonthCalendar.o $(directory)/CIntegerGetter.o $(directory)/CEvent.o $(directory)/CDayCalendar.o $(directory)/CDate.o $(directory)/CCalendar.o $(directory)/CAppParameters.o $(directory)/CApp.o -fsanitize=address -g -o main.out

$(directory)/main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp -o $(directory)/main.o

$(directory)/CUserInterface.o: CUserInterface.h CUserInterface.cpp
	$(CXX) $(CFLAGS) -c CUserInterface.cpp -o $(directory)/CUserInterface.o

$(directory)/CStringGetter.o: CStringGetter.h CStringGetter.cpp
	$(CXX) $(CFLAGS) -c CStringGetter.cpp -o $(directory)/CStringGetter.o

$(directory)/CRepeatingEvent.o: CRepeatingEvent.h CRepeatingEvent.cpp
	$(CXX) $(CFLAGS) -c CRepeatingEvent.cpp -o $(directory)/CRepeatingEvent.o

$(directory)/COneTimeEvent.o: COneTimeEvent.h COneTimeEvent.cpp
	$(CXX) $(CFLAGS) -c COneTimeEvent.cpp -o $(directory)/COneTimeEvent.o

$(directory)/CMonthCalendar.o: CMonthCalendar.h CMonthCalendar.cpp
	$(CXX) $(CFLAGS) -c CMonthCalendar.cpp -o $(directory)/CMonthCalendar.o

$(directory)/CIntegerGetter.o: CIntegerGetter.h CIntegerGetter.cpp
	$(CXX) $(CFLAGS) -c CIntegerGetter.cpp -o $(directory)/CIntegerGetter.o

$(directory)/CEvent.o: CEvent.h CEvent.cpp
	$(CXX) $(CFLAGS) -c CEvent.cpp -o $(directory)/CEvent.o

$(directory)/CDayCalendar.o: CDayCalendar.h CDayCalendar.cpp
	$(CXX) $(CFLAGS) -c CDayCalendar.cpp -o $(directory)/CDayCalendar.o

$(directory)/CDate.o: CDate.h CDate.cpp
	$(CXX) $(CFLAGS) -c CDate.cpp -o $(directory)/CDate.o

$(directory)/CConfigFile.o: CConfigFile.h CConfigFile.cpp
	$(CXX) $(CFLAGS) -c CConfigFile.cpp -o $(directory)/CConfigFile.o

$(directory)/CCalendar.o: CCalendar.h CCalendar.cpp
	$(CXX) $(CFLAGS) -c CCalendar.cpp -o $(directory)/CCalendar.o

$(directory)/CAppParameters.o: CAppParameters.h CAppParameters.cpp
	$(CXX) $(CFLAGS) -c CAppParameters.cpp -o $(directory)/CAppParameters.o

$(directory)/CApp.o: CApp.h CApp.cpp
	$(CXX) $(CFLAGS) -c CApp.cpp -o $(directory)/CApp.o

clean:
	rm -f $(directory)/*.o main
