#ifndef FINALPARSER_PARSER_H
#define FINALPARSER_PARSER_H
#pragma once
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <map>
#include <vector>

namespace fileParse
{

    typedef std::map<std::string, std::vector<std::string>> FileMap;
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

    void searchInFile(std::string const &fileName, std::map<std::string, std::vector<std::string>> &fileConnectionMap);

    FileMap parse(std::vector<std::string> listOfFiles);

    void cleanMap(FileMap &fileMap);

}
#endif //FINALPARSER_PARSER_H