/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/menu_screen/MenuViewBase.hpp>
#include <touchgfx/Color.hpp>

MenuViewBase::MenuViewBase()
{

    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 800, 480);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    box2.setPosition(718, 77, 50, 97);
    box2.setColor(touchgfx::Color::getColorFromRGB(207, 41, 124));

    box2_1.setPosition(257, 52, 207, 402);
    box2_1.setColor(touchgfx::Color::getColorFromRGB(207, 41, 124));

    box2_1_1.setPosition(42, 125, 668, 15);
    box2_1_1.setColor(touchgfx::Color::getColorFromRGB(207, 41, 124));

    add(__background);
    add(box1);
    add(box2);
    add(box2_1);
    add(box2_1_1);
}

void MenuViewBase::setupScreen()
{

}
