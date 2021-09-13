#include "random_crossover.hpp"
#include "../Path_representation.hpp"
#include <cstdlib>
#include <vector>
#include <set>

using std::vector;
using std::set;

PathRepresentation RandomCrossover::crosslink(const PathRepresentation &A,
                                               const PathRepresentation &B) {
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
