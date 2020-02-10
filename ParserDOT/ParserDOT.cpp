#include "ParserDOT.h"
#include <string>
#include <fstream>

namespace parserDOT
{
    void ParseToDOT_1(Dependencies files)
    {
        std::string graphInDOT = "graph{ ";



        for (std::pair<std::string, std::string> dep : files)
        {
            graphInDOT += "\"" + dep.first + "\" -- \"" + dep.second + "\";";
        }

        graphInDOT += "}";

        std::ofstream DOTfile;

        DOTfile.open("graph.dot", std::ofstream::out | std::ofstream::trunc);
        DOTfile << graphInDOT;
        DOTfile.close();
    }
}