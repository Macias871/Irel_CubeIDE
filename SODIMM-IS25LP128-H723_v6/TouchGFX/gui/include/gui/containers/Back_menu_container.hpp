#ifndef BACK_MENU_CONTAINER_1_HPP
#define BACK_MENU_CONTAINER_1_HPP

#include <gui_generated/containers/Back_menu_containerBase.hpp>
#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <gui_generated/containers/Menu_tree_title_containerBase.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Utils.hpp>
#include "../Structures.h"

class Back_menu_container : public Back_menu_containerBase
{
public:
    Back_menu_container();
    virtual ~Back_menu_container() {}

    TGFX_Menu_t TGFX_back_elemnt;

    virtual void initialize();

    virtual void Back_clicked();

    void setBack(TGFX_Menu_t Menu_parent,GenericCallback< Back_menu_container& >& callback);

protected:

    GenericCallback< Back_menu_container& >* BackCallback;

};

#endif // BACK_MENU_CONTAINER_1_HPP
