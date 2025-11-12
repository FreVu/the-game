#include "Outfit.h"

#include "Tools/FileSystemHelper.hpp"

Outfit::Outfit(std::filesystem::directory_entry directory) : _directory (directory)
{
}

std::string Outfit::getCurrentFile() const
{
    return _directory.path().string() + "/" + (_currentStep < 10 ? "00" : "0") + std::to_string(_currentStep) +
           (_front ? "_f.png" : "_b.png");
}

void Outfit::flip()
{
    _front = !_front;
}

void Outfit::undress()
{
    _currentStep = FileSystemHelper::getRandomNumberFromSection(_directory.path().string() + "/steps.txt", _currentStep);
}
