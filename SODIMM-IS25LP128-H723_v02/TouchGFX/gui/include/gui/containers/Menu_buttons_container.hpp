#ifndef MENU_BUTTONS_CONTAINER_HPP
#define MENU_BUTTONS_CONTAINER_HPP

#include <gui_generated/containers/Menu_buttons_containerBase.hpp>

class Menu_buttons_container : public Menu_buttons_containerBase
{
public:
    Menu_buttons_container();
    virtual ~Menu_buttons_container() {}

    virtual void initialize();
protected:
};

#endif // MENU_BUTTONS_CONTAINER_HPP
