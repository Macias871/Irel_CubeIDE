#ifndef MENU_BUTTONS_CONTAINER_HPP
#define MENU_BUTTONS_CONTAINER_HPP

#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Utils.hpp>
#include "../Structures.h"



class Menu_buttons_container : public Menu_buttons_containerBase
{
public:
    Menu_buttons_container();
    virtual ~Menu_buttons_container() {}

    virtual void initialize();

    void setupListElement( TEXTS iconTextID, TGFX_Menu_t Menu);
    TGFX_Menu_t TGFX_menu_elemnt;

    virtual void clickAction();

    /**
     * Setup the view callback
     */
    void setAction(GenericCallback< Menu_buttons_container& >& callback);

protected:

    GenericCallback< Menu_buttons_container& >* viewCallback;


};

#endif // MENU_BUTTONS_CONTAINER_HPP
