//
// Created by janvsz on 04.02.2020.
//
#include"FunctionParser.h"
#include<iostream>
#include<string>
#include<regex>

namespace functionParser
{
    bool is_include(const std::string &line)
    {
        std::regex exp(R"(^\s*\#include\s)");
        return std::regex_match(line, exp);
    }

    std::string get_include(const std::string &line)
    {
        std::regex exp(R"([<\"][^>\"](\w+)[>\"]\\s*")");
        std::smatch match;
        if (std::regex_search(line.begin(), line.end(), match, exp))
            return match.str(1);
    }

    bool is_namespace(const std::string line)
    {
        std::regex pattern("namespace (\\w+)");

        return std::regex_match(line, pattern);
    }

    std::string get_namespace(const std::string line)
    {
        std::regex pattern("namespace (\\w+)");
        std::smatch match;
        std::regex_search(line, match, pattern);

        return match[1];
    }

    bool is_block_opening_bracket(const std::string &line)
    {
        std::regex exp(R"(\s*(\{))");
        return std::regex_match(line, exp);
    }

    bool is_block_closing_bracket(const std::string &line)
    {
        std::regex exp(R"(\s*(\}))");
        return std::regex_match(line, exp);
    }


    bool is_function_call(std::string line)
    {
        std::regex pattern("([\\:\\w]+)\\s*\\(");
        std::smatch match;

        return std::regex_search(line, match, pattern);
    }

    std::vector<std::string> get_function_calls(std::string line)
    {
        std::regex pattern("([\\.\\:\\w]+)\\s*\\(");
        std::smatch match;
        std::regex_search(line, match, pattern);

        std::regex str_pattern("\"(.*)\"");
        line = std::regex_replace(line, str_pattern, "\"\"");

        std::vector<std::string> calls;
        while (std::regex_search(line, match, pattern))
        {
            std::regex sub_pattern("\\.");
            std::smatch dot_match;
            std::string function_match = match[1];

            line = match.suffix().str();

            if (!std::regex_search(function_match, dot_match, sub_pattern))
            {
                calls.push_back(function_match);
            }
        }

        return calls;
    }

    bool is_function_header(std::string line)
    {
        std::regex pattern("^[\\s\\w\\<\\>\\*\\:]+\\s(\\w+)\\s*\\(");
        std::smatch match;

        return std::regex_search(line, match, pattern);
    }

    std::string get_function_header(std::string line)
    {
        std::regex pattern("^[\\s\\w\\<\\>\\*\\:]+\\s(\\w+)\\s*\\(");
        std::smatch match;
        std::regex_search(line, match, pattern);

        return match[1];
    }

    std::string get_file_path_base_from_cpp(std::string filePath)
    {
        std::regex pattern("^(\\.\\\\(\\w+\\\\)*\\w+)\\.cpp");
        std::smatch match;
        std::regex_search(filePath, match, pattern);

        return match[1];
    }
}
