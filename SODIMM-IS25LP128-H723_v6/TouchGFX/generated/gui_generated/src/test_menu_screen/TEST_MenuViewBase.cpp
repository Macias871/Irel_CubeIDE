/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/test_menu_screen/TEST_MenuViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


TEST_MenuViewBase::TEST_MenuViewBase() :
    buttonCallback(this, &TEST_MenuViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 800);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_BLACK_ID));

    Test_menu_tree_title.setXY(0, 0);

    Test_menu_back_cont.setXY(0, 732);

    Test_menu_scroll.setPosition(0, 151, 480, 581);
    Test_menu_scroll.setScrollbarsColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    I1_wyp_ico.setXY(240, 30);
    I1_wyp_ico.setBitmap(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_RED_ID));
    Test_menu_scroll.add(I1_wyp_ico);

    I2_pnc_ico.setXY(240, 80);
    I2_pnc_ico.setBitmap(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_RED_ID));
    Test_menu_scroll.add(I2_pnc_ico);

    I3_pop_ico.setXY(240, 130);
    I3_pop_ico.setBitmap(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_RED_ID));
    Test_menu_scroll.add(I3_pop_ico);

    I4_pwc_ico.setXY(240, 180);
    I4_pwc_ico.setBitmap(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_RED_ID));
    Test_menu_scroll.add(I4_pwc_ico);

    I5_zas_ico.setXY(240, 230);
    I5_zas_ico.setBitmap(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_RED_ID));
    Test_menu_scroll.add(I5_zas_ico);

    I6_sspr_ico.setXY(240, 280);
    I6_sspr_ico.setBitmap(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_RED_ID));
    Test_menu_scroll.add(I6_sspr_ico);

    I7_wedo_ico.setXY(240, 330);
    I7_wedo_ico.setBitmap(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_RED_ID));
    Test_menu_scroll.add(I7_wedo_ico);

    WPR_lab.setXY(246, 39);
    WPR_lab.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    WPR_lab.setLinespacing(0);
    WPR_lab.setTypedText(touchgfx::TypedText(T_ICO_WPR_T));
    Test_menu_scroll.add(WPR_lab);

    PNC_lab.setXY(246, 89);
    PNC_lab.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    PNC_lab.setLinespacing(0);
    PNC_lab.setTypedText(touchgfx::TypedText(T_ICO_PNC_T));
    Test_menu_scroll.add(PNC_lab);

    POP_lab.setXY(246, 139);
    POP_lab.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    POP_lab.setLinespacing(0);
    POP_lab.setTypedText(touchgfx::TypedText(T_ICO_POP_T));
    Test_menu_scroll.add(POP_lab);

    PWC_lab.setXY(246, 189);
    PWC_lab.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    PWC_lab.setLinespacing(0);
    PWC_lab.setTypedText(touchgfx::TypedText(T_ICO_PWC_T));
    Test_menu_scroll.add(PWC_lab);

    PWR_lab.setXY(246, 239);
    PWR_lab.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    PWR_lab.setLinespacing(0);
    PWR_lab.setTypedText(touchgfx::TypedText(T_ICO_PWR_T));
    Test_menu_scroll.add(PWR_lab);

    SPR_lab.setXY(246, 290);
    SPR_lab.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    SPR_lab.setLinespacing(0);
    SPR_lab.setTypedText(touchgfx::TypedText(T_ICO_CMOT_T));
    Test_menu_scroll.add(SPR_lab);

    EXTIN_lab.setXY(246, 339);
    EXTIN_lab.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    EXTIN_lab.setLinespacing(0);
    EXTIN_lab.setTypedText(touchgfx::TypedText(T_ICO_WEDO_T));
    Test_menu_scroll.add(EXTIN_lab);

    Btn_Spr.setXY(2, 30);
    Btn_Spr.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_Spr.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_Spr);

    Btn_Pdz.setXY(2, 80);
    Btn_Pdz.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_Pdz.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_Pdz);

    Btn_Pco.setXY(2, 130);
    Btn_Pco.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_Pco.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_Pco);

    Btn_Pcwu.setXY(2, 180);
    Btn_Pcwu.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_Pcwu.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_Pcwu);

    Btn_3d.setXY(2, 230);
    Btn_3d.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_3d.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_3d);

    Btn_Gr1.setXY(2, 280);
    Btn_Gr1.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_Gr1.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_Gr1);

    Btn_Gr2.setXY(2, 330);
    Btn_Gr2.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_Gr2.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_Gr2);

    Btn_Zz.setXY(2, 380);
    Btn_Zz.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_OFF_ID), touchgfx::Bitmap(BITMAP_BUTTON_SMALL_IN_MENU_ON_ID));
    Btn_Zz.setAction(buttonCallback);
    Test_menu_scroll.add(Btn_Zz);

    Bt2.setXY(8, 89);
    Bt2.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt2.setLinespacing(0);
    Bt2.setTypedText(touchgfx::TypedText(T_BTN_PDZ_T));
    Test_menu_scroll.add(Bt2);

    Bt1.setXY(8, 39);
    Bt1.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt1.setLinespacing(0);
    Bt1.setTypedText(touchgfx::TypedText(T_BTN_SPR_T));
    Test_menu_scroll.add(Bt1);

    Bt3.setXY(8, 139);
    Bt3.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt3.setLinespacing(0);
    Bt3.setTypedText(touchgfx::TypedText(T_BTN_PCO_T));
    Test_menu_scroll.add(Bt3);

    Bt4.setXY(8, 189);
    Bt4.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt4.setLinespacing(0);
    Bt4.setTypedText(touchgfx::TypedText(T_BTN_PCWU_T));
    Test_menu_scroll.add(Bt4);

    Bt5.setXY(8, 239);
    Bt5.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt5.setLinespacing(0);
    Bt5.setTypedText(touchgfx::TypedText(T_BTN_3DV_T));
    Test_menu_scroll.add(Bt5);

    Bt6.setXY(8, 290);
    Bt6.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt6.setLinespacing(0);
    Bt6.setTypedText(touchgfx::TypedText(T_BTN_GR1_T));
    Test_menu_scroll.add(Bt6);

    Bt7.setXY(8, 339);
    Bt7.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt7.setLinespacing(0);
    Bt7.setTypedText(touchgfx::TypedText(T_BTN_GR2_T));
    Test_menu_scroll.add(Bt7);

    Bt8.setXY(8, 389);
    Bt8.setColor(touchgfx::Color::getColorFromRGB(46, 147, 209));
    Bt8.setLinespacing(0);
    Bt8.setTypedText(touchgfx::TypedText(T_BTN_ZZ));
    Test_menu_scroll.add(Bt8);
    Test_menu_scroll.setScrollbarsPermanentlyVisible();

    Slave_scroll_cont.setPosition(0, 68, 480, 83);
    Slave_scroll_cont.enableHorizontalScroll(false);
    Slave_scroll_cont.enableVerticalScroll(false);
    Slave_scroll_cont.setScrollbarsColor(touchgfx::Color::getColorFromRGB(39, 183, 219));

    Btn1.setXY(14, 19);
    Btn1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_INACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_ACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_NORMAL_ID));
    Btn1.setSelected(true);
    Btn1.setDeselectionEnabled(true);
    Slave_scroll_cont.add(Btn1);

    Btn2.setXY(97, 19);
    Btn2.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_INACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_ACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_NORMAL_ID));
    Btn2.setSelected(false);
    Btn2.setDeselectionEnabled(false);
    Slave_scroll_cont.add(Btn2);

    Btn3.setXY(181, 19);
    Btn3.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_INACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_ACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_NORMAL_ID));
    Btn3.setSelected(false);
    Btn3.setDeselectionEnabled(false);
    Slave_scroll_cont.add(Btn3);

    Btn4.setXY(263, 19);
    Btn4.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_INACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_ACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_NORMAL_ID));
    Btn4.setSelected(false);
    Btn4.setDeselectionEnabled(false);
    Slave_scroll_cont.add(Btn4);

    Btn5.setXY(347, 19);
    Btn5.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_INACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_ACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_NORMAL_ID));
    Btn5.setSelected(false);
    Btn5.setDeselectionEnabled(false);
    Slave_scroll_cont.add(Btn5);

    Btn6.setXY(422, 19);
    Btn6.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_INACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_ACTIVE_ID), touchgfx::Bitmap(BITMAP_BLUE_RADIO_BUTTONS_RADIO_BUTTON_NORMAL_ID));
    Btn6.setSelected(false);
    Btn6.setDeselectionEnabled(false);
    Slave_scroll_cont.add(Btn6);

    T6.setXY(438, 29);
    T6.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    T6.setLinespacing(0);
    T6.setTypedText(touchgfx::TypedText(T___SINGLEUSE_3OQQ));
    Slave_scroll_cont.add(T6);

    T5.setXY(363, 29);
    T5.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    T5.setLinespacing(0);
    T5.setTypedText(touchgfx::TypedText(T___SINGLEUSE_D2CB));
    Slave_scroll_cont.add(T5);

    T4.setXY(279, 29);
    T4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    T4.setLinespacing(0);
    T4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_D0NX));
    Slave_scroll_cont.add(T4);

    T3.setXY(197, 29);
    T3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    T3.setLinespacing(0);
    T3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_H379));
    Slave_scroll_cont.add(T3);

    T2.setXY(113, 29);
    T2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    T2.setLinespacing(0);
    T2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_QM4U));
    Slave_scroll_cont.add(T2);

    T1.setXY(30, 29);
    T1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    T1.setLinespacing(0);
    T1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_N0ZN));
    Slave_scroll_cont.add(T1);
    Slave_scroll_cont.setScrollbarsVisible(false);

    add(__background);
    add(image1);
    add(Test_menu_tree_title);
    add(Test_menu_back_cont);
    add(Test_menu_scroll);
    add(Slave_scroll_cont);
    radioButtonGroup1.add(Btn1);
    radioButtonGroup1.add(Btn2);
    radioButtonGroup1.add(Btn3);
    radioButtonGroup1.add(Btn4);
    radioButtonGroup1.add(Btn5);
    radioButtonGroup1.add(Btn6);
}

