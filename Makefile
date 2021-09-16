run_tspga.o: main.o 
	g++ main.o -o run_tspga 

main.o: main.cpp ./Point/point.cpp ./Genetic-Algorithm/path_representation.cpp ./Genetic-Algorithm/Crossover/random_crossover.cpp ./Genetic-Algorithm/Crossover/partially_mapped_crossover.cpp ./Genetic-Algorithm/Crossover/uniform_partially_mapped_crossover.cpp
	g++ -c -Wall main.cpp ./Point/point.cpp ./Genetic-Algorithm/path_representation.cpp ./Genetic-Algorithm/Crossover/random_crossover.cpp ./Genetic-Algorithm/Crossover/partially_mapped_crossover.cpp ./Genetic-Algorithm/Crossover/uniform_partially_mapped_crossover.cpp
	
clean:
	rm main.o run_tspga


