# Parallel-Implementation-of-Genetic-Algorithms-for-TSP

how to run 

 g++ Optimized\ -\ Implementation/main.cpp Optimized\ -\ Implementation/Point/point.cpp Optimized\ -\ Implementation/Genetic-Algorithm/path_representation.cpp Optimized\ -\ Implementation/Genetic-Algorithm/Crossover/random_crossover.cpp Optimized\ -\ Implementation/Genetic-Algorithm/Crossover/partially_mapped_crossover.cpp Optimized\ -\ Implementation/Genetic-Algorithm/Crossover/uniform_partially_mapped_crossover.cpp -o optimized -fopenmp

./optimized --population 1000 --generation 10 --keep 100 --mutation 900 < "./test-files/test-500.txt"
