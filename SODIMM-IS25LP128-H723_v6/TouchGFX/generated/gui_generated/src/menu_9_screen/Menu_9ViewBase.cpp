/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


Menu_9ViewBase::Menu_9ViewBase()
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 800);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    backgroud.setXY(0, 0);
    backgroud.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_BLACK_ID));

    menu_tree_title_cont.setXY(0, 0);

    back_menu_cont.setXY(0, 732);

    scrollcnt.setPosition(0, 68, 480, 664);
    scrollcnt.setScrollbarsColor(touchgfx::Color::getColorFromRGB(49, 192, 224));

    list.setDirection(touchgfx::SOUTH);
    list.setPosition(115, 0, 250, 250);
    scrollcnt.add(list);
    scrollcnt.setScrollbarsPermanentlyVisible();

    add(__background);
    add(backgroud);
    add(menu_tree_title_cont);
    add(back_menu_cont);
    add(scrollcnt);
}

void Menu_9ViewBase::setupScreen()
{
    menu_tree_title_cont.initialize();
    back_menu_cont.initialize();
}
