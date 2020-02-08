#ifndef FUNCTION_DEPENDENCY_MORZECHOWSKI_INCLUDED
#define FUNCTION_DEPENDENCY_MORZECHOWSKI_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "FunctionParser.h"

namespace functionParser
{
    typedef std::map<std::string, std::vector<std::string>> FunctionDependency;

    FunctionDependency parse(std::string);
    void parseNamespace(std::string, std::ifstream &, FunctionDependency &);
    std::vector<std::string> parseFunction(std::ifstream &, std::string namespaceName = "");
}

#endif // FUNCTION_DEPENDENCY_MORZECHOWSKI_INCLUDED
