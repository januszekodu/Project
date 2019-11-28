#include<map>
#include<string>
#include<vector>

#include "Parser.h"

namespace Graph
{
    std::vector<Edge> Parser::parse(const Dependencies dependencies)
    {
        std::vector<Edge> edges;

        for( const std::pair<std::string, std::vector<std::string>> single_file_dependecies : dependencies )
        {
            for(std::string dependency : single_file_dependecies.second)
            {
                edges.push_back(Edge(single_file_dependecies.first, dependency));
            }
        }

        return edges;
    }
}
