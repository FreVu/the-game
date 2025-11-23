#pragma once

#include "Outfit.h"

#include <filesystem>

class Girl
{
public:

    explicit Girl(std::filesystem::directory_entry directory);

    std::string getFrontFile();

    void flip();
    bool undress();

private:

    std::string _name;
    Outfit* _outfit;
};
