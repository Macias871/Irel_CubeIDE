/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/clock_settings_screen/Clock_settingsViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


Clock_settingsViewBase::Clock_settingsViewBase()
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 800);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_BLACK_ID));

    Clock_menu_tree_title_container.setXY(0, 0);

    Clock_back_menu_container.setXY(0, 732);

    HH_container.setXY(102, 153);

    MM_container.setXY(305, 153);

    DD_container.setXY(0, 400);

    MO_container.setXY(190, 400);

    YY_container.setXY(380, 400);

    T_hh.setXY(107, 129);
    T_hh.setColor(touchgfx::Color::getColorFromRGB(26, 122, 119));
    T_hh.setLinespacing(0);
    T_hh.setTypedText(touchgfx::TypedText(T_TIME_HH));

    T_mm.setXY(317, 129);
    T_mm.setColor(touchgfx::Color::getColorFromRGB(26, 122, 119));
    T_mm.setLinespacing(0);
    T_mm.setTypedText(touchgfx::TypedText(T_TIME_MM));

    T_dd.setXY(18, 376);
    T_dd.setColor(touchgfx::Color::getColorFromRGB(26, 122, 119));
    T_dd.setLinespacing(0);
    T_dd.setTypedText(touchgfx::TypedText(T_TIME_DD));

    T_mo.setXY(199, 376);
    T_mo.setColor(touchgfx::Color::getColorFromRGB(26, 122, 119));
    T_mo.setLinespacing(0);
    T_mo.setTypedText(touchgfx::TypedText(T_TIME_MO));

    T_yy.setXY(407, 376);
    T_yy.setColor(touchgfx::Color::getColorFromRGB(26, 122, 119));
    T_yy.setLinespacing(0);
    T_yy.setTypedText(touchgfx::TypedText(T_TIME_YY));

    add(__background);
    add(image1);
    add(Clock_menu_tree_title_container);
    add(Clock_back_menu_container);
    add(HH_container);
    add(MM_container);
    add(DD_container);
    add(MO_container);
    add(YY_container);
    add(T_hh);
    add(T_mm);
    add(T_dd);
    add(T_mo);
    add(T_yy);
}

void Clock_settingsViewBase::setupScreen()
{
    Clock_menu_tree_title_container.initialize();
    Clock_back_menu_container.initialize();
    HH_container.initialize();
    MM_container.initialize();
    DD_container.initialize();
    MO_container.initialize();
    YY_container.initialize();
}