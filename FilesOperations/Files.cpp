#include "Files.h"

namespace filesOperations
{
	std::vector<std::string> getFilesArray()
	{

		auto dir = ".";
		std::vector<std::string> filesList;
		for (auto item : std::filesystem::recursive_directory_iterator(dir))
		{
			if (!std::filesystem::is_regular_file(item.path()) || item.path().extension() != ".cpp" && item.path().extension() != ".h" && item.path().extension() != ".hpp")
				continue;
			filesList.push_back(item.path().string());
		}
		return filesList;
	}

	std::string getNameFromPath(std::string fileName)
	{
		std::string sep = "\\";
		return fileName.substr(fileName.find_last_of(sep)+1, fileName.length() );
	}
}
