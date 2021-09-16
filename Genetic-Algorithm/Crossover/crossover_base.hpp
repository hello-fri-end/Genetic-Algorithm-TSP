#ifndef CROSSOVER_BASE_H
#define CROSSOVER_BASE_H

/*
 * @file Crossover/crossover_base.hpp
 * @author Shah Anwaar Khalid
 *
 * This abstract class represents a crossover between two genomes,
 * given their path represenation.
 */

// Forward Declaration of PathRepresentation Class.
class PathRepresentation;

#include <utility>

class Crossover{
  public:
    //! Constructor
    Crossover() {};
    
    //! Destructor
    ~Crossover() {};

    //! Performs crossover of two genomes
    virtual std::pair<PathRepresentation, PathRepresentation> crosslink
           (const PathRepresentation &A, const PathRepresentation & B)  = 0;
};

#endif
