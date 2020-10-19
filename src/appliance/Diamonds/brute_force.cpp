// ALG1-TP2 project appliance file
// Diamonds module
// brute-force algorithm class
// ====================================
//
// Description:
// This class implements the algorithm for finding the minimum
//   diamond waste possible in a sequence of cuts, using a brute
//   force aproach.
////////////////////////////////////////////////////////////////

#include "Diamonds/brute_force.hpp"

#include <climits>
#include <cmath>
#include <iostream>
#include <string>

namespace Diamonds {

std::list<unsigned int> brute_force::final_weights = std::list<unsigned int>();

//:D
// Auxiliary function that finds possible minimuns
void brute_force::find_min(std::vector<unsigned int>& p_weights)
{
	/*std::cerr << "Entering brute_force::find_min" << std::endl;
	std::cerr << "Printing input from find_min" << std::endl;
	// Printing weights (guarantee of good argument)
	if(!p_weights.empty()) {
		std::vector<unsigned int>::iterator it = p_weights.begin();
		while (it != p_weights.end()) {
			std::cerr << std::to_string(*it) << ' ';
			it++;
		}
		std::cerr << '\n';
	}
	*/
	// Stopping point
	if(p_weights.size() == 2) {
		final_weights.push_back(abs(p_weights.at(0) - p_weights.at(1)));
		return;
	}


	// Recursive calls
	unsigned int i = 0, j = 0, k = 0;
	unsigned int orgsize = p_weights.size();
	unsigned int subsize = orgsize - 1;
	// Weights passed into recursive calls
	std::vector<unsigned int> sub_weights(subsize);
	
	// Choose diamonds i and j
	// i stays, and j is consumed
	for (i = 0; i < subsize; i++) {
		for (j = i + 1; j < subsize; j++) {
			// Walk through sub_weights, to fill it
			for (k = 0; k < i; k ++)
				sub_weights.at(k) = p_weights.at(k);
			// Here, k = i
			sub_weights.at(k) = abs(p_weights.at(k) - p_weights.at(j));
			for (k++; k < j; k++)
				sub_weights.at(k) = p_weights.at(k);
			// Here, k = j
			// Jump that position and continue
			for (k++; k < orgsize; k++)
				sub_weights.at(k - 1) = p_weights.at(k);
			find_min(sub_weights);
		}
	}
	
	//std::cerr << "Leaving brute_force::find_min" << std::endl;
}

//:D
// Uses brute force to test all the possible configurations, and
//   choose the one that minimizes the final weight.
// Concretely, builds a decision tree and chooses the leaf with
//   minimum key.
unsigned int brute_force::run(std::vector<unsigned int>* p_weights)
{
	std::cerr << "Entering brute_force algorithm" << std::endl;
	
	if(p_weights == nullptr)
		throw std::invalid_argument("Diamonds::brute_force p_weights nullptr");


	// Produce each possible final weight and store in final_weights
	find_min(*p_weights); // stores in final_weights

	// Find the minimum one
	unsigned int min_weight = ULONG_MAX; // Current minimum
	std::list<unsigned int>::iterator it = final_weights.begin();
	for(; it != final_weights.end(); it++) {
		if(*it < min_weight)
			min_weight = *it;
	}

	std::cerr << "Finished brute_force algorithm" << std::endl;
	return min_weight;
}

}
