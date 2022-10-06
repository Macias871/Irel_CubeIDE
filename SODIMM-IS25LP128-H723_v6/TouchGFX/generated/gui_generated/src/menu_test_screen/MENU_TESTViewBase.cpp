/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/menu_test_screen/MENU_TESTViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


MENU_TESTViewBase::MENU_TESTViewBase() :
    buttonCallback(this, &MENU_TESTViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 800);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_BLACK_ID));

    back_menu_container_11.setXY(0, 732);

    menu_tree_title_container1.setXY(0, 0);

    button1.setXY(134, 459);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    button1.setAction(buttonCallback);

    add(__background);
    add(image1);
    add(back_menu_container_11);
    add(menu_tree_title_container1);
    add(button1);
}

void MENU_TESTViewBase::setupScreen()
{
    back_menu_container_11.initialize();
    menu_tree_title_container1.initialize();
}

void MENU_TESTViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction1
        //When button1 clicked change screen to MENU_TEST
        //Go to MENU_TEST with no screen transition
        application().gotoMENU_TESTScreenNoTransition();
    }
}
