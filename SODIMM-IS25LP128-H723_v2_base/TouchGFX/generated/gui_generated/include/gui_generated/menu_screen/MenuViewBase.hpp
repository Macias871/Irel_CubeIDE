/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MENUVIEWBASE_HPP
#define MENUVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>

class MenuViewBase : public touchgfx::View<MenuPresenter>
{
public:
    MenuViewBase();
    virtual ~MenuViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::Box box2;
    touchgfx::Box box2_1;
    touchgfx::Box box2_1_1;

private:

};

#endif // MENUVIEWBASE_HPP