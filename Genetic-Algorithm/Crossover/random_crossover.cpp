#include "random_crossover.hpp"
#include "../Path_representation.hpp"
#include <cstdlib>
#include <vector>
#include <set>

using std::vector;
using std::set;
using std::pair;

pair<PathRepresentation, PathRepresentation> RandomCrossover::
      crosslink(const PathRepresentation &A, const PathRepresentation &B) {
  vector<int> pathA = A.get_order();
  vector<int> pathB = B.get_order();
  vector<int> offspring1, offspring2 ;

  set<int> keepTrack1, keepTrack2;

  size_t numPoints = pathA.size();

  // Generate a random index in the range[2, . . ., numPoints -2]
  unsigned randomIndex1 = (rand() % (numPoints - 3)) + 2;
  unsigned randomIndex2 = (rand() % (numPoints - 3)) + 2;

  for(unsigned i = 0 ; i < randomIndex1; ++i)
  {
    offspring1.push_back(pathA.at(i));
    keepTrack1.insert(pathA.at(i));
  }

  for(unsigned i = 0 ; i < randomIndex2; ++i)
  {
    offspring2.push_back(pathB.at(i));
    keepTrack2.insert(pathB.at(i));
  }

  //crosslinking

  for(const auto &point: pathB ){
    bool found = keepTrack1.find(point)!= keepTrack1.end();
    if(!found){
        offspring1.push_back(point);
    }
  }

  for(const auto &point: pathA ){
    bool found = keepTrack2.find(point)!= keepTrack2.end();
    if(!found){
        offspring2.push_back(point);
    }
  }

  PathRepresentation Offspring1(offspring1);
  PathRepresentation Offspring2(offspring2);
  return pair{Offspring1, Offspring2};
}
