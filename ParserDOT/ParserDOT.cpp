#pragma once
#include "ParserDOT.h"
#include <string>
#include <fstream>

namespace parserDOT
{
    void ParseToDOT_1(Dependencies files, FilesInfo data)
    {
        std::string graphInDOT = "digraph{ ";
        int s_1 = 0, s_2 = 0;
        bool FirstFound, SecondFound;


        for (std::pair<std::string, std::string> dep : files)
        {
            FirstFound, SecondFound = false;

            for (fileParse::FileData dat : data) //wyszukiwanie danych o pliku
            {
                if (dat.name == dep.first)
                {
                    s_1 = dat.size;
                    FirstFound = true;
                }
                if (dat.name == dep.second)
                {
                    s_2 = dat.size;
                    SecondFound = true;
                }
            }
            if (!FirstFound) s_1 = 0;
            if (!SecondFound) s_2 = 0; //przypisanie zera w przypadku braku danych

            graphInDOT += "\"" + dep.first + " (" + std::to_string(s_1) + ")" + "\" -> \"" + dep.second + " (" + std::to_string(s_2) + ")" + "\";"; //dodanie linii w jêzyku DOT

        }

        graphInDOT += "}";

        std::ofstream DOTfile;

        DOTfile.open("graph.dot", std::ofstream::out | std::ofstream::trunc); //zapisanie danych o grafie do pliku
        DOTfile << graphInDOT;
        DOTfile.close();
    }

    void ParseToDOT_2(Dependencies files)
    {
        std::string graphInDOT = "digraph{ ";



        for (std::pair<std::string, std::string> dep : files)
        {
            graphInDOT += "\"" + dep.first + "\" -> \"" + dep.second + "\";";
        }

        graphInDOT += "}";

        std::ofstream DOTfile;

        DOTfile.open("graph.dot", std::ofstream::out | std::ofstream::trunc);
        DOTfile << graphInDOT;
        DOTfile.close();
    }

    void ParseToDOT_3(const graph3::Graph dependencies)
    {
        std::string graphInDOT = "digraph{ ";



        for (std::pair<graph3::Edge, unsigned int> dep : dependencies)
        {
            graphInDOT += "\"" + dep.first.first + "\" -> \"" + dep.first.second + "\"[label=\"" + std::to_string(dep.second) + "\"];";
        }

        graphInDOT += "}";

        std::ofstream DOTfile;

        DOTfile.open("graph.dot", std::ofstream::out | std::ofstream::trunc);
        DOTfile << graphInDOT;
        DOTfile.close();
    }
}