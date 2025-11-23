#include "StripGameScene.h"

#include "UI/UIButton.h"
#include "UI/Helper.hpp"

#include "Tools/FileSystemHelper.hpp"

#include "Engine/GameData.h"
#include "Engine/Girl.h"

using namespace ax;

// static int s_sceneID = 1000;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "StripGameScene.cpp\n");
}

bool StripGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    GameData::create();

    _mouseListener                = EventListenerMouse::create();
    _mouseListener->onMouseMove   = AX_CALLBACK_1(StripGameScene::onMouseMove, this);
    _mouseListener->onMouseUp     = AX_CALLBACK_1(StripGameScene::onMouseUp, this);
    _mouseListener->onMouseDown   = AX_CALLBACK_1(StripGameScene::onMouseDown, this);
    _mouseListener->onMouseScroll = AX_CALLBACK_1(StripGameScene::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    //_keyboardListener                = EventListenerKeyboard::create();
    //_keyboardListener->onKeyPressed  = AX_CALLBACK_2(StripGameScene::onKeyPressed, this);
    //_keyboardListener->onKeyReleased = AX_CALLBACK_2(StripGameScene::onKeyReleased, this);
    //_eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 11);

    // Create portrait zones in the upper part of the screen
    createPortraitZones();

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void StripGameScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        // AXLOGD("onTouchesBegan detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
    }
}

void StripGameScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        // AXLOGD("onTouchesMoved detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
    }
}

void StripGameScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        // AXLOGD("onTouchesEnded detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
    }
}

void StripGameScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    // AXLOGD("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void StripGameScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOGD("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void StripGameScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void StripGameScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    // AXLOGD("onMouseScroll detected, X:{}  Y:{}", e->getScrollX(), e->getScrollY());
}

void StripGameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    // AXLOGD("Scene: #{} onKeyPressed, keycode: {}", _sceneID, static_cast<int>(code));
}

void StripGameScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    AXLOGD("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void StripGameScene::createPortraitZones()
{
    const auto margin = 10;
    auto screenSize   = _director->getVisibleSize();
    auto screenOrigin = _director->getVisibleOrigin();

    // const auto nbPortrait = 2;  // TODO
    // std::vector<std::string> portraitFile = {"Fe/Fe001/Out001/000_f.png", "Fe/Fe002/Out004/000_f.png"};

    //  Calculate portrait zone dimensions with 2:3 aspect ratio
    float portraitHeight = screenSize.height / 2.0f;
    float portraitWidth  = portraitHeight * 2.0f / 3.0f;

    float portraitY = screenOrigin.y + screenSize.height - portraitHeight / 2 - 50;

    auto next = UIHelper::Helper::createButton("Button.png", "", "", "NEXT", screenSize.x / 2, screenSize.y / 4, 100, 40,
                                         AX_CALLBACK_1(StripGameScene::randomNext, this));

    if (next == nullptr)
    {
        problemLoading("'Button.png'");
    }
    else
    {
        // next->setTag(static_cast<int>(i));
        this->addChild(next, 2);
    }

    auto girls = GameData::getInstance()->getGirls();
    for (unsigned i = 0; i < girls.size(); i++)
    {
        GirlData data;

        float portraitX = screenOrigin.x + screenSize.width * (i + 1) / (girls.size() + 1);

        data._portrait = Sprite::create(girls[i].getFrontFile());
        if (data._portrait == nullptr)
        {
            problemLoading(girls[i].getFrontFile().c_str());
        }
        else
        {
            data._portrait->setPosition(Vec2(portraitX, portraitY));
            data._portrait->setScale(portraitWidth / data._portrait->getContentSize().width,
                                     portraitHeight / data._portrait->getContentSize().height);
            this->addChild(data._portrait, 2);
        }

        // Create FLIP button centered and with same width as portrait
        auto flipButton = UIHelper::Helper::createButton("Button.png", "", "", "FLIP", 
                                                    static_cast<int>(portraitX),
                                                    static_cast<int>(portraitY - portraitHeight / 2 - (20 + margin)), 
                                                    static_cast<int>(portraitWidth), 40,
                                                    AX_CALLBACK_1(StripGameScene::flipCallback, this, i));

        if (flipButton == nullptr)
        {
            problemLoading("'Button.png'");
        }
        else
        {
            flipButton->setTag(static_cast<int>(i));
            this->addChild(flipButton, 2);
        }

        // Control parameters
        const int buttonSizeX = 30;
        const int buttonSizeY = 30;
        const int labelWidth = 30;
        const int spacing = 5;
        const int iconSize = 30;
        
        // Position displays and controls side by side
        const int controlSpacing = 50;
        const int controlWidth = buttonSizeX + spacing + labelWidth + spacing + iconSize + spacing + buttonSizeX; // button + spacing + label + spacing + icon + spacing + button
        float attackControlX = portraitX - controlWidth / 2 - controlSpacing / 2;
        float defenseControlX = portraitX + controlWidth / 2 + controlSpacing / 2;
        
        // Create displays just under the FLIP button
        float displayY = portraitY - portraitHeight / 2 - (20 + margin) - 40 - margin;
        float attackDisplayX  = defenseControlX;
        float defenseDisplayX = attackControlX;
        
        data._attackDisplay = UIHelper::Helper::createValueDisplay(0,
                                                                   static_cast<int>(attackDisplayX),
                                                                   static_cast<int>(displayY),
                                                                   labelWidth,
                                                                   "",
                                                                   "Attack.png");

        if (data._attackDisplay == nullptr)
        {
            problemLoading("'Attack.png'");
        }
        else
        {
            data._attackDisplay->setTag(static_cast<int>(i));
            this->addChild(data._attackDisplay, 2);
        }

        data._defenseDisplay = UIHelper::Helper::createValueDisplay(0,
                                                                      static_cast<int>(defenseDisplayX),
                                                                      static_cast<int>(displayY),
                                                                      labelWidth,
                                                                      "",
                                                                      "Defence.png");

        if (data._defenseDisplay == nullptr)
        {
            problemLoading("'Defence.png'");
        }
        else
        {
            data._defenseDisplay->setTag(static_cast<int>(i));
            this->addChild(data._defenseDisplay, 2);
        }

        // Create controls under the displays
        float controlY = displayY - iconSize - margin;
        
        data._attackControl = UIHelper::Helper::createIntegerControl("Button.png", 0, 0, 5, 
                                                                static_cast<int>(attackControlX), 
                                                                static_cast<int>(controlY), buttonSizeX, buttonSizeY, labelWidth, "", "Attack.png");

        if (data._attackControl == nullptr)
        {
            problemLoading("'Button.png'");
        }
        else
        {
            data._attackControl->setTag(static_cast<int>(i));
            this->addChild(data._attackControl, 2);
        }

        // Create Defense control next to the attack control
        data._defenseControl = UIHelper::Helper::createIntegerControl("Button.png", 0, 0, 5, 
                                                                static_cast<int>(defenseControlX), 
                                                                static_cast<int>(controlY), buttonSizeX, buttonSizeY, labelWidth, "", "Defence.png");

        if (data._defenseControl == nullptr)
        {
            problemLoading("'Button.png'");
        }
        else
        {
            data._defenseControl->setTag(static_cast<int>(i));
            this->addChild(data._defenseControl, 2);
        }

        _girlData.push_back(data);
    }

    // Create END TURN button in lower right corner
    const int buttonWidth = 100;
    const int buttonHeight = 40;
    float endTurnX = screenOrigin.x + screenSize.width - buttonWidth / 2 - margin;
    float endTurnY = screenOrigin.y + buttonHeight / 2 + margin;

    auto endTurnButton = UIHelper::Helper::createButton("Button.png", "", "", "END TURN", endTurnX, endTurnY, buttonWidth, buttonHeight,
                                                  AX_CALLBACK_1(StripGameScene::endTurnCallback, this, 0));

    if (endTurnButton == nullptr)
    {
        problemLoading("'Button.png'");
    }
    else
    {
        this->addChild(endTurnButton, 2);
    }
}

void StripGameScene::update(float delta) {}

void StripGameScene::menuCloseCallback(ax::Object* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void StripGameScene::flipCallback(ax::Object* sender, int index)
{
    AXLOG("Flip button clicked, index: %d", index);
    GameData::getInstance()->getGirls()[index].flip();
    _girlData[index]._portrait->setTexture(GameData::getInstance()->getGirls()[index].getFrontFile());
}

void StripGameScene::lost(ax::Object* sender, int index)
{
    AXLOG("Next button clicked, index: %d", index);

    if (GameData::getInstance()->getGirls()[index].undress())
    {
        _girlData[index]._portrait->setTexture(GameData::getInstance()->getGirls()[index].getFrontFile());
    }
    else
    {
        // lost
    }
}

void StripGameScene::randomNext(ax::Object* sender)
{
    AXLOG("Random Next button clicked");
    auto [girl,index] = GameData::getInstance()->getRandomGirl();

    if (girl->undress())
    {
        _girlData[index]._portrait->setTexture(girl->getFrontFile());
    }
    else
    {
        // lost
    }
}

void StripGameScene::endTurnCallback(ax::Object* sender, int index)
{
    AXLOG("END TURN button clicked, index: %d", index);
    // Access model similar to flipCallback
    auto girls = GameData::getInstance()->getGirls();
    if (index >= 0 && index < static_cast<int>(girls.size()))
    {
        // End turn logic can be added here
        // For now, following the pattern of flipCallback
    }
}

StripGameScene::StripGameScene()
{
    //_sceneID = ++s_sceneID;
    // AXLOGD("Scene: ctor: #{}", _sceneID);
}

StripGameScene::~StripGameScene()
{
    // AXLOGD("~Scene: dtor: #{}", _sceneID);

    if (_touchListener)
        _eventDispatcher->removeEventListener(_touchListener);
    if (_keyboardListener)
        _eventDispatcher->removeEventListener(_keyboardListener);
    if (_mouseListener)
        _eventDispatcher->removeEventListener(_mouseListener);
    //_sceneID = -1;
}
