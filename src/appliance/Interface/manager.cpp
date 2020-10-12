// ALG1-TP2 project appliance file
// Interface module
// manager class
// ====================================
//
// Description:
// Calls and supervises the running and processing of in/out ops
//   of the algorithm from ~Diamonds~ module.
////////////////////////////////////////////////////////////////

#include "Interface/manager.hpp"

#include "Diamonds/Diamonds.hpp" // Algorithms module

#include <iostream>

namespace Interface {

// Private members

//:D
void manager::print_result()
{
	std::cout << m_alg_ret << '\n';
}

// Public members

//:D
manager::manager(std::vector<unsigned int>* p_entries,
                 const std::string& p_mode)
{
	std::cerr << "Entering manager" << std::endl;

	// Printing weights (guarantee of good argument)
	if(p_entries != nullptr) {
		std::vector<unsigned int>::iterator it = p_entries->begin();
		while (it != p_entries->end()) {
			std::cerr << std::to_string(*it) << ' ';
			it++;
		}
		std::cerr << '\n';
	}

	// Choosing algorithm
	if (!p_mode.compare("Brute"))
		m_alg_ret = Diamonds::brute_force(p_entries);
	else
		m_alg_ret = Diamonds::dynamic(p_entries);

	std::cerr << "Result is:" << "\n\n";

	print_result();

	std::cerr << '\n';

	std::cerr << "Leaving manager" << std::endl;
}

//:D
unsigned int manager::get_alg_ret()
{
	return m_alg_ret;
}

}
