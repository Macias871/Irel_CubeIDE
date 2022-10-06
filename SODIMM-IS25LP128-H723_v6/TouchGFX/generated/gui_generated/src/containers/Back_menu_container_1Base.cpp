/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/Back_menu_container_1Base.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Back_menu_container_1Base::Back_menu_container_1Base() :
    buttonCallback(this, &Back_menu_container_1Base::buttonCallbackHandler)
{
    setWidth(480);
    setHeight(68);
    line1.setPosition(0, 9, 480, 25);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(70, 105, 138));
    line1.setPainter(line1Painter);
    line1.setStart(5, 4);
    line1.setEnd(475, 4);
    line1.setLineWidth(5);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);

    button1.setXY(123, 21);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    button1.setAction(buttonCallback);

    textArea1.setXY(194, 30);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(33, 133, 126));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T_WSTECZ));

    add(line1);
    add(button1);
    add(textArea1);
}

Back_menu_container_1Base::~Back_menu_container_1Base()
{

}

void Back_menu_container_1Base::initialize()
{

}

void Back_menu_container_1Base::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //back_inter
        //When button1 clicked call virtual function
        //Call Back_clicked
        Back_clicked();
    }
}

