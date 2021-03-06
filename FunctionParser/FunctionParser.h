//
// Created by janvsz on 04.02.2020.
//

#ifndef IO_PROJECT_2_FUNCTIONPARSER_H
#define IO_PROJECT_2_FUNCTIONPARSER_H
#include<string>
#include<vector>


namespace functionParser
{
    bool is_include(const std::string &);

    std::string get_include(const std::string &);

    bool is_namespace(const std::string);

    std::string get_namespace(const std::string);

    bool is_block_opening_bracket(const std::string &);

    bool is_block_closing_bracket(const std::string &);

    bool is_block_closing_bracket(const std::string &);

    bool is_function_header(std::string);
    std::string get_function_header(std::string);

    bool is_function_call(std::string);
    std::vector<std::string> get_function_calls(std::string);
    bool has_namespace(std::string);
    std::string get_file_path_base_from_cpp(std::string);
}
#endif //IO_PROJECT_2_FUNCTIONPARSER_H
