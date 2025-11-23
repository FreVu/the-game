#pragma once

#include "axmol.h"

#include "Engine/Girl.h"

class StripGameScene : public ax::Scene
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
    void createPortraitZones();

    StripGameScene();
    ~StripGameScene();

private:

    class TurnBets
    {
        public:

            int _girlAttack;
            int _girlDefense;

            int _protagonistAttack;
            int _protagonistDefense;
    };

    std::vector<TurnBets> _turnBets;

    // Portrait zones
    std::vector<ax::Sprite*> _portrait;

    ax::EventListenerTouchAllAtOnce* _touchListener = nullptr;
    ax::EventListenerKeyboard* _keyboardListener    = nullptr;
    ax::EventListenerMouse* _mouseListener          = nullptr;

    void flipCallback(ax::Object* sender, int index);
    void lost(ax::Object* sender, int index);
    void randomNext(ax::Object* sender);
    void endTurnCallback(ax::Object* sender, int index);
};
