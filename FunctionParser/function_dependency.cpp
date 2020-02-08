#include "FunctionParser.h"
#include "function_dependency.h"
#include <iostream>
#include <map>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;

namespace functionParser
{
    FunctionDependency parse(std::string filePath)
    {
            std::cout << "Processing file \"" << filePath << "\"..." << std::endl;

            std::ifstream file;

            FunctionDependency tmp;

            if (boost::algorithm::ends_with(filePath, ".h") || boost::algorithm::ends_with(filePath, ".hpp"))
            {
                return tmp;
            }

            file.open(filePath);

            if (!file.is_open())
            {
                std::cout << "\t[FAILED]" << std::endl;
                return tmp;
            }

            while (!file.eof())
            {
                std::string currentLine;
                std::getline(file, currentLine);

                if (is_namespace(currentLine))
                {
                    parseNamespace(get_namespace(currentLine), file, tmp);
                }

                if (is_function_header(currentLine))
                {
                    tmp.insert(std::pair<std::string, std::vector<std::string>>(get_function_header(currentLine), parseFunction(file)));
                }
            }

            file.close();

            return tmp;
    }

    void parseNamespace(std::string namespaceName, std::ifstream &file, FunctionDependency &dependencies)
    {
        int block_bracket_counter = 0;

        while (!file.eof())
        {
            std::string currentLine;
            std::getline(file, currentLine);

            if (is_block_opening_bracket(currentLine))
            {
                block_bracket_counter++;
            }

            if (is_block_closing_bracket(currentLine))
            {
                block_bracket_counter--;
            }

            if(block_bracket_counter == 0)
            {
                break;
            }

            if (is_function_header(currentLine))
            {
                dependencies.insert(std::pair<std::string, std::vector<std::string>>(
                    namespaceName + "::" + get_function_header(currentLine),
                    parseFunction(file, namespaceName)
                ));
            }
        }
    }

    std::vector<std::string> parseFunction(std::ifstream &file, std::string namespaceName)
    {
        int block_bracket_counter = 0;
        std::vector<std::string> function_calls;

        while (!file.eof())
        {
            std::string currentLine;
            std::getline(file, currentLine);

            if (is_block_opening_bracket(currentLine))
            {
                block_bracket_counter++;
            }

            if (is_block_closing_bracket(currentLine))
            {
                block_bracket_counter--;
            }

            if(block_bracket_counter < 1)
            {
                break;
            }

            if(is_function_call(currentLine))
            {
                std::string functionName = get_function_call(currentLine);
                functionName.insert(0, !namespaceName.empty() ? namespaceName + "::" : "");

                function_calls.push_back(functionName);
            }
        }

        return function_calls;
    }
}
