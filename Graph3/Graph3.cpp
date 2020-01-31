#include"Graph3.h"

namespace graph3 {

	void removeDuplicates(std::vector<std::string>& stringArray) {
		stringArray.erase(std::unique(stringArray.begin(), stringArray.end()), stringArray.end());
	}

	std::vector<std::string> getUsedNamespaces(std::string filePath) {
		std::vector<std::string> NSpaces;
		
		std::string line;
		std::ifstream file;

		file.open(filePath);
		if (file.is_open()) {
			while (std::getline(file, line)) {
				if (line.find("::") != std::string::npos) {
					line = line.substr(0, line.find_first_of("::"));
					if (line.find(" ") != std::string::npos)
						line = line.substr(line.find_last_of(" "), line.length());

					line.erase(std::remove(line.begin(), line.end(), '\t'));
					line.erase(std::remove(line.begin(), line.end(), ' '));
					NSpaces.push_back(line);
				}

			}
		}
		return NSpaces;
	}

	std::vector<std::string> getUserCreatedNamespaces(fList fileList) {

		fMap fileMap = Search::cone(fileList);
		std::vector<std::string> userNamespaces;

		for (auto it = fileMap.cbegin(); it != fileMap.cend(); ++it)
		{
			for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
				userNamespaces.push_back(*it2);
		}
		removeDuplicates(userNamespaces);

		return userNamespaces;
	}

	std::vector<std::string> getUsedUserNamespaces(std::string filePath, std::vector<std::string>userNamespaces, std::vector<std::string> usedNamespaces) {
		std::vector<std::string> listOfFiles;
		for (int i = 0; i < usedNamespaces.size(); i++) {
			for (int j = 0; j < userNamespaces.size(); j++) {
				if (usedNamespaces[i] == userNamespaces[j]) {
					listOfFiles.push_back(usedNamespaces[i]);
				}
			}
		}
		return listOfFiles;
	}


	std::vector<Edge> searchForConnections(fList fileList){
		std::vector<Edge> filesAndNamespaces;
		std::vector<std::string> userNamespaces = getUserCreatedNamespaces(fileList);
		for (int i = 0; i < fileList.size(); i++) {
			std::vector<std::string> usedNamespaces = getUsedNamespaces(fileList[i]);
			std::vector<std::string> userUsed = getUsedUserNamespaces(fileList[i], userNamespaces, usedNamespaces);
			for (int j = 0; j < userUsed.size(); j++)
				filesAndNamespaces.push_back(Edge(fileList[i], userUsed[j]));
	
		}
		return filesAndNamespaces;
	}


	std::vector<Edge> getNSConnections(fList fileList) {
		std::vector<Edge> nsConnections;
		std::vector<Edge> fileConnections = searchForConnections(fileList);

		fMap fileMap = Search::cone(fileList);
		for (auto const& con : fileConnections) {
			for (auto it = fileMap.cbegin(); it != fileMap.cend(); ++it)
			{
				if (it->first == filesOperations::getNameFromPath(con.first)) {
					for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
						nsConnections.push_back(Edge(*it2, con.second));
					}
				}
			}
		}
		return nsConnections;
	}


	void PrintModulesConnection(fList fileList) {
		std::vector<Edge> nsConnections = getNSConnections(fileList);
		std::vector<int> weights;
		std::vector<int> weightEl;

		for (int j = 0; j < nsConnections.size(); j++) {
			weights.push_back(1);
			weightEl.push_back(j);
			for (int k = j + 1; k < nsConnections.size();) {
				if (nsConnections[j].second == nsConnections[k].second){
					weights[j]++;
					nsConnections.erase(nsConnections.begin() + k);
				}
				else {
					k++;   
				}
			}
		}

		int it = 0;
		for (auto const& ns : nsConnections)
		{
			
			std::cout << ns.first << " ---> " << ns.second << " WEIGHT: " << weights[weightEl[it]] << std::endl;
			it++;
		}

	}
}