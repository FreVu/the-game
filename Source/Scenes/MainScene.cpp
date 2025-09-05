#include "MainScene.h"

using namespace ax;

//static int s_sceneID = 1000;

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

    auto visibleSize = _director->getVisibleSize();
    auto origin      = _director->getVisibleOrigin();
    auto safeArea    = _director->getSafeAreaRect();
    auto safeOrigin  = safeArea.origin;

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           AX_CALLBACK_1(MainScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // Some templates (uncomment what you  need)
    //_touchListener                 = EventListenerTouchAllAtOnce::create();
    //_touchListener->onTouchesBegan = AX_CALLBACK_2(MainScene::onTouchesBegan, this);
    //_touchListener->onTouchesMoved = AX_CALLBACK_2(MainScene::onTouchesMoved, this);
    //_touchListener->onTouchesEnded = AX_CALLBACK_2(MainScene::onTouchesEnded, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

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

    // add a label shows "Hello World"
    // create and initialize a label

    auto title = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (title == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        title->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - title->getContentSize().height));
        this->addChild(title, 1);
    }

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png"sv);
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //    auto drawNode = DrawNode::create();
    //    drawNode->setPosition(Vec2(0, 0));
    //    addChild(drawNode);

    //    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4F::BLUE);
    //}

    for (unsigned int i = 0; i < 4; i++)
    {
        Girl girl;
        _girls.emplace_back(girl);
    }


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
    // AXLOGD("onMouseMove detected, X:{}  Y:{}", e->getCursorX(), e->getCursorY());
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    // AXLOGD("onMouseScroll detected, X:{}  Y:{}", e->getScrollX(), e->getScrollY());
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    //AXLOGD("Scene: #{} onKeyPressed, keycode: {}", _sceneID, static_cast<int>(code));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    AXLOGD("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void MainScene::update(float delta)
{
}

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

MainScene::MainScene()
{
    //_sceneID = ++s_sceneID;
    //AXLOGD("Scene: ctor: #{}", _sceneID);
}

MainScene::~MainScene()
{
    //AXLOGD("~Scene: dtor: #{}", _sceneID);

    if (_touchListener)
        _eventDispatcher->removeEventListener(_touchListener);
    if (_keyboardListener)
        _eventDispatcher->removeEventListener(_keyboardListener);
    if (_mouseListener)
        _eventDispatcher->removeEventListener(_mouseListener);
    //_sceneID = -1;
}
