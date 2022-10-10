#ifndef MENU_9VIEW_HPP
#define MENU_9VIEW_HPP

#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <gui/containers/Menu_buttons_container.hpp>
#include <gui/test_menu_screen/TEST_MenuView.hpp>
#include <touchgfx/Utils.hpp>
#include <BitmapDatabase.hpp>
#include <gui/containers/Back_menu_container.hpp>
#include <gui_generated/common/FrontendApplicationBase.hpp>
#include "../Structures.h"
//#include <gui/common/FrontendHeap.hpp>
//#include <gui/model/Model.hpp>






void Change_screen(void);




class Menu_9View : public Menu_9ViewBase
{
public:
    Menu_9View();
    virtual ~Menu_9View() {}

    virtual void setupScreen();
    virtual void tearDownScreen();
    void fill_positions_menu(TGFX_Menu_t Menu);


    void Open_callback_menu(TGFX_Menu_t Menu);
    void listElementClicked(Menu_buttons_container& element);
    void BackElementClicked(Back_menu_container& element);


protected:



    static const int numberOfListElements = 100;
    Menu_buttons_container scrollListListItems[numberOfListElements];


    Callback<Menu_9View, Menu_buttons_container&> listElementClickedCallback;
    Callback<Menu_9View, Back_menu_container&> BackElementClickedCallback;

};

#endif // MENU_9VIEW_HPP
