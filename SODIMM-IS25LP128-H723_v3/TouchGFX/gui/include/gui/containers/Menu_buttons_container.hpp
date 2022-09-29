#ifndef MENU_BUTTONS_CONTAINER_HPP
#define MENU_BUTTONS_CONTAINER_HPP

#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>






class Menu_buttons_container : public Menu_buttons_containerBase
{
public:
    Menu_buttons_container();
    virtual ~Menu_buttons_container() {}

    virtual void initialize();
    void setupListElement(const Bitmap& iconBMP, TEXTS iconTextID);
    void SetListElemnts(int item);


protected:

  //  Callback<Menu_buttons_container,int16_t> scrollmenu_ItemSelectedCallback;
  //  void scrollmenu_ItemSelectedCallback(int16_t itemSelected);
};

#endif // MENU_BUTTONS_CONTAINER_HPP
