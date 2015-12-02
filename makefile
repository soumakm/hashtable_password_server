proj5.x: passserver.cpp proj5.cpp
	g++ -Wall -pedantic -std=c++11 -g -o proj5.x passserver.cpp -lcrypt proj5.cpp

clean:
	rm -f *.o *.x core.*
