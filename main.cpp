#include "Parse/Parse.h"
#include "Graph/Parser.h"
#include "Graph3/Graph3.h"
#include "FilesOperations/Files.h"
#include "FunctionParser/function_dependency.h"
#include "Graphviz/Graphviz.h"
#include "ParserDOT/ParserDOT.h"

void FirstStory();
void SecondStory();
void ThirdStory();

int main(){
	FirstStory();
	//SecondStory();
	//ThirdStory();
}

void FirstStory()
{
	std::cout << "First story:\n\n";

	Graph::Parser parser;
	std::vector<std::string> files = filesOperations::getFilesArray();

	fileParse::FilePair filePair = fileParse::parse(files);
	std::vector<Graph::Edge> graphEdges = parser.parse(filePair.second);


    parserDOT::ParseToDOT_1(graphEdges); //parsowanie danych wektora graphEdges do pliku graph.dot
    Graphviz::GenGraph(); //generowanie z pliku graph.dot pliku graph.jpg
    Graphviz::OpenGraph(); //otwarcie grafu (pliku graph.jpg)
}

void SecondStory()
{
	std::cout << "Second story:\n\n";
    std::vector<std::string> files = filesOperations::getFilesArray();

    for (std::string file : files)
    {
        std::cout << file << std::endl;
        functionParser::FunctionDependency dependencies = functionParser::parse(file);
        std::cout << "Processing file \"" << file << "\" OK" << std::endl << std::endl;

        for (const std::pair<std::string, std::vector<std::string>> functionDependencies : dependencies)
        {
            std::cout << functionDependencies.first << std::endl;

            for (const std::string _function : functionDependencies.second)
            {
                std::cout << " > " << _function << std::endl;
            }

            std::cout << std::endl;
        }
    }

	std::cout << std::endl;
}

void ThirdStory()
{
	std::cout << "Third story:\n\n";
	std::vector<std::string> files = filesOperations::getFilesArray();
	graph3::Graph graph = graph3::getGraph(files);
	std::cout << std::endl;
}