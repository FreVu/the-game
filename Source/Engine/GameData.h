#pragma once

#include "Girl.h"

#include <vector>

class GameData
{
public:

    static void create();
    static GameData* getInstance();

    std::vector<Girl> getGirls();
    void addGirl(Girl girl);

private:

    GameData();

    static GameData* _instance;

    std::vector<Girl> _girls;
};
