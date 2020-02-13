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

int main()
{
    //FirstStory();
	//SecondStory();
	//ThirdStory();
}

void FirstStory()
{
	std::cout << "First story: ";

	std::vector<std::string> files = filesOperations::getFilesArray();

	fileParse::FilePair filePair = fileParse::parse(files);
	std::vector<Graph::Edge> graphEdges = Graph::parse(filePair.second);

    parserDOT::ParseToDOT_1(graphEdges, filePair.first); //parsowanie danych wektora graphEdges do pliku graph.dot
    Graphviz::GenGraph(); //generowanie z pliku graph.dot pliku graph.jpg
    Graphviz::OpenGraph(); //otwarcie grafu (pliku graph.jpg)
}

void SecondStory()
{
	std::cout << "Second story: ";
    std::vector<std::string> files = filesOperations::getFilesArray();

    std::vector<std::string> functionHeaders;
    for (std::string headerFile : functionParser::filter_header_files(files))
    {
        std::vector<std::string> fileFunctionHeaders = functionParser::get_function_headers(headerFile);
        functionHeaders.insert(functionHeaders.end(), fileFunctionHeaders.begin(), fileFunctionHeaders.end());
    }

    functionParser::FunctionDependency allDependencies;

    for (std::string file : files)
    {
        functionParser::FunctionDependency dependencies = functionParser::parse(file, functionHeaders);
        allDependencies.insert(dependencies.begin(), dependencies.end());
    }

	std::vector<Graph::Edge> graphEdges = Graph::parse(allDependencies);

    parserDOT::ParseToDOT_2(graphEdges); //parsowanie danych wektora graphEdges do pliku graph.dot
    Graphviz::GenGraph(); //generowanie z pliku graph.dot pliku graph.jpg
    Graphviz::OpenGraph(); //otwarcie grafu (pliku graph.jpg)
}

void ThirdStory()
{
	std::cout << "Third story: ";
	std::vector<std::string> files = filesOperations::getFilesArray();
	graph3::Graph graph = graph3::getGraph(files);

    parserDOT::ParseToDOT_3(graph); //parsowanie danych wektora graphEdges do pliku graph.dot
    Graphviz::GenGraph(); //generowanie z pliku graph.dot pliku graph.jpg
    Graphviz::OpenGraph(); //otwarcie grafu (pliku graph.jpg)
}
