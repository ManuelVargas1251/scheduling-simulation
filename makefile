all: main.cpp
	g++ -std=c++11 main.cpp -o main

#Removes all object files from directory
#It also removes the executable of CacheSim 
#so to basically start with a clean slate every time
clean			:
			/bin/rm main *.o 