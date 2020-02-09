#include "Printer.h"
#include <string>

namespace Printer
{
    void Printer::PrintDep(Dependencies files)
    {
        std::string PrevFile;
        Dependencies TempDep = files;

        std::cout << "Dependencies in project: " << std::endl;
        for (auto const& file : TempDep)
        {

            if (file.first == PrevFile)
            {
                std::cout << ", " << file.second;
            }
            else
            {
                std::cout << std::endl << file.first << " ---> " << file.second;
                PrevFile = file.first;
            }
        }
    }
}