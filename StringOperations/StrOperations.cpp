#include "StrOperations.h"

namespace strOperations 
{
	void removeDuplicates(std::vector<std::string>& stringArray)
	{
		stringArray.erase(std::unique(stringArray.begin(), stringArray.end()), stringArray.end());
	}

	std::vector<std::string> SplitString(std::string toSplit, std::string splitBy)
	{
		std::vector<std::string> splitted;
		int start = 0, end = 0;

		while ((end = toSplit.find(splitBy, start)) < toSplit.size())
		{
			splitted.push_back(toSplit.substr(start, end - start));
			start = end + 2;
		}
		if (start < toSplit.size())
			splitted.push_back(toSplit.substr(start));
		return splitted;
	}
}