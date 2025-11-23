#pragma once

#include "axmol.h"
#include <ui/UIWidget.h>
#include <ui/UIButton.h>

#include <string>
#include <functional>

namespace UIHelper
{

class IntegerControl : public ax::Node
{
public:
    static IntegerControl* create(const std::string& buttonImage,
                                  int initialValue,
                                  int minValue,
                                  int maxValue,
                                  int posX,
                                  int posY,
                                  int buttonSizeX,
                                  int buttonSizeY,
                                  int labelWidth,
                                  const std::string& topLabelText,
                                  const std::string& middleImage = "")
    {
        auto control = new (std::nothrow) IntegerControl();
        if (control && control->init(buttonImage, initialValue, minValue, maxValue, posX, posY, buttonSizeX, buttonSizeY, labelWidth, topLabelText, middleImage))
        {
            control->autorelease();
            return control;
        }
        delete control;
        return nullptr;
    }

    int getValue() const { return _value; }
    
    void setValue(int value)
    {
        _value = std::max(_minValue, std::min(_maxValue, value));
        updateDisplay();
    }

    void setMaxValue(int maxValue)
    {
        _maxValue = maxValue;
        // Clamp current value if it exceeds new max
        if (_value > _maxValue)
        {
            _value = _maxValue;
        }
        updateDisplay();
    }

    Node* getContainer() { return this; }

private:
    bool init(const std::string& buttonImage,
              int initialValue,
              int minValue,
              int maxValue,
              int posX,
              int posY,
              int buttonSizeX,
              int buttonSizeY,
              int labelWidth,
              const std::string& topLabelText,
              const std::string& middleImage)
    {
        if (!Node::init())
        {
            return false;
        }

        _value = std::max(minValue, std::min(maxValue, initialValue));
        _minValue = minValue;
        _maxValue = maxValue;

        const int spacing = 5;
        const int topLabelSpacing = 5;
        // Position children relative to container origin (0,0)
        // Container will be positioned at (posX, posY)
        const int centerX = 0;
        const int centerY = 0;

        // Create top label if text is provided
        if (!topLabelText.empty())
        {
            _topLabel = ax::Label::createWithTTF(topLabelText, "fonts/Arial.ttf", 16);
            if (_topLabel == nullptr)
            {
                return false;
            }
            float topLabelY = centerY + buttonSizeY / 2 + topLabelSpacing + 10; // Position above buttons
            _topLabel->setPosition(ax::Vec2(centerX, topLabelY));
            _topLabel->setAlignment(ax::TextHAlignment::CENTER, ax::TextVAlignment::CENTER);
            this->addChild(_topLabel);
        }

        // Calculate evenly distributed positions for 4 elements: minus, value, icon, plus
        // Estimate icon size (will be scaled to button height)
        float iconWidth = buttonSizeY; // Assume square icon after scaling
        float totalWidth = buttonSizeX + spacing + labelWidth + spacing + iconWidth + spacing + buttonSizeX;
        float startX = centerX - totalWidth / 2;
        
        // Position each element evenly
        float minusX = startX + buttonSizeX / 2;
        float valueX = startX + buttonSizeX + spacing + labelWidth / 2;
        float iconX = startX + buttonSizeX + spacing + labelWidth + spacing + iconWidth / 2;
        float plusX = startX + buttonSizeX + spacing + labelWidth + spacing + iconWidth + spacing + buttonSizeX / 2;

        // Create minus button
        _minusButton = ax::ui::Button::create(buttonImage, "", "");
        if (_minusButton == nullptr || _minusButton->getContentSize().width <= 0 || _minusButton->getContentSize().height <= 0)
        {
            return false;
        }
        _minusButton->setContentSize(ax::Vec2(buttonSizeX, buttonSizeY));
        _minusButton->setSizeType(ax::ui::Widget::SizeType::ABSOLUTE);
        _minusButton->ignoreContentAdaptWithSize(false);
        _minusButton->setTitleText("-");
        _minusButton->draw();
        _minusButton->setPosition(ax::Vec2(minusX, centerY));
        _minusButton->addClickEventListener(AX_CALLBACK_1(IntegerControl::onMinusClicked, this));
        this->addChild(_minusButton);

        // Create label for value
        _valueLabel = ax::Label::createWithTTF(std::to_string(_value), "fonts/Arial.ttf", 20);
        if (_valueLabel == nullptr)
        {
            return false;
        }
        _valueLabel->setPosition(ax::Vec2(valueX, centerY));
        _valueLabel->setContentSize(ax::Size(labelWidth, buttonSizeY));
        _valueLabel->setAlignment(ax::TextHAlignment::CENTER, ax::TextVAlignment::CENTER);
        this->addChild(_valueLabel);

        // Create middle image after value label if provided
        if (!middleImage.empty())
        {
            _middleImage = ax::Sprite::create(middleImage);
            if (_middleImage != nullptr)
            {
                _middleImage->setPosition(ax::Vec2(iconX, centerY));
                // Scale image to fit button height
                float imageScale = buttonSizeY / _middleImage->getContentSize().height;
                _middleImage->setScale(imageScale);
                this->addChild(_middleImage);
            }
        }

        // Create plus button
        _plusButton = ax::ui::Button::create(buttonImage, "", "");
        if (_plusButton == nullptr || _plusButton->getContentSize().width <= 0 || _plusButton->getContentSize().height <= 0)
        {
            return false;
        }
        _plusButton->setContentSize(ax::Vec2(buttonSizeX, buttonSizeY));
        _plusButton->setSizeType(ax::ui::Widget::SizeType::ABSOLUTE);
        _plusButton->ignoreContentAdaptWithSize(false);
        _plusButton->setTitleText("+");
        _plusButton->draw();
        _plusButton->setPosition(ax::Vec2(plusX, centerY));
        _plusButton->addClickEventListener(AX_CALLBACK_1(IntegerControl::onPlusClicked, this));
        this->addChild(_plusButton);

        // Set container position to the requested position
        this->setPosition(ax::Vec2(posX, posY));

        updateDisplay();
        return true;
    }

