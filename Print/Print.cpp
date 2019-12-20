#include "Print.h"

namespace print
{
    void print(std::vector<std::pair<std::string, std::string>> files)
    {
        std::cout << "Connections in project: " << std::endl;
        for(auto const& file: files)
        {
            std::cout << file.first << " ---> " << file.second << std::endl;
        }
    }
}