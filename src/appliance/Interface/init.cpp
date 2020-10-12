// ALG1-TP2 project appliance file
// Interface module
// init class
// ====================================
//
// Description:
// This class initializes the program, and calls procedures for
//   entry processing, and then sends the processed entries to
//   the program system manager, that is, the class ~manager~.
////////////////////////////////////////////////////////////////

#include "Interface/init.hpp"

#include "Interface/manager.hpp"
#include "Utils/error.hpp"

#include <iostream>
#include <fstream>
#include <vector>

namespace Interface {

//:D
void init::m_process_entries(int p_argc, char** p_argv)
{
	std::cerr << "Processing entries..." << std::endl;
	const int k_min_args = 2, k_max_args = 3;

	// Check argc
	if (p_argc < k_min_args || p_argc > k_max_args) {
		throw wrong_argc("Program usage: $PROGRAM $TEST_FILE");
	}

	// Initialize our weights string
	// Check entry in argv[1]'s format
	char* test_file_name = p_argv[1];

	std::cerr << "Test file = " << test_file_name << std::endl;

	std::fstream test_file(test_file_name, std::fstream::in);
	
	if (!test_file) 
		throw std::invalid_argument(std::string("Unable to open entry file ")
																+= test_file_name);

	// Defining m_num_diamonds
	char t_peek = 0; // Aux peek char
	int num_diamonds = 0; // Necessary for checking >= 0
	
	// In case number of diamonds is not provided
	t_peek = test_file.peek();
	if (t_peek == '\n' || t_peek == EOF)
		throw std::runtime_error("Malformed entry file.");

	test_file >> num_diamonds;
	if (num_diamonds >= 0)
		m_num_diamonds = num_diamonds;
	else
		throw std::runtime_error("Negative number of diamonds...");

	// Initializing m_weights to expect m_num_diamonds values
	m_weights = new std::vector<unsigned int>(m_num_diamonds);

	// Here, we reutilize the variable num_diamonds
	unsigned int i = 0;
	int aux_int = 0; // To help check validity of entries
	while(i < m_num_diamonds && test_file.good()) {
		// Checking if it is a digit
		if (!std::isdigit(test_file.peek()))
			test_file >> aux_int;
		else
			throw std::runtime_error("Non-digit character provided");

		// Checking if diamond weight is positive
		if (aux_int >= 0)
			m_weights->at(i) = aux_int;
		else
			throw std::runtime_error("Negative diamond weight provided");
		i++;
	}

	if (test_file.bad() || test_file.fail())
		throw std::runtime_error("Something went wrong in file reading");

	t_peek = test_file.peek();
	if (t_peek != EOF && t_peek != '\n')
		throw std::runtime_error("Wrong number of weights provided");

	test_file.close();

	std::cerr << "Processed entries..." << std::endl;
}

//:D
// Process entries, and send them to the algorithm manager.
init::init(int p_argc, char** p_argv)
{
	std::cerr << "Entering init" << std::endl;
	m_weights = nullptr;
	m_num_diamonds = 0;
	try {
		// Changes m_weights and m_num_diamonds
		m_process_entries(p_argc, p_argv);
	}
	catch (wrong_argc& e) {
		Utils::error(e, "Fatal");
		return;
	}
	catch (std::runtime_error& e) {
		Utils::error(e, "Fatal");
		return;
	}

	// Setting algorithm to be used
	std::string alg_mode;
	// Checking argc
	if (p_argc != 3)
		alg_mode = "brute";
	else
		alg_mode = p_argv[2];
	std::cerr << "alg_mode = " << alg_mode << std::endl;

	manager{m_weights, alg_mode};

	std::cerr << "Leaving init" << std::endl;
}

//:D
init::~init()
{
	std::cerr << "Destroying init" << std::endl;

	if (m_weights != nullptr) {
		m_weights->clear();
		delete m_weights;
	}
}

}
