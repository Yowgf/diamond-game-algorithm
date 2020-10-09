// ALG1-TP2 project header file
// Utils module
// error class
// ============================
//
// Description:
// Class that implements errors found in the
//   project.
/////////////////////////////////////////////////

#include "Utils/error.hpp"

#include <iostream>

namespace Utils {

//:D
error::error(std::exception& e, const char* t_type)
{
	error(e, std::string(t_type));
}

//:D
error::error(std::exception& e, const std::string t_type)
{
	if(!t_type.compare("Fatal"))
		fatal_error(e);
	else {
		fatal_error(e = std::invalid_argument(std::string("Unknown error ") += t_type));
	}
}

//:D
void error::fatal_error(std::exception& e)
{
	std::cerr << std::endl << e.what() << std::endl;
	std::cerr << "Fatal error, terminating program..." << std::endl;
	exit(1);
}

}