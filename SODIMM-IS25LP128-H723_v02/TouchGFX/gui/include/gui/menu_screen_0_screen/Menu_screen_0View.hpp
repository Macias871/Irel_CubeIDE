#ifndef MENU_SCREEN_0VIEW_HPP
#define MENU_SCREEN_0VIEW_HPP

#include <gui_generated/menu_screen_0_screen/Menu_screen_0ViewBase.hpp>
#include <gui/menu_screen_0_screen/Menu_screen_0Presenter.hpp>

class Menu_screen_0View : public Menu_screen_0ViewBase
{
public:
    Menu_screen_0View();
    virtual ~Menu_screen_0View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MENU_SCREEN_0VIEW_HPP
