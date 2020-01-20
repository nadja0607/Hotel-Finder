all: main.o HotelsMap.o Hotel.o
	g++ main.o  HotelsMap.o Hotel.o -o hotelFinder
main.o: main.cpp
	g++ -c main.cpp
Hotels.o: Hotel.h Hotel.cpp
	g++ -c Hotel.cpp
HotelsMap.o: HotelsMap.h HotelsMap.cpp
	g++ -c  HotelsMap.cpp
clean:
	rm *.o hotelFinder