    void updateDisplay()
    {
        if (_valueLabel)
        {
            _valueLabel->setString(std::to_string(_value));
        }
        if (_minusButton)
        {
            _minusButton->setEnabled(_value > _minValue);
        }
        if (_plusButton)
        {
            _plusButton->setEnabled(_value < _maxValue);
        }
    }

    void onMinusClicked(ax::Object* sender)
    {
        if (_value > _minValue)
        {
            _value--;
            updateDisplay();
        }
    }

    void onPlusClicked(ax::Object* sender)
    {
        if (_value < _maxValue)
        {
            _value++;
            updateDisplay();
        }
    }

    int _value;
    int _minValue;
    int _maxValue;
    ax::ui::Button* _minusButton = nullptr;
    ax::Label* _valueLabel       = nullptr;
    ax::ui::Button* _plusButton = nullptr;
    ax::Label* _topLabel         = nullptr;
    ax::Sprite* _middleImage     = nullptr;
};

class ValueDisplay : public ax::Node
{
public:
    static ValueDisplay* create(int initialValue,
                                int posX,
                                int posY,
                                int labelWidth,
                                const std::string& topLabelText,
                                const std::string& iconImage)
    {
        auto display = new (std::nothrow) ValueDisplay();
        if (display && display->init(initialValue, posX, posY, labelWidth, topLabelText, iconImage))
        {
            display->autorelease();
            return display;
        }
        delete display;
        return nullptr;
    }

    int getValue() const { return _value; }
    
    void setValue(int value)
    {
        _value = value;
        updateDisplay();
    }

