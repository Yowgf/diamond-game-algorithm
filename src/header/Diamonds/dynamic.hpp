// ALG1-TP2 project header file
// Diamonds module
// dynamic algorithm class
// ====================================
//
// Description:
// This class implements the algorithm for finding the minimum
//   diamond waste possible in a sequence of cuts, using a
//   dynamic programming algorithm aproach.
////////////////////////////////////////////////////////////////

#ifndef DYNAMIC_H
#define DYNAMIC_H 1

#include "Diamonds/Diamonds_cg.hpp"

namespace Diamonds {

class dynamic {
private:
	// Pre-processing
	// Input:  pointer to unsorted vector of weights
	// Sorting is performed inline
	static void insertion_sort(wvec*);

	// Input:  pointer to increasingly ordered vector of weights
	// Output: pointer to bucketed list of weights
	static wbuckets* bucketized(wvec*);

	// Messing with the buckets (actually cutting the diamonds)
	// Input:  bucketized weights
	// Output: minimum weight through diamond cutting
	static weight cut_diamonds(wbuckets*);
public:
	// Input:  pointer to vector containing weights
	// Output: minimum final weight
	static weight run(wvec* p_weights);


};

}

#endif
