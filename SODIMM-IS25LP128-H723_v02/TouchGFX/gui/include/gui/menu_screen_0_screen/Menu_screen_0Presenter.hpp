#ifndef MENU_SCREEN_0PRESENTER_HPP
#define MENU_SCREEN_0PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Menu_screen_0View;

class Menu_screen_0Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Menu_screen_0Presenter(Menu_screen_0View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Menu_screen_0Presenter() {};

private:
    Menu_screen_0Presenter();

    Menu_screen_0View& view;
};

#endif // MENU_SCREEN_0PRESENTER_HPP
