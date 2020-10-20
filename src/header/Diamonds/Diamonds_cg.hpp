// ALG1-TP2 project header file
// Diamonds module
// Diamonds common ground definitions
// ====================================
//
// Description:
// Diamonds module common ground definitions
////////////////////////////////////////////////////////////////

#ifndef DIAMONDS_CG_H
#define DIAMONDS_CG_H 1

#include <list>
#include <tuple>
#include <vector>

namespace Diamonds {

const unsigned int k_max_diams = 256;
const unsigned int k_max_weight = 128;

typedef unsigned int weight;
typedef std::pair<weight, unsigned int> bucket;
typedef std::list<bucket*> wbuckets;
typedef std::vector<weight> wvec;

}

#endif
