#include<map>
#include<string>
#include<vector>

namespace Graph
{
    typedef std::map<std::string, std::vector<std::string>> Dependencies;
    typedef std::pair<std::string, std::string> Edge;

    std::vector<Edge> parse(const Dependencies);
}
