#include "Parse.h"

std::ifstream::pos_type getFileSize(std::string const& filePath)
{
    std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

namespace fileParse
{

    void searchInFile(std::string const& fileName, FileMap & fileMap, std::vector<FileData> & fileDataVec)
    {
        std::vector<std::string> vectorWithFiles;
        std::string currentFile;
        std::string filePath = fileName;

        boost::char_separator<char> lineSeparator("\"");
        boost::char_separator<char> fileNameSmallSeparator("/");
        boost::char_separator<char> fileNameSeparator("\\");

        FileData fileData;

        boost::tokenizer<boost::char_separator<char>> tokens(fileName, fileNameSeparator);

        std::string line;
        std::ifstream file;
        file.open(fileName);
        if (!file.is_open())
        {
            perror("Error open");
            exit(EXIT_FAILURE);
        }

        for (auto const &token : tokens)
        {
            currentFile = token;
        }
        fileData.name = currentFile;
        fileData.size = getFileSize(filePath);

        while (std::getline(file, line))
        {
            if (line.find("include") != std::string::npos)
            {
                tokenizer tokens(line, lineSeparator);

                for (tokenizer::iterator token_it = tokens.begin(); token_it != tokens.end(); ++token_it)
                {
                    if (distance(tokens.begin(), token_it) == 1)
                    {
                        std::string tmp = *token_it;
                        std::string returnName;
                        boost::tokenizer<boost::char_separator<char>> fileTokens(tmp, fileNameSmallSeparator);
                        for (auto const &token : fileTokens)
                        {
                            returnName = token;
                        }
                        vectorWithFiles.emplace_back(returnName);
                    }
                }
            }
        }

        if (currentFile == "Parse.cpp")
            vectorWithFiles.pop_back();

        fileDataVec.emplace_back(fileData);
        fileMap.insert(std::pair<std::string, std::vector<std::string>>(currentFile, vectorWithFiles));
    }

    void cleanMap(FileMap &fileMap)
    {
        for (auto it = fileMap.cbegin(); it != fileMap.cend();)
        {
            if (it->second.empty())
            {
                fileMap.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }

    void getSizeAfterClean(FileMap & fileMap, std::vector<FileData> & fileDataVec)
    {
        std::vector<std::string> tmpVec;
        for (auto it = fileMap.cbegin(); it != fileMap.cend(); it++)
        {
            tmpVec.emplace_back(it->first);
        }

        for(std::vector<FileData>::iterator fileVecIt=fileDataVec.begin(); fileVecIt!=fileDataVec.end(); )
        {
            int counter = 0;
            for(auto const& vecIt: tmpVec)
            {
                if(fileVecIt->name == vecIt)
                {
                    counter++;
                }
            }
            if(counter == 0)
            {
                fileVecIt = fileDataVec.erase(fileVecIt);
            }
            else
            {
                ++fileVecIt;
            }
        }
    }

    FilePair parse(std::vector<std::string> listOfFiles)
    {
        FilePair filePair;
        FileMap fileMap;
        std::vector<FileData> fileDataVec;
        for (auto const &it: listOfFiles)
        {
            searchInFile(it, fileMap, fileDataVec);
        }

        cleanMap(fileMap);
        getSizeAfterClean(fileMap, fileDataVec);

        filePair.first = fileDataVec;
        filePair.second = fileMap;

        //////// If you want to print all map and vector just uncomment below code ////////
        /*for(auto it = fileMap.cbegin(); it != fileMap.cend(); ++it)
        {
            std::cout <<"Nazwa pliku: " << it->first << std::endl;
            std::cout << "Jego powiazania: ";
            for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                std::cout << *it2 << " ";

            std::cout << std::endl << std::endl;
        }

         for(auto const& it: fileDataVec)
        {
            std::cout << "File name: " << it.name << ", file size: " << it.size << " and file edge power: " << it.edgePower << std::endl;
        }
         */

        return filePair;
    }
}
