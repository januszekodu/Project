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

    FunctionDependency parse(std::string, const std::vector<std::string> &);

    void parseNamespace(std::string, std::ifstream &, FunctionDependency &, const std::vector<std::string> &);
    std::vector<std::string> parseFunction(std::ifstream &, const std::vector<std::string> &, std::string namespaceName = "");
    bool is_header_file(std::string);

    std::vector<std::string> get_function_headers(std::string);

    std::vector<std::string> filter_header_files(std::vector<std::string>);

    FunctionDependency parseMain(std::string, const std::vector<std::string> &);
}

#endif // FUNCTION_DEPENDENCY_MORZECHOWSKI_INCLUDED
