#include "Search.h"

namespace Search
{

	void SearchF(std::string const &fileName, fMap &fileMap)
	{
		std::vector<std::string> fileVector;
		std::string cFile;

		boost::char_separator<char> lSep("\"");
		boost::char_separator<char> llSep("/");
		boost::char_separator<char> lllSep("\\");
		

		boost::tokenizer<boost::char_separator<char>> tokens(fileName, lllSep);

		std::string line;
		std::ifstream file;
		file.open(fileName);
		if (!file.is_open())
		{
			perror("Error");
			exit(EXIT_FAILURE);

		}

		for (auto const &token : tokens) {
			cFile = token;
		}

		while (std::getline(file, line))
		{
			if (line.find("namespace") != std::string::npos)
			{
				tokenizer tokens(line, llSep);

				for (tokenizer::iterator token_it = tokens.begin(); token_it != tokens.end(); token_it++)
				{
					if (distance(tokens.begin(), token_it) == 1)
					{
						std::string temp = *token_it;
						std::cout << temp;
						std::string Name;
						boost::tokenizer<boost::char_separator<char>> fileTokens(temp, lSep);
						std::cout << *token_it;
						for (auto const &token : fileTokens)
						{
							Name = token;
						}
						fileVector.emplace_back(Name);

					}

				}

			}


		}
		fileMap.insert(std::pair<std::string, std::vector<std::string>>(cFile, fileVector));
		

	}

	

	

	void cMap(fMap &fileMap)
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

	fMap cone(std::vector<std::string> FileList)
	{
		fMap fileMap;
		for (auto const &it : FileList)
		{
			SearchF(it, fileMap);


			for (auto it = fileMap.cbegin(); it != fileMap.cend(); ++it)
			{
				std::cout << "Nazwa metody: ";
				std::cout<< it->first << std::endl;
				std::cout << "Jej powiazania: ";
				for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
					std::cout << *it2 << " ";
				std::cout << std::endl << std::endl;
			}
			
		}
		return fileMap;
	}
}






