#include "Girl.h"

#include "Tools/FileSystemHelper.hpp"

Girl::Girl(std::filesystem::directory_entry directory) :
    _name(directory.path().string())
{
    auto outfitDirectory = FileSystemHelper::getRandomDirectory(directory.path().string());
    _outfit              = new Outfit(outfitDirectory);
}

std::string Girl::getFrontFile()
{
    return _outfit->getCurrentFile();
}

void Girl::flip()
{
    _outfit->flip();
}

bool Girl::undress()
{
    return _outfit->undress();
}
