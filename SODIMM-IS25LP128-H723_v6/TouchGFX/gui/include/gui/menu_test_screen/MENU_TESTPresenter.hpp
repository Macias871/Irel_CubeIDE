#ifndef MENU_TESTPRESENTER_HPP
#define MENU_TESTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MENU_TESTView;

class MENU_TESTPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MENU_TESTPresenter(MENU_TESTView& v);

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

    virtual ~MENU_TESTPresenter() {};

private:
    MENU_TESTPresenter();

    MENU_TESTView& view;
};

#endif // MENU_TESTPRESENTER_HPP
