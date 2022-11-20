all: clean bin/cRace

bin/cRace: bin/main.o bin/Agent.o bin/Graph.o bin/Parser.o bin/Party.o bin/Simulation.o bin/SelectionPolicy.o bin/JoinPolicy.o bin/Coalition.o bin/Offer.o
	g++ -o bin/cRace bin/main.o bin/Agent.o bin/Graph.o bin/Parser.o bin/Party.o bin/Simulation.o bin/SelectionPolicy.o bin/JoinPolicy.o bin/Coalition.o bin/Offer.o

bin/main.o: src/main.cpp src/Simulation.cpp src/Parser.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Agent.o: src/Agent.cpp src/Graph.cpp src/Coalition.cpp src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp

bin/Graph.o: src/Graph.cpp src/Party.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp

bin/Parser.o: src/Parser.cpp src/Simulation.cpp src/Agent.cpp src/SelectionPolicy.cpp src/JoinPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Parser.o src/Parser.cpp

bin/Party.o: src/Party.cpp src/Offer.cpp src/Simulation.cpp src/JoinPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Party.o src/Party.cpp

bin/Simulation.o: src/Simulation.cpp src/Graph.cpp src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Simulation.o src/Simulation.cpp

bin/SelectionPolicy.o: src/SelectionPolicy.cpp src/Simulation.cpp src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp

bin/JoinPolicy.o: src/JoinPolicy.cpp src/Simulation.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/JoinPolicy.o src/JoinPolicy.cpp

bin/Coalition.o: src/Coalition.cpp src/Party.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Coalition.o src/Coalition.cpp

bin/Offer.o: src/Offer.cpp src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Offer.o src/Offer.cpp


clean:
	rm -f bin/*
