#ifndef RANDOM_CROSSOVER_H
#define RANDOM_CROSSOVER_H

/*
 * @file Crossover/random_crossover.hpp
 * @author Shah Anwaar Khalid
 *
 * This class represents random_crossover between two genomes,
 * given their path representation.
 */

#include "crossover_base.hpp"

class RandomCrossover : public Crossover {

  public:

    //! Constructor
    RandomCrossover() {};

    //! Destructor
    ~RandomCrossover() {};

    //! Crossover function
    PathRepresentation crosslink(const PathRepresentation &A, const PathRepresentation &B);
};

#endif
