#include "Parse/Parse.h"
#include "Graph/Parser.h"
#include "Print/Print.h"
#include "Graph3/Graph3.h"
#include "FilesOperations/Files.h"

void FirstStory();
void SecondStory();
void ThirdStory();

int main(){
	FirstStory();
	SecondStory();
	ThirdStory();
}


void FirstStory(){
	std::cout << "First story:\n\n";

	Graph::Parser parser;
	std::vector<std::string> files = filesOperations::getFilesArray();

	fileParse::FileMap fileMap = fileParse::parse(files);
	std::vector<Graph::Edge> graphEdges = parser.parse(fileMap);

	print::print(graphEdges);

	std::cout << std::endl;
}

void SecondStory() {
	std::cout << "Second story:\n\n";


	std::cout << std::endl;
}

void ThirdStory() {
	std::cout << "Third story:\n\n";
	std::vector<std::string> files = filesOperations::getFilesArray();
	graph3::PrintModulesConnection(files);
	std::cout << std::endl;
}