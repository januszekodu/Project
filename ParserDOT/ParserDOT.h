#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace parserDOT
{
    typedef std::vector<std::pair<std::string, std::string>> Dependencies;

    void ParseToDOT_1(const Dependencies); //funkcja parsuj¹ca dane z pierwszej historyjki
    void ParseToDOT_2(); //funkcja parsuj¹ca dane z drugiej historyjki #TODO
    void ParseToDOT_3(); //funkcja parsuj¹ca dane z trzeciej historyjki #TODO
 
}
