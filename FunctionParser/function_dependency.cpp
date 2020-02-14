#include "FunctionParser.h"
#include "function_dependency.h"
#include <iostream>
#include <map>
#include <regex>
#include <boost/algorithm/string/predicate.hpp>

namespace functionParser
{
    std::vector<std::string> get_function_headers(std::string filePath)
    {
        std::ifstream headerFile;

        headerFile.open(filePath);

        std::string namespaceName;
        std::vector<std::string> functions;

        while (!headerFile.eof())
        {
            std::string line;
            std::getline(headerFile, line);

            if (is_namespace(line))
            {
                namespaceName = get_namespace(line);
            }

            if (is_function_header(line))
            {
                functions.push_back(namespaceName + "::" + get_function_header(line));
            }
        }

        return functions;
    }


    std::vector<std::string> functionHeaders;

    FunctionDependency parse(std::string filePath, const std::vector<std::string> &allFunctionHeaders)
    {
            std::ifstream file;

            FunctionDependency functionDependency;

            if (is_header_file(filePath))
            {
                return functionDependency;
            }

            if (filePath == ".\\main.cpp")
            {
                return parseMain(filePath, allFunctionHeaders);
            }

            std::string headerFilePath = get_file_path_base_from_cpp(filePath) + ".h";
            functionHeaders = get_function_headers(headerFilePath);
            file.open(filePath);

            if (!file.is_open())
            {
                return functionDependency;
            }

            while (!file.eof())
            {
                std::string currentLine;
                std::getline(file, currentLine);

                if (is_namespace(currentLine))
                {
                    parseNamespace(get_namespace(currentLine), file, functionDependency, allFunctionHeaders);
                }

                if (is_function_header(currentLine))
                {
                    functionDependency.insert(std::pair<std::string, std::vector<std::string>>(get_function_header(currentLine), parseFunction(file, allFunctionHeaders)));
                }
            }

            file.close();

            return functionDependency;
    }

    void parseNamespace(std::string namespaceName, std::ifstream &file, FunctionDependency &dependencies, const std::vector<std::string> &allFunctionHeaders)
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
                for (std::string fun : functionHeaders)
                {
                    std::string thisFun = namespaceName + "::" + get_function_header(currentLine);

                    if (thisFun == fun)
                    {
                        std::vector<std::string> functionCalls = parseFunction(file, allFunctionHeaders, namespaceName);

                        if (functionCalls.size() != 0)
                        {
                            dependencies.insert({thisFun, functionCalls});
                        }
                    }
                }
            }
        }
    }

    std::vector<std::string> parseFunction(std::ifstream &file, const std::vector<std::string> &allFunctionHeaders, std::string namespaceName)
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
                for (std::string call : get_function_calls(currentLine))
                {
                    if (!has_namespace(call) && !namespaceName.empty())
                    {
                        call = namespaceName+"::"+call;
                    }

                    for (std::string functionHeader : allFunctionHeaders)
                    {
                        if (functionHeader == call)
                        {
                            function_calls.push_back(call);

                            break;
                        }
                    }
                }
            }
        }

        return function_calls;
    }

    bool is_header_file(const std::string filePath)
    {
        return boost::algorithm::ends_with(filePath, ".h") || boost::algorithm::ends_with(filePath, ".hpp");
    }

    std::vector<std::string> filter_header_files(std::vector<std::string> filePaths)
    {
        std::regex pattern(".(h|hpp)$");
        std::smatch match;

        std::vector<std::string> headerFiles;

        for (std::string filePath : filePaths)
        {
            if (std::regex_search(filePath, match, pattern))
            {
                headerFiles.push_back(filePath);
            }

        }

        return headerFiles;
    }

    bool has_namespace(std::string functionName)
    {
        std::regex pattern("\\:\\:");
        std::smatch match;

        return std::regex_search(functionName, match, pattern);
    }

    FunctionDependency parseMain(std::string filePath, const std::vector<std::string> &allFunctionHeaders)
    {
        std::ifstream file;
        FunctionDependency tmp;
        file.open(filePath);

        std::vector<std::string> mainFunctionHeaders, allFunctionHeadersCloned;

        allFunctionHeadersCloned.insert(allFunctionHeadersCloned.end(), allFunctionHeaders.begin(), allFunctionHeaders.end());

        bool beforeMain = true;

        while (!file.eof())
        {
            std::string currentLine;
            std::getline(file, currentLine);

            if (is_function_header(currentLine))
            {
                std::string functionHeader = get_function_header(currentLine);

                if (beforeMain)
                {
                    if (functionHeader == "main")
                    {
                        beforeMain = false;
                    }

                    mainFunctionHeaders.push_back(functionHeader);
                    allFunctionHeadersCloned.push_back(functionHeader);

                    if (functionHeader != "main")
                    {
                        continue;
                    }
                }

                for (std::string fun : mainFunctionHeaders)
                {
                    if (functionHeader == fun)
                    {
                        std::vector<std::string> functionCalls = parseFunction(file, allFunctionHeadersCloned);

                        if (functionCalls.size() != 0)
                        {
                            tmp.insert({functionHeader, functionCalls});
                        }
                    }
                }
            }

        }

        return tmp;
    }
}
