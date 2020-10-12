// ALG1-TP2 project header file
// Interface module
// init class
// ====================================
//
// Description:
// This class initializes the program, and calls procedures for
//   entry processing, and then sends the processed entries to
//   the program system manager, that is, the class ~manager~.
////////////////////////////////////////////////////////////////

#ifndef INIT_H
#define INIT_H 1

#include <stdexcept>
#include <vector>

namespace Interface {

class init {
private:
	unsigned int m_num_diamonds;
	std::vector<unsigned int>* m_weights;
	
	// Defines m_num_diamonds and m_weights
	void m_process_entries(int p_argc, char** p_argv);

public:
	class wrong_argc : public std::invalid_argument {
	public:
		wrong_argc(const char* p_what) : std::invalid_argument(p_what) {};
	};

	init(int p_argc, char** p_argv);
	~init();
};

}

#endif
