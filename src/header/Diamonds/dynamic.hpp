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

#include <vector>

namespace Diamonds {

class dynamic {
public:
	// Input:  pointer to vector containing weights
	// Output: minimum final weight
	static unsigned int run(std::vector<unsigned int>* p_weights);


};

}

#endif
