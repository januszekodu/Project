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
    struct FileData
    {
        std::string name;
        int size;
        int edgePower=1;  //because in C++ we can't duplicate #include the same file
    };

    typedef std::map<std::string, std::vector<std::string>> FileMap;
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    typedef std::pair<std::vector<FileData>, FileMap> FilePair;

    void searchInFile(std::string const& fileName, FileMap & fileMap, std::vector<FileData> & fileDataVec);
    void getSizeAfterClean(FileMap & fileMap, std::vector<FileData> & fileDataVec);
    void cleanMap(FileMap &fileMap);
    FilePair parse(std::vector<std::string> listOfFiles);
    std::ifstream::pos_type getFileSize(std::string const& filePath);

}
#endif //FINALPARSER_PARSER_H