#include <iostream>
#include "Parse/Parser.h"
#include "Graph/Parser.h"
#include "files.h"

int main()
{
    Graph::Parser parser;
	std::vector<std::string> files = getFilesArray();
    FileMap fileMap = parse(files);

    std::vector<Graph::Edge> graphEdges = parser.parse(fileMap);
}
