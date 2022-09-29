#ifndef MENU_BUTTONS_CONTAINER_HPP
#define MENU_BUTTONS_CONTAINER_HPP

#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

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

extern TGFX_Menu_t sub_menu_9_1;
extern TGFX_Menu_t sub_menu_9_2;


class Menu_buttons_container : public Menu_buttons_containerBase
{
public:
    Menu_buttons_container();
    virtual ~Menu_buttons_container() {}

    virtual void initialize();

    void SetListElemnts(int item);


protected:

  //  Callback<Menu_buttons_container,int16_t> scrollmenu_ItemSelectedCallback;
  //  void scrollmenu_ItemSelectedCallback(int16_t itemSelected);
};

#endif // MENU_BUTTONS_CONTAINER_HPP
