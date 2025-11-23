#include "StripGameScene.h"

#include "StartMenu.h"
#include "UI/UIButton.h"

#include "UI/Helper.hpp"

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "StripGameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto origin      = _director->getVisibleOrigin();
    auto visibleSize = _director->getVisibleSize();

    auto safeArea   = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    // TITLE
    auto title = ax::Label::createWithTTF("THE GAME", "fonts/Arial.ttf", 24);
    if (title == nullptr)
    {
        problemLoading("'fonts/Arial.ttf'");
    }
    else
    {
        title->setPosition(
            ax::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - title->getContentSize().height));
        this->addChild(title, 1);
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    auto startButton = UIHelper::Helper::createButton(
        "Button.png", "", "", "START", safeOrigin.x + safeArea.size.width / 2 - 50,
        safeOrigin.y + safeArea.size.height / 2 - 20, 100, 40, AX_CALLBACK_1(StartMenu::menuStartCallback, this));

    if (startButton == nullptr)
    {
        problemLoading("'Button.png'");
    }
    else
    {
        this->addChild(startButton, 1);
    }

    // add a "close" icon to exit the progress. it's an autorelease object
    float x = safeOrigin.x + safeArea.size.width - 40;
    float y = safeOrigin.y + 40;

    auto closeItem = UIHelper::Helper::createButton("Quit.png", "", "", "", x, y, 40, 40,
                                              AX_CALLBACK_1(StartMenu::menuCloseCallback, this));

    if (closeItem == nullptr)
    {
        problemLoading("'Quit.png'");
    }
    else
    {
        this->addChild(closeItem, 1);
    }

    /////////////////////////////
    // 3. add your codes below...

    // Some templates (uncomment what you  need)
    // auto touchListener = EventListenerTouchAllAtOnce::create();
    // touchListener->onTouchesBegan = AX_CALLBACK_2(StartMenu::onTouchesBegan, this);
    // touchListener->onTouchesMoved = AX_CALLBACK_2(StartMenu::onTouchesMoved, this);
    // touchListener->onTouchesEnded = AX_CALLBACK_2(StartMenu::onTouchesEnded, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto mouseListener           = ax::EventListenerMouse::create();
    mouseListener->onMouseMove   = AX_CALLBACK_1(StartMenu::onMouseMove, this);
    mouseListener->onMouseUp     = AX_CALLBACK_1(StartMenu::onMouseUp, this);
    mouseListener->onMouseDown   = AX_CALLBACK_1(StartMenu::onMouseDown, this);
    mouseListener->onMouseScroll = AX_CALLBACK_1(StartMenu::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //// add "HelloWorld" splash screen"
    // auto sprite = Sprite::create("HelloWorld.png"sv);
    // if (sprite == nullptr)
    //{
    //     problemLoading("'HelloWorld.png'");
    // }
    // else
    //{
    //     // position the sprite on the center of the screen
    //     sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //     sprite->setContentSize(Size(20, 20));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //    auto drawNode = DrawNode::create();
    //    drawNode->setPosition(Vec2(0, 0));
    //    addChild(drawNode);

    //    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4F::BLUE);
    //}

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void StartMenu::onMouseDown(ax::Event* event)
{
    ax::EventMouse* e = static_cast<ax::EventMouse*>(event);
    AXLOG("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void StartMenu::onMouseUp(ax::Event* event)
{
    ax::EventMouse* e = static_cast<ax::EventMouse*>(event);
    AXLOG("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));

    //_director->replaceScene(utils::createInstance<MainScene>());
    // this->getEventDispatcher()->removeAllEventListeners();
}

void StartMenu::onMouseMove(ax::Event* event)
{
    ax::EventMouse* e = static_cast<ax::EventMouse*>(event);
    AXLOG("onMouseMove detected, X:%f  Y:%f", e->getCursorX(), e->getCursorY());
}

void StartMenu::onMouseScroll(ax::Event* event)
{
    ax::EventMouse* e = static_cast<ax::EventMouse*>(event);
    AXLOG("onMouseScroll detected, X:%f  Y:%f", e->getScrollX(), e->getScrollY());
}
//
// void StartMenu::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
//{
//    AXLOG("onKeyPressed, keycode: %d", static_cast<int>(code));
//}
//
// void StartMenu::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
//{
//    AXLOG("onKeyReleased, keycode: %d", static_cast<int>(code));
//}

void StartMenu::update(float delta)
{
    // switch (_gameState)
    //{
    // case GameState::init:
    //{
    //     _gameState = GameState::update;
    //     break;
    // }

    // case GameState::update:
    //{
    //     /////////////////////////////
    //     // Add your codes below...like....
    //     //
    //     // UpdateJoyStick();
    //     // UpdatePlayer();
    //     // UpdatePhysics();
    //     // ...
    //     break;
    // }

    // case GameState::pause:
    //{
    //     /////////////////////////////
    //     // Add your codes below...like....
    //     //
    //     // anyPauseStuff()

    //    break;
    //}

    // case GameState::menu1:
    //{    /////////////////////////////
    //     // Add your codes below...like....
    //     //
    //     // UpdateMenu1();
    //     break;
    // }

    // case GameState::menu2:
    //{    /////////////////////////////
    //     // Add your codes below...like....
    //     //
    //     // UpdateMenu2();
    //     break;
    // }

    // case GameState::end:
    //{    /////////////////////////////
    //     // Add your codes below...like....
    //     //
    //     // CleanUpMyCrap();
    //     menuCloseCallback(this);
    //     break;
    // }

    //} //switch
}

void StartMenu::menuCloseCallback(ax::Object* sender)
{
    AXLOG("Quit button clicked");
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void StartMenu::menuStartCallback(ax::Object* sender)
{
    AXLOG("Start button clicked");
    //this->getEventDispatcher()->removeAllEventListeners();
    _director->replaceScene(ax::utils::createInstance<StripGameScene>());
}
