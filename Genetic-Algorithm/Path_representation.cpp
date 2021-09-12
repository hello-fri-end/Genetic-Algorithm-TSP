#include "Path_representation.hpp"
#include <iostream>
#include <algorithm>
#include <set>
#include <cstdlib>

using std::vector;
using std::set;
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

PathRepresentation cyclic_crossover(const PathRepresentation& A, const PathRepresentation& B)
{
/* To be implemented*/
}

PathRepresentation random_crossover(const PathRepresentation& A, const PathRepresentation& B)
{
  vector<int> pathA = A.get_order();
  vector<int> pathB = B.get_order();
  vector<int> offspring ;
  set<int> keepTrack;

  size_t numPoints = pathA.size();

  // Generate a random index in the range[2, . . ., numPoints -2]
  unsigned randomIndex = (rand() % (numPoints - 3)) + 2;

  for(unsigned i = 0 ; i < randomIndex; ++i)
  {
    offspring.push_back(pathA.at(i));
    keepTrack.insert(pathA.at(i));
  }

  //crosslinking

  for(const auto &point: pathB ){
    bool found = keepTrack.find(point)!= keepTrack.end();
    if(!found){
        offspring.push_back(point);
    }
  }

  PathRepresentation Offspring(offspring);
  return Offspring;
}


