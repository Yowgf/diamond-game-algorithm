// ALG1-TP2 project header file
// Utils module
// error class
// ============================
//
// Description:
// Class that implements errors found in the
//   project.
/////////////////////////////////////////////////

#ifndef ERROR_H
#define ERROR_H 1

#include <stdexcept>
#include <string>

namespace Utils {

class error {
private:
	void fatal_error(std::exception&);

public:
	error(std::exception&, const char*);
	error(std::exception&, const std::string);
};

}

#endif
