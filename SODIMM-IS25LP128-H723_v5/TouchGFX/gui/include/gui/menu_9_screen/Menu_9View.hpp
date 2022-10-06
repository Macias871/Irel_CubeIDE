#ifndef MENU_9VIEW_HPP
#define MENU_9VIEW_HPP

#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <touchgfx/Utils.hpp>



#define Menu_items 30



extern TGFX_Menu_t menu_9;
extern TGFX_Menu_t sub_menu_9_1;
	extern TGFX_Menu_t sub_menu_9_1_1;
	extern TGFX_Menu_t sub_menu_9_1_2;

	extern TGFX_Menu_t sub_menu_9_2_1 ;
		extern TGFX_Menu_t sub_menu_9_2_1_1 ;
		extern TGFX_Menu_t sub_menu_9_2_1_2 ;
		extern TGFX_Menu_t sub_menu_9_2_1_3 ;
			extern TGFX_Menu_t sub_menu_9_2_1_3_1;
			extern TGFX_Menu_t sub_menu_9_2_1_3_2;
			extern TGFX_Menu_t sub_menu_9_2_1_3_3;
			extern TGFX_Menu_t sub_menu_9_2_1_3_4;
			extern TGFX_Menu_t sub_menu_9_2_1_3_5;
			extern TGFX_Menu_t sub_menu_9_2_1_3_6;
			extern TGFX_Menu_t sub_menu_9_2_1_3_7;
			extern TGFX_Menu_t sub_menu_9_2_1_3_8;
			extern TGFX_Menu_t sub_menu_9_2_1_3_9;
			extern TGFX_Menu_t sub_menu_9_2_1_3_10;
			extern TGFX_Menu_t sub_menu_9_2_1_3_11;
			extern TGFX_Menu_t sub_menu_9_2_1_3_12;
			extern TGFX_Menu_t sub_menu_9_2_1_3_13;
		extern TGFX_Menu_t sub_menu_9_2_1_4 ;
	extern TGFX_Menu_t sub_menu_9_2_2;


	extern TGFX_Menu_t sub_menu_9_1_3;
	extern TGFX_Menu_t sub_menu_9_1_4;

extern TGFX_Menu_t sub_menu_9_2;
extern TGFX_Menu_t sub_menu_9_3;
extern TGFX_Menu_t sub_menu_9_4;
extern TGFX_Menu_t sub_menu_9_5;
extern TGFX_Menu_t sub_menu_9_6;

extern TGFX_Menu_t *Sub_menu;
extern TGFX_Menu_t Temp_menu;
extern TGFX_Menu_t *TGFX_Actual_menu;

class Menu_9View : public Menu_9ViewBase
{
public:
    Menu_9View();
    virtual ~Menu_9View() {}

    virtual void setupScreen();
    virtual void tearDownScreen();
    void fill_positions_menu(TGFX_Menu_t Menu);

    void listElementClicked(Menu_buttons_container& element);
    void BackElementClicked(Back_menu_container_1& element);

protected:

    Callback<Menu_9View, Menu_buttons_container&> listElementClickedCallback;
    Callback<Menu_9View, Back_menu_container_1&> BackElementClickedCallback;

};

#endif // MENU_9VIEW_HPP
