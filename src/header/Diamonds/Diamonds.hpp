// ALG1-TP2 project header file
// Diamonds module
// Diamonds library
// ====================================
//
// Description:
// This file includes all the header files inside ~Diamonds~
//   module, for easy access to the whole module.
// Also, implements algorithms.
////////////////////////////////////////////////////////////////

#ifndef DIAMONDS_H
#define DIAMONDS_H 1

#include <vector>

namespace Diamonds {

// Algorithm using brute-force, for the sake of comparison
unsigned int brute_force(std::vector<unsigned int>* p_weights);

// Algorithm using dynamic programming paradigm
unsigned int dynamic(std::vector<unsigned int>* p_weights);

}

#endif
