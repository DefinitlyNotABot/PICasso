#pragma once

#include <string>

#include <tuple>

class Filereader
{
public:
    // Reads the file and returns a tuple: (valid, filecontent)
    std::tuple<bool, std::string> readFile(const std::string& filename);
};
