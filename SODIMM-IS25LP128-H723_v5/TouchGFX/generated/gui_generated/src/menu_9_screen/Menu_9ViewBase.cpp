/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


Menu_9ViewBase::Menu_9ViewBase() :
    updateItemCallback(this, &Menu_9ViewBase::updateItemCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 800);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    backgroud.setXY(0, 0);
    backgroud.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_BLACK_ID));

    menu_tree_title_container1.setXY(0, 0);

    back_menu_container_11.setXY(0, 732);

    scrollList.setPosition(10, 68, 440, 572);
    scrollList.setHorizontal(false);
    scrollList.setCircular(false);
    scrollList.setEasingEquation(touchgfx::EasingEquations::backEaseOut);
    scrollList.setSwipeAcceleration(10);
    scrollList.setDragAcceleration(10);
    scrollList.setNumberOfItems(2);
    scrollList.setPadding(0, 0);
    scrollList.setSnapping(false);
    scrollList.setDrawableSize(52, 0);
    scrollList.setDrawables(scrollListListItems, updateItemCallback);

    add(__background);
    add(backgroud);
    add(menu_tree_title_container1);
    add(back_menu_container_11);
    add(scrollList);
}

void Menu_9ViewBase::setupScreen()
{
    menu_tree_title_container1.initialize();
    back_menu_container_11.initialize();
    scrollList.initialize();
    for (int i = 0; i < scrollListListItems.getNumberOfDrawables(); i++)
    {
        scrollListListItems[i].initialize();
    }
}

void Menu_9ViewBase::updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex)
{
    if (items == &scrollListListItems)
    {
        touchgfx::Drawable* d = items->getDrawable(containerIndex);
        Menu_buttons_container* cc = (Menu_buttons_container*)d;
        scrollListUpdateItem(*cc, itemIndex);
    }
}
