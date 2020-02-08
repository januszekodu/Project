#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<filesystem>


namespace filesOperations
{
	std::vector<std::string> getFilesArray();
	std::string getNameFromPath(std::string);
}