    ax::Node* getContainer() { return this; }

private:
    bool init(int initialValue,
              int posX,
              int posY,
              int labelWidth,
              const std::string& topLabelText,
              const std::string& iconImage)
    {
        if (!ax::Node::init())
        {
            return false;
        }

        _value = initialValue;

        const int spacing = 5;
        const int topLabelSpacing = 5;
        const int iconSize = 30; // Icon size (will be scaled)
        // Position children relative to container origin (0,0)
        // Container will be positioned at (posX, posY)
        const int centerX = 0;
        const int centerY = 0;

        // Create top label if text is provided
        if (!topLabelText.empty())
        {
            _topLabel = ax::Label::createWithTTF(topLabelText, "fonts/Arial.ttf", 16);
            if (_topLabel == nullptr)
            {
                return false;
            }
            float topLabelY = centerY + iconSize / 2 + topLabelSpacing + 10; // Position above elements
            _topLabel->setPosition(ax::Vec2(centerX, topLabelY));
            _topLabel->setAlignment(ax::TextHAlignment::CENTER, ax::TextVAlignment::CENTER);
            this->addChild(_topLabel);
        }

        // Calculate evenly distributed positions for 2 elements: value and icon
        float totalWidth = labelWidth + spacing + iconSize;
        float startX = centerX - totalWidth / 2;
        
        // Position each element
        float valueX = startX + labelWidth / 2;
        float iconX = startX + labelWidth + spacing + iconSize / 2;

        // Create label for value
        _valueLabel = ax::Label::createWithTTF(std::to_string(_value), "fonts/Arial.ttf", 20);
        if (_valueLabel == nullptr)
        {
            return false;
        }
        _valueLabel->setPosition(ax::Vec2(valueX, centerY));
        _valueLabel->setContentSize(ax::Size(labelWidth, iconSize));
        _valueLabel->setAlignment(ax::TextHAlignment::CENTER, ax::TextVAlignment::CENTER);
        this->addChild(_valueLabel);

        // Create icon image if provided
        if (!iconImage.empty())
        {
            _iconImage = ax::Sprite::create(iconImage);
            if (_iconImage != nullptr)
            {
                _iconImage->setPosition(ax::Vec2(iconX, centerY));
                // Scale image to fit icon size
                float imageScale = iconSize / _iconImage->getContentSize().height;
                _iconImage->setScale(imageScale);
                this->addChild(_iconImage);
            }
        }

        // Set container position to the requested position
        this->setPosition(ax::Vec2(posX, posY));

        updateDisplay();
        return true;
    }

    void updateDisplay()
    {
        if (_valueLabel)
        {
            _valueLabel->setString(std::to_string(_value));
        }
    }

    int _value;
    ax::Label* _valueLabel = nullptr;
    ax::Label* _topLabel = nullptr;
    ax::Sprite* _iconImage = nullptr;
};

class Helper
{
public:
    static ax::ui::Button* createButton(const std::string& normalImage,
                                        const std::string& selectedImage,
                                        const std::string& disabledImage,
                                        const std::string& text,
                                        int posX,
                                        int posY,
                                        int sizeX,
                                        int sizeY,
                                        const ax::ui::Widget::ccWidgetClickCallback& callback)
    {
        auto button = ax::ui::Button::create(normalImage, selectedImage, disabledImage);

        if (button == nullptr || button->getContentSize().width <= 0 || button->getContentSize().height <= 0)
        {
            throw std::runtime_error("Error loading button images: " + normalImage + ", " + selectedImage + ", " +
                                     disabledImage);
        }
        else
        {
            button->setContentSize(ax::Vec2(sizeX, sizeY));
            button->setSizeType(ax::ui::Widget::SizeType::ABSOLUTE);
            button->ignoreContentAdaptWithSize(false);
            button->setTitleText(text);
            button->draw();
            button->addClickEventListener(callback);
            button->setPosition(ax::Vec2(posX, posY));
        }

        return button;
    }

    static IntegerControl* createIntegerControl(const std::string& buttonImage,
                                                int initialValue,
                                                int minValue,
                                                int maxValue,
                                                int posX,
                                                int posY,
                                                int buttonSizeX,
                                                int buttonSizeY,
                                                int labelWidth,
                                                const std::string& topLabelText,
                                                const std::string& middleImage)
    {
        return IntegerControl::create(buttonImage, initialValue, minValue, maxValue, posX, posY, buttonSizeX, buttonSizeY, labelWidth, topLabelText, middleImage);
    }

    static ValueDisplay* createValueDisplay(int initialValue,
                                            int posX,
                                            int posY,
                                            int labelWidth,
                                            const std::string& topLabelText,
                                            const std::string& iconImage)
    {
        return ValueDisplay::create(initialValue, posX, posY, labelWidth, topLabelText, iconImage);
    }
};

}  // namespace UI
