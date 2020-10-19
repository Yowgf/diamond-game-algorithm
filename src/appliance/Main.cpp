// ALG1-TP2 project Main file
// Main function
// ============================
//
// Description:
// Direct interaction with the world outside of the program, and
//   transfers control to the most high-level ~Interface~ module
//   routine.
// Only simple parameter passing and exception handling is done
//   in the main function.
////////////////////////////////////////////////////////////////

#include "Diamonds/Diamonds.hpp"
#include "Interface/Interface.hpp"
#include "Utils/Utils.hpp"

#include <iostream>
#include <stdexcept>

//:D
int main(int argc, char** argv)
{
	std::cerr << "Program starting..." << std::endl;
	try {
		Interface::init(argc, argv);
	}
	// This is supposed to be handled inside init constructor
	catch(Interface::init::wrong_argc& e) {
		Utils::error(e, "Inst terminate");
	}
	// Unknown exception
	catch(std::exception& e) {
		Utils::error(e, "Inst terminate");
	}
	
	std::cerr << "Program terminated, error_code = ";
	std::cerr << Utils::error::error_code;
	std::cerr << std::endl;

	return Utils::error::error_code;
}
