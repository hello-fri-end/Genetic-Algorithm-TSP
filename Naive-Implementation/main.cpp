#include "Point/point.hpp"
#include "Genetic-Algorithm/path_representation.hpp"
#include "Genetic-Algorithm/Crossover/crossover_base.hpp"
#include "Genetic-Algorithm/Crossover/random_crossover.hpp"
#include "Genetic-Algorithm/Crossover/partially_mapped_crossover.hpp"
#include "Genetic-Algorithm/Crossover/uniform_partially_mapped_crossover.hpp"
#include <iostream>
#include <cstdlib>  	// srand(), atoi()
#include <ctime> 		// time()
#include <getopt.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void help();


int main(int argc, char **argv) {


	// Parsing Arguments

	int populationSize, numGenerations,
			keepPopulation, numMutations;

	int c;

	while(1) {
		static struct option long_options[] = {
			{"population",	required_argument,	0,	'p'},
			{"generation",	required_argument,	0,	'g'},
			{"keep",	required_argument,	0,	'k'},
			{"mutation",	required_argument,	0,	'm'},
			{"help",		no_argument,	0,	'h'},
			{0, 0, 0, 0}
		};

		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "p:g:k:m:h",
                       long_options, &option_index);
		/* Detect the end of the options. */
    	if (c == -1)
    	break;

    	switch(c)
    		{
    		case 'p':
    			populationSize = atoi(optarg); break;
    		case 'g':
    			numGenerations = atoi(optarg); break;
    		case 'k':
    			keepPopulation = atoi(optarg); break;
    		case 'm':
    			numMutations = atoi(optarg); break;
    		case 'h':
    			help(); exit(0);
    		default :
    			abort ();
    		}
    	}

    if(argc != 9) {
    	help();
    }

	// Setting Input

	srand (unsigned (time (0)));

	int pointsNumber;
	double inputX, inputY, inputZ;
	vector<Point> pointsCluster;

	// Points Input

  //cout<<"Enter the number of cities:";
	cin >> pointsNumber;

	for(int i = 0; i < pointsNumber; i++) {
    //cout<<"Enter city co-ordinates: ";
		cin >> inputX >> inputY >> inputZ ;
		Point inputPoint {inputX, inputY, inputZ};
		pointsCluster.push_back(inputPoint);
		 
	}

	// Run Genetic Algorithm with random_crossover & partially_mapped_crossover
  RandomCrossover random_crosslink;
  PartiallyMappedCrossover pmc_crosslink;
  UniformPartiallyMappedCrossover upmc_crosslink;
  Crossover* CrossoverObject[3] = {&random_crosslink, &pmc_crosslink, &upmc_crosslink};
  

  for(unsigned i = 0 ; i < 3; ++i)
  {
    cout<<endl;
    if( i == 0)
      cout<<" Running Genetic Algorithm with Random Crossover"<<endl;
    else if (i == 1)
      cout<<" Running Genetic Algorithm with Partially Mapped Crossover"<<endl;
    else
      cout<<" Running Genetic Algorithm with Uniform Partially Mapped Crossover"<<endl;

    PathRepresentation bestGenome = run_genetic_algorithm(pointsCluster, CrossoverObject[i],
        populationSize,numGenerations,
        keepPopulation, numMutations);
    vector<int> shortestPathFound = bestGenome.get_order();
    double pathLength = bestGenome.get_fitness_score();

    cout << "Shortest Path Found : [";
    for(const auto& genome : shortestPathFound) {
      cout << " " << genome;
    }
    cout << "]\nLength is : " << pathLength << endl;
  }
	return 0;
}

void help() {
    	cout <<
    		"ALL OPTIONS ARE REQUIRED\n"
    		"where options are :\n"
    		"-p <value>, --population <value>\n"
    		"population is a positive integer specifying the population size.\n\n"

    		"-g <value>, --generation <value>\n"
    		"generations is a positive integer specifying how many generations to run the GA for.\n\n"

    		"-k <value>, --keep <value>\n"
    		"the number of the population that should be preserved from generation to generation.\n\n"

    		"-m <value>, --mutation <value>\n"
    		"specifies how many mutations to apply to each member of the population."

    		<< endl;
}