void TEST_MenuViewBase::setupScreen()
{
    Test_menu_tree_title.initialize();
    Test_menu_back_cont.initialize();
}

void TEST_MenuViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &Btn_Spr)
    {
        //spr_clk
        //When Btn_Spr clicked call virtual function
        //Call btn_spr_clicked
        btn_spr_clicked();
    }
    else if (&src == &Btn_Pdz)
    {
        //pdz_clk
        //When Btn_Pdz clicked call virtual function
        //Call btn_pdz_clicked
        btn_pdz_clicked();
    }
    else if (&src == &Btn_Pco)
    {
        //pco_clk
        //When Btn_Pco clicked call virtual function
        //Call btn_pco_clicked
        btn_pco_clicked();
    }
    else if (&src == &Btn_Pcwu)
    {
        //pcwu_clk
        //When Btn_Pcwu clicked call virtual function
        //Call btn_pcwu_clicked
        btn_pcwu_clicked();
    }
    else if (&src == &Btn_3d)
    {
        //z3d_clk
        //When Btn_3d clicked call virtual function
        //Call btn_3d_clicked
        btn_3d_clicked();
    }
    else if (&src == &Btn_Gr1)
    {
        //gr1_clk
        //When Btn_Gr1 clicked call virtual function
        //Call btn_gr1_clicked
        btn_gr1_clicked();
    }
    else if (&src == &Btn_Gr2)
    {
        //gr2_clk
        //When Btn_Gr2 clicked call virtual function
        //Call btn_gr2_clicked
        btn_gr2_clicked();
    }
    else if (&src == &Btn_Zz)
    {
        //zz_clk
        //When Btn_Zz clicked call virtual function
        //Call btn_zz_clicked
        btn_zz_clicked();
    }
}
