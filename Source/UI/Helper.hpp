#pragma once

#include "axmol.h"
#include <ui/UIWidget.h>

USING_NS_AX;

namespace UI
{

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
            button->setContentSize(Vec2(sizeX, sizeY));
            button->setSizeType(ui::Widget::SizeType::ABSOLUTE);
            button->ignoreContentAdaptWithSize(false);
            button->setTitleText(text);
            button->draw();
            button->addClickEventListener(callback);
            button->setPosition(Vec2(posX, posY));
        }

        return button;
    }
};

}  // namespace UI
