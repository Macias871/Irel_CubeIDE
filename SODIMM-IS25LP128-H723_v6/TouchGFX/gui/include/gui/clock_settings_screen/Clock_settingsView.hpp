#ifndef CLOCK_SETTINGSVIEW_HPP
#define CLOCK_SETTINGSVIEW_HPP

#include <gui_generated/clock_settings_screen/Clock_settingsViewBase.hpp>
#include <gui/clock_settings_screen/Clock_settingsPresenter.hpp>

class Clock_settingsView : public Clock_settingsViewBase
{
public:
    Clock_settingsView();
    virtual ~Clock_settingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void BackClicked(Back_menu_container& element);
protected:

    Callback<Clock_settingsView, Back_menu_container&> BackClickedCallback;
};

#endif // CLOCK_SETTINGSVIEW_HPP
