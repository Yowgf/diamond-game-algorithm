// ALG1-TP2 project header file
// Diamonds module
// brute-force algorithm class
// ====================================
//
// Description:
// This class implements the algorithm for finding the minimum
//   diamond waste possible in a sequence of cuts, using a brute
//   force aproach.
////////////////////////////////////////////////////////////////

#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H 1

#include <list>
#include <vector>

namespace Diamonds {

class brute_force {
private:
	static void find_min(std::vector<unsigned int>&);

public:
	static std::list<unsigned int> final_weights;
	// Receives vector containing weights, and returns minimum
	//   final weight.
	static unsigned int run(std::vector<unsigned int>* p_weights);

};

}

#endif
