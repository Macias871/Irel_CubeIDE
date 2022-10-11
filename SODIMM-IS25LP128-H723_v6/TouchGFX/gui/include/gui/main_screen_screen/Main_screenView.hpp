#ifndef MAIN_SCREENVIEW_HPP
#define MAIN_SCREENVIEW_HPP

#include <gui_generated/main_screen_screen/Main_screenViewBase.hpp>
#include <gui/main_screen_screen/Main_screenPresenter.hpp>
#include "../Structures.h"

void Change_screen();

class Main_screenView : public Main_screenViewBase
{
public:
    Main_screenView();
    virtual ~Main_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void shortcut_goto_test();
    virtual void Set_date_time();
protected:
};

#endif // MAIN_SCREENVIEW_HPP
