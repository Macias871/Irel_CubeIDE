/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MENU_9VIEWBASE_HPP
#define MENU_9VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/containers/Menu_tree_title_container.hpp>
#include <gui/containers/Back_menu_container_1.hpp>
#include <touchgfx/containers/scrollers/ScrollList.hpp>
#include <gui/containers/Menu_buttons_container.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/mixins/ClickListener.hpp>

class Menu_9ViewBase : public touchgfx::View<Menu_9Presenter>
{
public:
    Menu_9ViewBase();
    virtual ~Menu_9ViewBase() {}
    virtual void setupScreen();

    virtual void scrollListUpdateItem(Menu_buttons_container& item, int16_t itemIndex)
    {
        // Override and implement this function in Menu_9
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image backgroud;
    Menu_tree_title_container menu_tree_title_container1;
    Back_menu_container_1 back_menu_container_11;
    touchgfx::ClickListener< touchgfx::ScrollList > scrollList;
    touchgfx::DrawableListItems<Menu_buttons_container, 10> scrollListListItems;
    touchgfx::TextArea textArea1;

private:
    touchgfx::Callback<Menu_9ViewBase, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> updateItemCallback;
    void updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // MENU_9VIEWBASE_HPP
