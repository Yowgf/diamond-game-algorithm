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

#include <stdexcept>

#ifndef MAIN_APP
#define MAIN_APP 1

int main(int argc, char** argv)
{
	try {
		Interface::init(argc, argv);
	}
	catch(std::exception& e) {
		Utils::error(e, "Fatal");
	}

	return 0;
}

#endif
