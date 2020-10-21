// ALG1-TP2 project tester
// Time complexity
// ====================================
//
// Description:
// Measures time complexity of the algorithm.
// This file is adapted for a windows cmd shell.
////////////////////////////////////////////////////////////////

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

const unsigned int kmax_ndiamonds = 500000;
unsigned int diam_step   = 10000; // Create file for 0, diam_step, 2diam_step, ...
const unsigned int kmax_sweight   = 128;
// Number of tests performed for each configuration
const unsigned int kmax_iterconf  = 10;

// Generate random entries ranging from 0 to kmax_ndiamonds 
//   diamonds, and kmax_sweight maximum weight. These weights
//   are distributed between the diamonds stochastically.
int main() {
	// For string manipulations
	std::stringstream ss;

	// For time measures
	clock_t t;

	std::fstream test_file;
	std::fstream output_csv;
	// Temporary test_file, created with a specific configuration
	std::string test_file_name("cur_test");
	std::string output_csv_name("times.csv");

	// Command to run the test
	std::string test_command((std::string("tp2.exe ") += test_file_name) += " >nul 2>&1");
	// Command to delete the test file
	std::string del_command(std::string("del ") += test_file_name);

	std::cerr << "Test command = " << test_command << std::endl;

	output_csv.open(output_csv_name.c_str(), std::fstream::out | std::fstream::trunc);
	if(!output_csv.is_open())
		throw std::runtime_error("Unable to open file");

	// Initializing random number generator
	srand(time(NULL));

	unsigned int n_diamonds  = 0;
	unsigned int cur_weight = 0; // This is decided randomly for every diamond
	register unsigned int i = 0; // iterating variable
	// Now, create all the possibilities (0 to kmax_ndiamonds)
	for (n_diamonds = 0; n_diamonds < kmax_ndiamonds; n_diamonds += diam_step) {
		
		// Open test file
		test_file.open(test_file_name.c_str(), std::fstream::out | std::fstream::trunc);
		if (!test_file)
			throw std::runtime_error(std::string("Unable to open test_file ") += test_file_name);

		// Setup configuration
		
		// Write configuration into test file
		// First, the number of diamonds
		test_file << n_diamonds << '\n';
		// Then, the diamonds weight
		
		for (i = 0; i < n_diamonds; i++) {
			cur_weight = rand() % kmax_sweight + 1; // 1 to 128
			test_file << cur_weight << ' ';
		}
		test_file << '\n';

		// Now, the test file is ready for being used for testing
		// So close it and send it to the executable
		test_file.close();

		std::cerr << "Testing for " << n_diamonds << " diamonds..." << std::endl;
		t = clock();
		for (i = 0; i < kmax_iterconf; i++) {
			system(test_command.c_str());
		}
		t = clock() - t;

	
		// Write the mean time per configuration to csv file
		output_csv << (int)(((float)t) / kmax_iterconf);
		
	}

	if (test_file.is_open())
		test_file.close();

	if (output_csv.is_open())
		output_csv.close();

	system(del_command.c_str());

	return 0;
}
