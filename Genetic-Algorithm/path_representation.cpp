#include "path_representation.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>

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
double PathRepresentation::fitness_score(const vector<Point> &points) {
  size_t numPoints = genome.size();

  for(size_t i = 0, j = 1; i < numPoints -1; ++i, ++j)
    fitnessScore += points[genome.at(i)].distance_to(points[j]);

  // TS has to go back to the startting position.
  fitnessScore+= points[genome.front()].distance_to(points.back());

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
  // Generate an initial population of random genes
  vector<PathRepresentation> population;
  size_t numPoints = points.size();
  
  for(unsigned i = 0 ; i < populationSize; ++i) {
    PathRepresentation genome(numPoints);
    population.push_back(genome);
  }

  for(unsigned gen = 0; gen < numGenerations * 10; ++gen) {
    
    // Compute fitness score of each genome.
    for(PathRepresentation& genome:population){
      genome.fitness_score(points);
    }

    // sort the genomes by fitness.
    std::sort(population.begin(), population.end(), compare_paths);

    // Keep the top N fittest memebrs of the population &
    // replace the remaining memebrs with new genomes produced
    // by crosslinking.

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

      if (compare_paths(offsprings.first, offsprings.second) )
        population[i] = offsprings.first;
      else
        population[i] = offsprings.second;
    }

    //Mutate random genes
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
  return population[0];
}

bool compare_paths(const PathRepresentation &A, const PathRepresentation &B){
  double fitnessA = A.get_fitness_score();
  double fitnessB = B.get_fitness_score();
  if(fitnessA < fitnessB)
    return true;
  else
    return false;
}
