#include "random_crossover.hpp"
#include "../path_representation.hpp"
#include <cstdlib>
#include <vector>
#include <set>
#include<iostream>
extern "C"
{
#include<omp.h>
}
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
  vector<bool> mask1(numPoints, true);
  vector<bool> mask2(numPoints, true);

  unsigned i;
//#pragma omp parallel for private(i, keepTrack1, keepTrack2, pathA, pathB)
  for( i = 0; i < numPoints; ++i)
  {
    if(keepTrack1.find(pathB[i]) == keepTrack1.end())
      mask1[i] = false;

    if(keepTrack2.find(pathA[i]) == keepTrack2.end())
      mask2[i] = false;
  }


  for(i = 0 ; i < numPoints; ++i)
  {
    if(!mask1[i])
      offspring1.push_back(pathB[i]);

    if(!mask2[i])
      offspring2.push_back(pathA[i]);
  }
//  for(auto it: offspring1)
//    std::cout<<it<<" ";
//  std::cout<<std::endl;
//  std::cout<<std::endl;
//
  PathRepresentation Offspring1(offspring1);
  PathRepresentation Offspring2(offspring2);
  return pair{Offspring1, Offspring2};
}
