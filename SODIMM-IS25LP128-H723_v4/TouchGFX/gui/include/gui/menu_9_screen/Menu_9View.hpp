#ifndef MENU_9VIEW_HPP
#define MENU_9VIEW_HPP

#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <touchgfx/Utils.hpp>



#define Menu_items 30



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

class Menu_9View : public Menu_9ViewBase
{
public:
    Menu_9View();
    virtual ~Menu_9View() {}
    virtual void setupScreen();
    void fill_positions_menu(TGFX_Menu_t Menu);
    virtual void tearDownScreen();

    //virtual void GetItem(Menu_buttons_container& item, TGFX_Menu_t Menu);
    void ButtonsContainerClickedHandler(TGFX_Menu_t Menu);

protected:

    Callback<Menu_9View, TGFX_Menu_t> viewCallback;
    /*     * Callback Declarations     */
   // touchgfx::Callback<Menu_9View> customContainer1Trigger1Callback;
    /*     * Callback Handler Declarations     */
   // void customContainer1Trigger1CallbackHandler();
};

#endif // MENU_9VIEW_HPP
