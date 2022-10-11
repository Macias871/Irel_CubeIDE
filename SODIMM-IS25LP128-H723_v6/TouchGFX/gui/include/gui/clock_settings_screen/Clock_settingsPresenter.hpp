#ifndef CLOCK_SETTINGSPRESENTER_HPP
#define CLOCK_SETTINGSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Clock_settingsView;

class Clock_settingsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Clock_settingsPresenter(Clock_settingsView& v);

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

    virtual ~Clock_settingsPresenter() {};

private:
    Clock_settingsPresenter();

    Clock_settingsView& view;
};

#endif // CLOCK_SETTINGSPRESENTER_HPP
