#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<filesystem>

namespace fs = std::filesystem;

std::vector<std::string> getFilesArray() {

	auto dir = ".";
	std::vector<std::string> filesList;
	for (auto item : fs::recursive_directory_iterator(dir))
	{
		if (!fs::is_regular_file(item.path()) || item.path().extension() != ".cpp" && item.path().extension() != ".h" && item.path().extension() != ".hpp")
			continue;
		filesList.push_back(item.path().string());
	}

	return filesList;
}



