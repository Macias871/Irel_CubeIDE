#ifndef MENU_9PRESENTER_HPP
#define MENU_9PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Menu_9View;

class Menu_9Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Menu_9Presenter(Menu_9View& v);

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

    virtual ~Menu_9Presenter() {};

private:
    Menu_9Presenter();

    Menu_9View& view;
};

#endif // MENU_9PRESENTER_HPP
