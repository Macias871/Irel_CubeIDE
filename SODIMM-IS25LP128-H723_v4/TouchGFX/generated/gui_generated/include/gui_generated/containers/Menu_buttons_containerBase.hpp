/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MENU_BUTTONS_CONTAINERBASE_HPP
#define MENU_BUTTONS_CONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class Menu_buttons_containerBase : public touchgfx::Container
{
public:
    Menu_buttons_containerBase();
    virtual ~Menu_buttons_containerBase();
    virtual void initialize();

    /*
     * Virtual Action Handlers
     */
    virtual void button_menu_clicked()
    {
        // Override and implement this function in Menu_buttons_container
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Button button1;
    touchgfx::TextArea textarea;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Menu_buttons_containerBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // MENU_BUTTONS_CONTAINERBASE_HPP
