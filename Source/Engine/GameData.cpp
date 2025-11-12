#include "GameData.h"

#include <Tools/FileSystemHelper.hpp>

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
