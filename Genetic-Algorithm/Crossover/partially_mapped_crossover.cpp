#include "partially_mapped_crossover.hpp"
#include "../Path_representation.hpp"
#include <vector>
#include <utility>
#include <cstdlib>

using std::vector;
using std::pair;


pair<PathRepresentation, PathRepresentation> PartiallyMappedCrossover::
      crosslink(const PathRepresentation &A, const PathRepresentation &B)
{

  vector<int> pathA = A.get_order();
  vector<int> pathB = B.get_order();

  vector<int> offspring1(pathA);
  vector<int> offspring2(pathB);

  unsigned numCities = std::min(pathA.size(), pathB.size());

  vector<int> partialMapA(numCities);
  vector<int> partialMapB(numCities);

  // Initilize the partialmaps
  for(unsigned i = 0 ; i < numCities; ++i)
  {
    partialMapA[pathA[i]] = i;
    partialMapB[pathB[i]] = i;
  }

  // Generate random crossover points
  unsigned randomIndex1;
  unsigned randomIndex2;
  do
  {
    randomIndex1 = rand() % (numCities);
    randomIndex2 = rand() % (numCities);
  }
  while(randomIndex1 >= randomIndex2);

  for(unsigned i = randomIndex1; i <= randomIndex2; ++i)
  {
    // selected values
    int temp1 = pathA[i];
    int temp2 = pathB[i];

    std::swap(offspring1[partialMapA[temp2]], offspring1[i]);
    std::swap(offspring2[partialMapB[temp1]], offspring2[i]);
  }

  PathRepresentation Offspring1(offspring1);
  PathRepresentation Offspring2(offspring2);

  return pair{Offspring2, Offspring1};
}
