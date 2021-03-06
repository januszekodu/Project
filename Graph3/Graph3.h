#pragma once
#include"../Search/Search.h"
#include"../FilesOperations/Files.h"
#include "../StringOperations/StrOperations.h"

namespace graph3
{
	typedef std::map<std::string, std::vector<std::string>> fMap;
	typedef std::vector<std::string> fList;
	typedef std::pair<std::string, std::string> Edge;
	typedef std::vector<std::pair<Edge, unsigned int>> Graph;

	std::vector<Edge> searchForConnections(fList);
	std::vector<Edge> getNSConnections(fList);

	std::vector<std::string> getUserCreatedModules(fList);
	std::vector<std::string> getUsedModules(std::string);
	std::vector<std::string> getUsedUserModules(std::string, std::vector<std::string>, std::vector<std::string>);
	
	Graph getWeight(std::vector<Edge>);
	Graph getGraph(fList);
	
}