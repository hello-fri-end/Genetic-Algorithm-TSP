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
double PathRepresentation::fitness_score(const vector<vector<double>> &distances) {
  size_t numPoints = genome.size();

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
  // Generate an initial population of random genes
  vector<PathRepresentation> population;
  size_t numPoints = points.size();

  // Store the distances betweeen points
  // to avoid repetetive calculations.
  vector<vector<double>>distances(numPoints, vector<double>(numPoints));

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

  // sort the genomes by fitness.
  std::sort(population.begin(), population.end(), compare_paths);

  for(unsigned gen = 0; gen < numGenerations * 10; ++gen) {
    // sort the genomes by fitness.
    // no longer needed since we'll use insertion sort
    // to insert offsprings into the population
    //std::sort(population.begin(), population.end(), compare_paths);

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

      // Get the fitness score of both the springs 
      // & choose the fitter one.
      offsprings.first.fitness_score(distances);
      offsprings.second.fitness_score(distances);

      if (compare_paths(offsprings.first, offsprings.second) )
        insert_sorted(population, offsprings.first, i);
      else
        insert_sorted(population, offsprings.second, i);
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

void insert_sorted(vector<PathRepresentation>& population,
                   const PathRepresentation& offspring,
                   size_t end) {
  double offspringFitness = offspring.get_fitness_score();

  for(int i = 0; i < end; ++i)
  {
    if(offspringFitness <= population[i].get_fitness_score())
    {
      // offspring should be inserted at position i.
      // we have to shift the array to make space for it
      
      for(int j = end - 1; j >= i ; --j)
        population[j + 1] = population[j];

      population[i] = offspring;
      return ;
    }
  }
   if(offspringFitness < population[end].get_fitness_score() )
     population[end] = offspring;
}
