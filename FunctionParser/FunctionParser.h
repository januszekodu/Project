//
// Created by janvsz on 04.02.2020.
//

#ifndef IO_PROJECT_2_FUNCTIONPARSER_H
#define IO_PROJECT_2_FUNCTIONPARSER_H
#include<string>


namespace functionParser
{
    bool is_include(std::string);

    std::string get_include(std::string);

    bool is_namespace(std::string);

    std::string get_namespace(std::string);

    bool is_function_header(std::string);

    std::string get_function_header(std::string);

    bool is_function_call(std::string);

    std::string get_function_call(std::string);

    bool is_block_opening_bracket(std::string);

    bool is_block_closing_bracket(std::string);
}
#endif //IO_PROJECT_2_FUNCTIONPARSER_H