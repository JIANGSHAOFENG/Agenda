Agenda: User.o Date.o Meeting.o Storage.o AgendaService.o AgendaUI.o Agenda.cpp
	g++ -std=c++11 -o Agenda User.o Date.o Meeting.o Storage.o AgendaService.o AgendaUI.o Agenda.cpp

User.o: User.cpp User.h
	g++ -c -std=c++11 User.cpp -o User.o

Date.o: Date.cpp Date.h
	g++ -c -std=c++11 Date.cpp -o Date.o

Meeting.o: Meeting.cpp Meeting.h
	g++ -c -std=c++11 Meeting.cpp -o Meeting.o

Storage.o: Storage.cpp Storage.h
	g++ -c -std=c++11 Storage.cpp -o Storage.o

AgendaService.o: AgendaService.cpp AgendaService.h
	g++ -c -std=c++11 AgendaService.cpp -o AgendaService.o

AgendaUI.o: AgendaUI.cpp AgendaUI.h
	g++ -c -std=c++11 AgendaUI.cpp -o AgendaUI.o

clean:
	rm *.o Agenda
