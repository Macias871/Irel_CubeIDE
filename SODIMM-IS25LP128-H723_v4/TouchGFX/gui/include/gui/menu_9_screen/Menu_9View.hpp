#ifndef MENU_9VIEW_HPP
#define MENU_9VIEW_HPP

#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>

class Menu_9View : public Menu_9ViewBase
{
public:
    Menu_9View();
    virtual ~Menu_9View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MENU_9VIEW_HPP
