#ifndef UNIFORM_PARTIALLY_MAPPED_CROSSOVER_H
#define UNIFORM_PARTIALLY_MAPPED_CROSSOVER_H
/*
 * @file Crossover/partially_mapped_crossover.hpp
 * @author Shah Anwaar Khalid
 *
 * This class implements partially_mapped_crossover between
 * two genomes, given their path representation.
 */

#include "crossover_base.hpp"

class UniformPartiallyMappedCrossover : public Crossover {

  public:
    
    //! Constructor
    UniformPartiallyMappedCrossover(){};

    //! Destructor
    ~UniformPartiallyMappedCrossover(){};

    //! Crossover function
    std::pair<PathRepresentation, PathRepresentation>
      crosslink(const PathRepresentation&A, const PathRepresentation& B);

};
#endif
