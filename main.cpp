#include "Parse/Parse.h"
#include "Graph/Parser.h"
#include "Print/Print.h"
#include "Graph3/Graph3.h"
#include "FilesOperations/Files.h"

int main()
{
    Graph::Parser parser;

    std::vector<std::string> files = filesOperations::getFilesArray();

    fileParse::FileMap fileMap = fileParse::parse(files);

    std::vector<Graph::Edge> graphEdges = parser.parse(fileMap);
	std::cout << "First story:\n";
    print::print(graphEdges);


	std::cout << "Third story:\n";
	graph3::PrintModulesConnection(files);
}
