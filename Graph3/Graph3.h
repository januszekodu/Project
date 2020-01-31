#pragma once
#include"../Search/Search.h"
#include"../FilesOperations/Files.h"

namespace graph3
{
	typedef std::map<std::string, std::vector<std::string>> fMap;
	typedef std::vector<std::string> fList;
	typedef std::pair<std::string, std::string> Edge;

	std::vector<Edge> searchForConnections(fList);
	void removeDuplicates(std::vector<std::string>&);
	std::vector<std::string> getUserCreatedNamespaces(fList);
	std::vector<std::string> getUsedNamespaces(std::string);
	std::vector<std::string> getUsedUserNamespaces(std::string filePath, std::vector<std::string>userNamespaces, std::vector<std::string> usedNamespaces);
	std::vector<Edge> getNSConnections(fList);
	void PrintModulesConnection(fList);
}
