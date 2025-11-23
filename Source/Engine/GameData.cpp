#include "GameData.h"

#include <Tools/FileSystemHelper.hpp>
#include <random>

GameData* GameData::_instance = nullptr;

GameData::GameData() {}

void GameData::create()
{
    // Creation
    if (_instance != nullptr)
    {
        delete _instance;
    }
    _instance = new GameData();

    // Adding girls
    for (auto& girlList : FileSystemHelper::getRandomDirectories("Fe",3))
    {
        Girl girl(girlList);
        GameData::getInstance()->addGirl(girl);
    }
}

GameData* GameData::getInstance()
{
    return _instance;
}

std::vector<Girl> GameData::getGirls()
{
    return _girls;
}

void GameData::addGirl(Girl girl)
{
    _girls.emplace_back(girl);
}

std::pair<Girl*, size_t> GameData::getRandomGirl()
{
    if (_girls.empty())
    {
        return {nullptr, 0};
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, _girls.size() - 1);

    size_t index = dist(gen);
    return {&_girls[index], index};
}
