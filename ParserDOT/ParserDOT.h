#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../Parse/Parse.h"
#include "../Graph3/Graph3.h"

namespace parserDOT
{
    typedef std::vector<fileParse::FileData> FilesInfo;
    typedef std::vector<std::pair<std::string, std::string>> Dependencies;
    

    void ParseToDOT_1(const Dependencies, const FilesInfo); //funkcja parsuj¹ca dane z pierwszej historyjki

    //*********************************************************************************************************//

    void ParseToDOT_2(const Dependencies); //funkcja parsuj¹ca dane z drugiej historyjki

    //*********************************************************************************************************//

    void ParseToDOT_3(const graph3::Graph); //funkcja parsuj¹ca dane z trzeciej historyjki #TODO
 
}
