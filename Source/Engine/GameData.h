#pragma once

#include "Girl.h"

#include <vector>
#include <utility>

class GameData
{
public:

    static void create();
    static GameData* getInstance();

    std::vector<Girl> getGirls();
    void addGirl(Girl girl);
    std::pair<Girl*, size_t> getRandomGirl();

private:

    GameData();

    static GameData* _instance;

    std::vector<Girl> _girls;
};
