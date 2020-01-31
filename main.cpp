#include "Parse/Parse.h"
#include "Graph/Parser.h"
#include "files.h"
#include "Printer/Printer.h"

int main()
{
    Graph::Parser parser;

    std::vector<std::string> files = getFilesArray();

    fileParse::FileMap fileMap = fileParse::parse(files);

    std::vector<Graph::Edge> graphEdges = parser.parse(fileMap);

    Printer::Printer printer;
    printer.PrintDep(graphEdges);
}
