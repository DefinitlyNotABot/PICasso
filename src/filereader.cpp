#include <fstream>
#include <sstream>

#include "../header/filereader.hpp"


std::tuple<bool, std::string> Filereader::readFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return {false, ""};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return {true, buffer.str()};
}