
#pragma once
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <map>
#include <vector>




namespace Search
{
	typedef std::map<std::string, std::vector<std::string>> fMap;
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

	void SearchF(std::string const &fileName, std::map<std::string, std::vector<std::string>> &fileConnectionMap);

	fMap cone(std::vector<std::string> FileList);

	void cMap(fMap &fileMap);



}
