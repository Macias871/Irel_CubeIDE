#ifndef MENU_9VIEW_HPP
#define MENU_9VIEW_HPP
#include <gui/containers/Menu_buttons_container.hpp>
#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>




class Menu_9View : public Menu_9ViewBase
{
public:
    Menu_9View();
    virtual ~Menu_9View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void scrollListUpdateItem(Menu_buttons_container& item, int16_t itemIndex);


protected:
    Callback<Menu_9View,int16_t> scrollList_ItemSelectedCallback;
private:
    void scrollList_ItemSelectedHandler(int16_t itemSelected);
};

#endif // MENU_9VIEW_HPP
