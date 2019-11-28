#include <iostream>
#include "Parse/Parser.h"
#include "files.h"

int main()
{
	std::vector<std::string> files = getFilesArray();
    parse(files);
}
