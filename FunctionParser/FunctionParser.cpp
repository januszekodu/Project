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
        std::regex exp((R"([<\"][^>\"](\w+)[>\"]\\s*")"));
        std::smatch match;
        if (std::regex_search(line.begin(), line.end(), match, exp))
            return match.str(1);
    }

    bool is_namespace(const std::string &line)
    {
        std::regex exp(R"(^(namespace)\s.*)");
        return std::regex_match(line, exp);
    }

    std::string get_namespace(const std::string &line)
    {
        std::regex exp(R"(.*\s(\w+)$)");
        std::smatch match;
        if (std::regex_search(line.begin(), line.end(), match, exp))
            return match.str(1);
    }

    bool is_function_header(const std::string& line)
    {
        std::regex exp(R"(.*\s\w+(\((.*)\)\;?)");
        return std::regex_match(line, exp);
    }

    std::string get_function_header(const std::string &line)
    {
        std::regex exp(R"(.*\s*(\w+)\((.*)\)\;?)");
        std::smatch match;
        if (std::regex_search(line.begin(), line.end(), match, exp))
            return match.str(1);
    }

    bool is_function_call(const std::string &line)
    {
        std::regex exp(R"((return|=)\s(\w+)\(.*\)\;?)");
        return std::regex_match(line, exp);
    }

    std::string get_function_call(const std::string &line)
    {
        std::regex exp(R"((return|=)\s(\w+)\(.*\)\;?)");
        std::smatch match;
        if (std::regex_search(line.begin(), line.end(), match, exp))
            return match.str(2);
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
}
