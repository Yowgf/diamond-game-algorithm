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
#include <iostream>
#include <string>

namespace Diamonds {

// Static variables
wvec brute_force::final_weights = wvec(k_max_diams, ULONG_MAX);

//:D
// Auxiliary function that finds possible minimuns
void brute_force::find_min(wvec& p_weights)
{
	//std::cerr << "Entering brute_force::find_min" << std::endl;

	// Stopping point
	if(p_weights.size() == 2) {
		weight final_weight = 0;
		if (p_weights.at(0) > p_weights.at(1))
			final_weight = p_weights.at(0) - p_weights.at(1);
		else
			final_weight = p_weights.at(1) - p_weights.at(0);
		final_weights.at(final_weight) = final_weight;

		return;
	}

	// Recursive calls
	unsigned int i = 0, j = 0, k = 0;
	unsigned int orgsize = p_weights.size();
	unsigned int subsize = orgsize - 1;
	// Weights vector passed into recursive calls
	wvec sub_weights(subsize);

	// Choose diamonds i and j
	// i stays, and j is consumed
	for (i = 0; i < subsize; i++) {
		for (j = i + 1; j < orgsize; j++) {
			// Walk through sub_weights, to fill it
			for (k = 0; k < i; k ++)
				sub_weights.at(k) = p_weights.at(k);
			// Here, k = i
			// Put here abs(weight[i] - weight[j])
			if (p_weights.at(i) > p_weights.at(j))
				sub_weights.at(k) = p_weights.at(i) - p_weights.at(j);
			else
				sub_weights.at(k) = p_weights.at(j) - p_weights.at(i);
			for (k++; k < j; k++)
				sub_weights.at(k) = p_weights.at(k);
			// Here, k = j
			// Jump that position and continue
			for (; k < subsize; k++)
				sub_weights.at(k) = p_weights.at(k + 1);

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
weight brute_force::run(wvec* p_weights)
{
	std::cerr << "Entering brute_force algorithm" << std::endl;
	
	if(p_weights == nullptr)
		throw std::invalid_argument("Diamonds::brute_force p_weights nullptr");


	// Produce each possible final weight and store in final_weights
	find_min(*p_weights); // stores in final_weights

	// Find the minimum one
	weight min_weight = ULONG_MAX; // Current minimum
	auto it = final_weights.begin();
	for(; it != final_weights.end(); it++) {
		if(*it < min_weight)
			min_weight = *it;
	}

	std::cerr << "Finished brute_force algorithm" << std::endl;
	return min_weight;
}

}
