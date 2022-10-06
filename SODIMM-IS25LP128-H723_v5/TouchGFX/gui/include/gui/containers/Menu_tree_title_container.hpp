#ifndef MENU_TREE_TITLE_CONTAINER_HPP
#define MENU_TREE_TITLE_CONTAINER_HPP

#include <gui_generated/containers/Menu_tree_title_containerBase.hpp>
#include <gui_generated/containers/Menu_buttons_containerBase.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Utils.hpp>
#include "../Structures.h"


class Menu_tree_title_container : public Menu_tree_title_containerBase
{
public:
    Menu_tree_title_container();
    virtual ~Menu_tree_title_container() {}
    void Set_Title(TEXTS iconTextID);

    virtual void initialize();
protected:
};

#endif // MENU_TREE_TITLE_CONTAINER_HPP
