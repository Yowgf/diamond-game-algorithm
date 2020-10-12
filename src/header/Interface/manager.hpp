// ALG1-TP2 project header file
// Interface module
// manager class
// ====================================
//
// Description:
// Calls and supervises the running and processing of in/out ops
//   of the algorithm from ~Diamonds~ module.
////////////////////////////////////////////////////////////////

#ifndef MANAGER_H
#define MANAGER_H 1

#include <string>
#include <vector>

namespace Interface {

class manager {
private:
	unsigned int m_alg_ret; // Algorithm return value

	// Prints output of the program to std::cout
	void print_result();
public:
	// Algorithm manager
	manager(std::vector<unsigned int>*, const std::string& p_mode);

	unsigned int get_alg_ret();
};

}

#endif
