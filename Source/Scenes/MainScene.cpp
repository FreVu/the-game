#include "MainScene.h"

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
        "MainScene.cpp\n");
}

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    GameData::create();

    _mouseListener                = EventListenerMouse::create();
    _mouseListener->onMouseMove   = AX_CALLBACK_1(MainScene::onMouseMove, this);
    _mouseListener->onMouseUp     = AX_CALLBACK_1(MainScene::onMouseUp, this);
    _mouseListener->onMouseDown   = AX_CALLBACK_1(MainScene::onMouseDown, this);
    _mouseListener->onMouseScroll = AX_CALLBACK_1(MainScene::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    //_keyboardListener                = EventListenerKeyboard::create();
    //_keyboardListener->onKeyPressed  = AX_CALLBACK_2(MainScene::onKeyPressed, this);
    //_keyboardListener->onKeyReleased = AX_CALLBACK_2(MainScene::onKeyReleased, this);
    //_eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 11);

    // Create portrait zones in the upper part of the screen
    createPortraitZones();

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void MainScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        // AXLOGD("onTouchesBegan detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        // AXLOGD("onTouchesMoved detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        // AXLOGD("onTouchesEnded detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    // AXLOGD("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOGD("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    // AXLOGD("onMouseScroll detected, X:{}  Y:{}", e->getScrollX(), e->getScrollY());
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    // AXLOGD("Scene: #{} onKeyPressed, keycode: {}", _sceneID, static_cast<int>(code));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    AXLOGD("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void MainScene::createPortraitZones()
{
    const auto margin = 10;
    auto screenSize   = _director->getVisibleSize();
    auto screenOrigin = _director->getVisibleOrigin();

    //const auto nbPortrait = 2;  // TODO
    //std::vector<std::string> portraitFile = {"Fe/Fe001/Out001/000_f.png", "Fe/Fe002/Out004/000_f.png"};

    //  Calculate portrait zone dimensions with 2:3 aspect ratio
    float portraitHeight = screenSize.height / 2.0f;
    float portraitWidth  = portraitHeight * 2.0f / 3.0f;

    float portraitY = screenOrigin.y + screenSize.height - portraitHeight / 2 - 50;

    auto girls = GameData::getInstance()->getGirls();
    for (unsigned i = 0; i < girls.size(); i++)
    {
        float portraitX = screenOrigin.x + screenSize.width * (i + 1) / (girls.size() + 1);

        auto portrait = Sprite::create(girls[i].getFrontFile());
        _portrait.push_back(portrait);
        if (portrait == nullptr)
        {
            problemLoading(girls[i].getFrontFile().c_str());
        }
        else
        {
            portrait->setPosition(Vec2(portraitX, portraitY));
            portrait->setScale(portraitWidth / _portrait[i]->getContentSize().width,
                                   portraitHeight / _portrait[i]->getContentSize().height);
            this->addChild(_portrait[i], 2);
        }

        auto flipButton1 = UI::Helper::createButton(
            "Button.png",
            "",
            "",
            "FLIP",
            portraitX - (50 + margin),
            portraitY - portraitHeight / 2 - (20 + margin),
            100,
            40,
            AX_CALLBACK_1(MainScene::flipCallback, this, i));

        if (flipButton1 == nullptr)
        {
            problemLoading("'Button.png'");
        }
        else
        {
            flipButton1->setTag(static_cast<int>(i));
            this->addChild(flipButton1, 2);
        }

        auto nextButton1 = UI::Helper::createButton(
            "Button.png",
            "",
            "",
            "NEXT",
            portraitX + (50 + margin),
            portraitY - portraitHeight / 2 - (20 + margin),
            100,
            40,
            AX_CALLBACK_1(MainScene::nextCallback, this, i));

        if (nextButton1 == nullptr)
        {
            problemLoading("'Button.png'");
        }
        else
        {
            nextButton1->setTag(static_cast<int>(i));
            this->addChild(nextButton1, 2);
        }
    }

}

void MainScene::update(float delta) {}

void MainScene::menuCloseCallback(ax::Object* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MainScene::flipCallback(ax::Object* sender, int index)
{
    AXLOG("Flip button clicked, index: %d", index);
    GameData::getInstance()->getGirls()[index].flip();
    _portrait[index]->setTexture(GameData::getInstance()->getGirls()[index].getFrontFile());
}

void MainScene::nextCallback(ax::Object* sender, int index)
{
    AXLOG("Next button clicked, index: %d", index);
    GameData::getInstance()->getGirls()[index].undress();
    _portrait[index]->setTexture(GameData::getInstance()->getGirls()[index].getFrontFile());
}

MainScene::MainScene()
{
    //_sceneID = ++s_sceneID;
    // AXLOGD("Scene: ctor: #{}", _sceneID);
}

MainScene::~MainScene()
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
