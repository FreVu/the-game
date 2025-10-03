#pragma once

#include "axmol.h"

#include "Engine/Girl.h"

class MainScene : public ax::Scene
{
public:
    bool init() override;
    void update(float delta) override;

    // touch
    void onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event);

    // mouse
    void onMouseDown(ax::Event* event);
    void onMouseUp(ax::Event* event);
    void onMouseMove(ax::Event* event);
    void onMouseScroll(ax::Event* event);

    // Keyboard
    void onKeyPressed(ax::EventKeyboard::KeyCode code, ax::Event* event);
    void onKeyReleased(ax::EventKeyboard::KeyCode code, ax::Event* event);

    // a selector callback
    void menuCloseCallback(ax::Object* sender);

    // Portrait zones
    void createPortraitZones(const ax::Size& visibleSize, const ax::Vec2& origin);

    MainScene();
    ~MainScene();

private:

    std::vector<Girl> _girls;
    
    // Portrait zones
    ax::Sprite* _portrait1 = nullptr;
    ax::Sprite* _portrait2 = nullptr;

    ax::EventListenerTouchAllAtOnce* _touchListener = nullptr;
    ax::EventListenerKeyboard* _keyboardListener    = nullptr;
    ax::EventListenerMouse* _mouseListener          = nullptr;
};
