/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <BitmapDatabase.hpp>

Menu_buttons_containerBase::Menu_buttons_containerBase()
{
    setWidth(460);
    setHeight(64);
    btn_pos.setXY(10, 11);
    btn_pos.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_IN_MENU_ON_ID));

    add(btn_pos);
}

Menu_buttons_containerBase::~Menu_buttons_containerBase()
{

}

void Menu_buttons_containerBase::initialize()
{

}

