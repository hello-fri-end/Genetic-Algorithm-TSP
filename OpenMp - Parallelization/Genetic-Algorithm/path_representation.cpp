#include "path_representation.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>
extern "C"
{
#include<omp.h>
}

using std::vector;
using std::pair;
using std::cout;
using std::endl;

/* Takes the number of points to be visited &
 * generates a random order to visit those points
 *
 */
PathRepresentation::PathRepresentation( const int numPoints) {
  for(int i = 0 ; i < numPoints; ++i)
    genome.push_back(i);

  std::random_shuffle(genome.begin(), genome.end());
  fitnessScore = -1;
}


/*
 * Initializes the genome from the specified visit order.
 */
PathRepresentation::PathRepresentation(const vector<int>&order)
{
  genome = order;
  fitnessScore = -1;
}

PathRepresentation::~PathRepresentation()
{
  /*Nothing to do here*/
}

/*
 * Computes the fitness score (path length) of the genome.
 */
double PathRepresentation::fitness_score(const vector<vector<double>> &distances) {
  size_t numPoints = genome.size();

  fitnessScore = 0;

  for(size_t i = 0, j = 1; i < numPoints -1; ++i, ++j)
    fitnessScore += distances[genome.at(i)][genome.at(j)];

  // TS has to go back to the startting position.
  fitnessScore+= distances[genome.front()][genome.back()];

  return fitnessScore;
}


/*
 * Returns the visit order.
 */
vector<int> PathRepresentation::get_order() const {
  return genome;
}

/*
 * Returns the fitness score
 */
double PathRepresentation::get_fitness_score() const {
  return fitnessScore;
}

/*
 * Mutates the genome by swapping two random
 * values in the order vector.
 */
void PathRepresentation::mutate(){
  unsigned indexA;
  unsigned indexB;

  indexA = rand() % genome.size();
  do {
    indexB = rand()% genome.size();
  } while(indexB == indexA);

  std::iter_swap(genome.begin() + indexA, genome.begin() + indexB);
}

PathRepresentation run_genetic_algorithm(const std::vector<Point> &points,
                                         Crossover *CrossoverObject,
                                         size_t populationSize, size_t numGenerations,
                                         size_t keepPopulation, size_t numMutations)
{

  size_t threads[] = {1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 64, 128, 256};
  double time[12];
  double speedUp[12];
  PathRepresentation bestGenome(points.size());

  for(size_t thread = 0; thread < 12; ++thread)
  {
    double startTime = omp_get_wtime();
    cout<<"______ Running with "<<threads[thread]<<" threads ______"<<endl;
    cout<<endl;

    // Generate an initial population of random genes
    vector<PathRepresentation> population;
    size_t numPoints = points.size();

    // Store the distances betweeen points
    // to avoid repetetive calculations.
    vector<vector<double>>distances(numPoints, vector<double>(numPoints));

#pragma omp parallel for num_threads(threads[thread]) 
    for(unsigned i = 0; i < numPoints ; ++i)
      for(unsigned j = 0; j < numPoints ; ++j)
        distances[i][j] = points[i].distance_to(points[j]);



    for(unsigned i = 0 ; i < populationSize; ++i) {
      PathRepresentation genome(numPoints);
      population.push_back(genome);
    }

    // Compute fitness score of each genome.
    for(PathRepresentation& genome:population){
      genome.fitness_score(distances);
    }

    for(unsigned gen = 0; gen < numGenerations * 10; ++gen) {
      // sort the genomes by fitness.
      std::sort(population.begin(), population.end(), compare_paths);

      // Keep the top N fittest memebrs of the population &
      // replace the remaining memebrs with new genomes produced
      // by crosslinking.

#pragma omp parallel for num_threads(threads[thread]) 

      for(unsigned i = keepPopulation; i < populationSize; ++i){
        unsigned indexA;
        unsigned indexB;

        // range [0 . . . keepPopulation - 1]
        indexA = rand() % keepPopulation;
        do {
          indexB = rand() % keepPopulation;
        } while( indexA == indexB);

        pair<PathRepresentation, PathRepresentation>  offsprings= 
          CrossoverObject->crosslink(population[indexA], population[indexB]); 

        // Get the fitness score of both the springs 
        // & choose the fitter one.
        offsprings.first.fitness_score(distances);
        offsprings.second.fitness_score(distances);

        if (compare_paths(offsprings.first, offsprings.second) )
          population[i] = offsprings.first;
        else
          population[i] = offsprings.second;
      }

    //Mutate random genes
#pragma omp parallel for num_threads(threads[thread]) 

    for(unsigned i = 0; i < numMutations; ++i){
      unsigned randomIndex;
      randomIndex = 1 + rand() %( populationSize - 1);
      population[randomIndex].mutate();
    }

    if(gen % 10 == 0){
      cout<<" Generation "<<gen/10<<" : shortest path found "
        <<population[0].get_fitness_score()<<endl;
    }
    }

    double endTime = omp_get_wtime();
    time[thread] = endTime - startTime;
    speedUp[thread] = time[0]/time[thread];

    cout<<endl;
    cout<<"Time taken : "<<time[thread]<<endl;
    cout<<endl;

    bestGenome = population[0]; 
    }

   //plotting speed up vs threads & time vs threads
    int i ;
    char * commandsForGnuplot1[] = {"set title \"Speed Up VS Threads\"", "plot 'ST.temp' with lines" };
    char * commandsForGnuplot2[] = {"set title \"Execution Time VS Threads\"",  "plot 'TT.temp' with lines"};
    FILE * temp1 = fopen("ST.temp", "w");
    FILE * temp2 = fopen("TT.temp", "w");

    FILE * gnuplotPipe1 = popen ("gnuplot -persistent", "w");
    FILE * gnuplotPipe2 = popen ("gnuplot -persistent", "w");
    for (i=0; i < 12; i++)
    {
    fprintf(temp1, "%d %f \n", threads[i], speedUp[i]); //Write the data to a temporary file
    fprintf(temp2, "%d %f \n", threads[i], time[i]); //Write the data to a temporary file
    }

    for (i=0; i < 2; i++)
    {
    fprintf(gnuplotPipe1, "%s \n", commandsForGnuplot1[i]); //Send commands to gnuplot one by one.
    fprintf(gnuplotPipe2, "%s \n", commandsForGnuplot2[i]); //Send commands to gnuplot one by one.
    }

  return bestGenome;
}

bool compare_paths(const PathRepresentation &A, const PathRepresentation &B){
  double fitnessA = A.get_fitness_score();
  double fitnessB = B.get_fitness_score();
  if(fitnessA < fitnessB)
    return true;
  else
    return false;
}

