#ifndef MENU_BUTTONS_CONTAINER_HPP
#define MENU_BUTTONS_CONTAINER_HPP

#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
//#include <gui/menu_9_screen/Menu_9View.hpp>


typedef struct TGFX_menu_struct TGFX_Menu_t;

struct TGFX_menu_struct {

	const char * name;
	TEXTS  Ttext;
	TGFX_Menu_t * next;
	TGFX_Menu_t * prev;
	TGFX_Menu_t * child;
	TGFX_Menu_t * parent;
	void (*menu_function)(void);


};



class Menu_buttons_container : public Menu_buttons_containerBase
{
public:
    Menu_buttons_container();
    virtual ~Menu_buttons_container() {}

    virtual void initialize();
    void setupListElement(const Bitmap& iconBMP, TEXTS iconTextID, TGFX_Menu_t Menu);
    void SetListElemnts(int item);
    TGFX_Menu_t TGFX_menu_elemnt;


protected:


private:
    /*
     * Callback Declarations
     */
    touchgfx::Callback<Menu_buttons_containerBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
  //  GenericCallback< Menu_buttons_container& >* viewCallback;
  //  Callback<Menu_buttons_container,int16_t> scrollmenu_ItemSelectedCallback;
  //  void scrollmenu_ItemSelectedCallback(int16_t itemSelected);
};

#endif // MENU_BUTTONS_CONTAINER_HPP
