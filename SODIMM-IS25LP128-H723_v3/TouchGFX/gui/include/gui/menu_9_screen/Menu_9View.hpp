#ifndef MENU_9VIEW_HPP
#define MENU_9VIEW_HPP
#include <gui/containers/Menu_buttons_container.hpp>
#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>





extern TGFX_Menu_t menu_9;
extern TGFX_Menu_t sub_menu_9_1;
	extern TGFX_Menu_t sub_menu_9_1_1;
	extern TGFX_Menu_t sub_menu_9_1_2;
	extern TGFX_Menu_t sub_menu_9_1_3;
	extern TGFX_Menu_t sub_menu_9_1_4;

extern TGFX_Menu_t sub_menu_9_2;
extern TGFX_Menu_t sub_menu_9_3;
extern TGFX_Menu_t sub_menu_9_4;
extern TGFX_Menu_t sub_menu_9_5;
extern TGFX_Menu_t sub_menu_9_6;

extern TGFX_Menu_t *Sub_menu;
extern TGFX_Menu_t *Temp_menu;
extern TGFX_Menu_t *TGFX_Actual_menu;
extern TGFX_Menu_t *Base_of_menu_struct_items[30];

class Menu_9View : public Menu_9ViewBase
{
public:
    Menu_9View();
    virtual ~Menu_9View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void scrollListUpdateItem(Menu_buttons_container& item, int16_t itemIndex, TGFX_Menu_t Menu);
    void listElementClicked(Menu_buttons_container& element);
    void fill_positions_menu(TGFX_Menu_t Menu);

protected:
    Callback<Menu_9View,int16_t> scrollList_ItemSelectedCallback;
private:
    void scrollList_ItemSelectedHandler(int16_t itemSelected);
};

#endif // MENU_9VIEW_HPP
