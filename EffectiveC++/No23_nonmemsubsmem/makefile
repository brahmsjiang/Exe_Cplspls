
test:main.o webbrowsercookies.o webbrowserbookmarks.o webbrowser.o
	g++ -Wall main.o webbrowsercookies.o webbrowserbookmarks.o webbrowser.o -o test

main.o:main.cpp webbrowserbookmarks.h webbrowsercookies.h webbrowser.h
	g++ -c -Wall main.cpp -o main.o

webbrowser.o:webbrowser.cpp webbrowser.h
	g++ -c -Wall webbrowser.cpp -o webbrowser.o

webbrowsercookies.o:webbrowsercookies.cpp webbrowsercookies.h webbrowser.h
	g++ -c -Wall webbrowserbookmarks.cpp -o webbrowsercookies.o

webbrowserbookmarks.o:webbrowserbookmarks.cpp webbrowserbookmarks.h webbrowser.h
	g++ -c -Wall webbrowserbookmarks.cpp -o webbrowserbookmarks.o

clean:
	rm -rf *.o *.gch test 
