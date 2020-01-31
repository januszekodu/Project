#include <vector>
#include <string>
#include <iostream>

namespace Printer
{
    typedef std::vector<std::pair<std::string, std::string>> Dependencies;

    class Printer
    {
    public:
        void PrintDep(const Dependencies);
    };
}
