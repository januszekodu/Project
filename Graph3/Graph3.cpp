#include"Graph3.h"

namespace graph3
{
	//creating vector of all used modules in selected file
	std::vector<std::string> getUsedModules(std::string filePath)
	{
		std::vector<std::string> usedModules;
		std::string line;
		std::ifstream file;

		file.open(filePath);
		if (file.is_open())
        {
			while (std::getline(file, line))
			{
				if (line.find("::") != std::string::npos)
				{
					//splitting line by "::", to get all used modules
					std::vector<std::string> lineSplitted = strOperations::SplitString(line, "::");
					for (int i = 0; i < lineSplitted.size(); i++) 
					{
						lineSplitted[i] = lineSplitted[i].substr(0, lineSplitted[i].find_first_of("::"));
						
						//e.g. var = vars::getvar()
						if (lineSplitted[i].find(" ") != std::string::npos)
							lineSplitted[i] = lineSplitted[i].substr(lineSplitted[i].find_last_of(" ")+1, lineSplitted[i].length());
						//e.g. while(std::getline())
						if (lineSplitted[i].find("(") != std::string::npos)
							lineSplitted[i] = lineSplitted[i].substr(lineSplitted[i].find_last_of("(")+1, lineSplitted[i].length());
						//e.g. vector<var::getvar()>
						if (lineSplitted[i].find("<") != std::string::npos)
							lineSplitted[i] = lineSplitted[i].substr(lineSplitted[i].find_last_of("<")+1, lineSplitted[i].length());
						//e.g. void(int x,var::getvar())
						if (lineSplitted[i].find(",") != std::string::npos)
							lineSplitted[i] = lineSplitted[i].substr(lineSplitted[i].find_last_of(",")+1, lineSplitted[i].length());

						lineSplitted[i].erase(remove_if(lineSplitted[i].begin(), lineSplitted[i].end(), isspace), lineSplitted[i].end());
						usedModules.push_back(lineSplitted[i]);
					}
				}
			}
		}
		return usedModules;
	}

	//Creating vector of all user created namespaces, using function from Search module.
	std::vector<std::string> getUserCreatedModules(fList fileList)
    {
		fMap fileMap = Search::cone(fileList);
		std::vector<std::string> userModules;

		for (auto it = fileMap.cbegin(); it != fileMap.cend(); ++it)
			for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
				userModules.push_back(*it2);
		strOperations::removeDuplicates(userModules);

		return userModules;
	}

	//Creating vector of all used modules, created by users.
	std::vector<std::string> getUsedUserModules(std::string filePath, std::vector<std::string>userModules, std::vector<std::string> usedModules)
	{
		std::vector<std::string> listOfFiles;
		for (int i = 0; i < usedModules.size(); i++)
			for (int j = 0; j < userModules.size(); j++)
				if (usedModules[i] == userModules[j])
					listOfFiles.push_back(usedModules[i]);

		return listOfFiles;
	}

	//creating vector with dependencies between files and modules
	std::vector<Edge> searchForConnections(fList fileList)
	{
		std::vector<Edge> filesAndModules;
		std::vector<std::string> userModules = getUserCreatedModules(fileList);
		for (int i = 0; i < fileList.size(); i++)
        {
			std::vector<std::string> usedModules = getUsedModules(fileList[i]);
			std::vector<std::string> userUsed = getUsedUserModules(fileList[i], userModules, usedModules);
			for (int j = 0; j < userUsed.size(); j++)
				filesAndModules.push_back(Edge(fileList[i], userUsed[j]));
		}
		return filesAndModules;
	}

	//creating vector with module-module dependencies using file-module dependencies
	std::vector<Edge> getNSConnections(fList fileList)
	{
		std::vector<Edge> nsConnections;
		std::vector<Edge> fileConnections = searchForConnections(fileList);

		fMap fileMap = Search::cone(fileList);
		for (auto const& con : fileConnections)
			for (auto it = fileMap.cbegin(); it != fileMap.cend(); ++it)
				if (it->first == filesOperations::getNameFromPath(con.first))
					for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
						nsConnections.push_back(Edge(*it2, con.second));

		return nsConnections;
	}

	//creating graph with weights from vector with module-module dependencies
	Graph getWeight(std::vector<Edge> nsConnections)
	{
		Graph Graph;

		//creating graph with base weight
		for (int i = 0; i < nsConnections.size(); i++)
			Graph.push_back(std::pair(nsConnections[i], 1));

		for (int j = 0; j < Graph.size(); j++)
        {
			for (int k = j + 1; k < Graph.size();)
			{
				//if connections are the same, add weight and erase Graph
				if (Graph[j].first.first == Graph[k].first.first && Graph[j].first.second == Graph[k].first.second)
                {
					Graph[j].second++;
					Graph.erase(Graph.begin() + k);
				}
				else
					k++;
			}
		}
		return Graph;
	}

	//final function to return completed graph
	Graph getGraph(fList fileList)
	{
		std::vector<Edge> nsConnections = getNSConnections(fileList);
		Graph graph = getWeight(nsConnections);

		return graph;
	}
}
