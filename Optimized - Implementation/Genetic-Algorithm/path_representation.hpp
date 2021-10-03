/*
 * @file Genetic/Path_representation.h
 * @author Shah Anwaar Khalid
 *
 * The class represents path representation of a genome.
 */

#ifndef PATH_REPRESENTATION_H
#define PATH_REPRESENTATION_H

#include "../Point/point.hpp"
#include "Crossover/crossover_base.hpp"
#include <vector>
#include <cstdlib>

//class Crossover;
class PathRepresentation {

  public:
    //! Constructors

    /*
     * Takes the number of points that will be visited
     * & generates a random order to visit those points.
     */
    PathRepresentation(const int numPoints);

    /*
     * Initializes the genome from the specified visit order.
     */

    PathRepresentation(const std::vector<int> &order);

    //! Destructor
    ~PathRepresentation();

    //! Fitness Score
    double fitness_score(const std::vector<std::vector<double>>& distances);

    //! Mutate the gene
    void mutate();

    //! Order of visitation
    std::vector<int> get_order() const;

    //! Returns the fitness score
    double get_fitness_score() const;

  private:
    std::vector<int> genome;
    double fitnessScore;

};

PathRepresentation run_genetic_algorithm( const std::vector<Point>&points,
                                          Crossover* CrossoverObject,
                                          size_t populationSize, size_t numGenerations,
                                          size_t keepPopulation, size_t numMutations);

bool compare_paths(const PathRepresentation& A, const PathRepresentation &B);

void insert_sorted(std::vector<PathRepresentation>& population,
                   const PathRepresentation &offpsring,
                   size_t end);
#endif
