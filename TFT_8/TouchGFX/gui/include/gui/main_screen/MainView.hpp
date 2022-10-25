#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>







class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void SPR();
    virtual void PDZ();
    virtual void PCO();
    virtual void PCWU();
    virtual void Z3D();
    virtual void GR1();
    virtual void GR2();
    virtual void ZEWZRD();
    virtual void handleTickEvent();



protected:
    uint8_t counter;
    bool flag;
};

#endif // MAINVIEW_HPP
