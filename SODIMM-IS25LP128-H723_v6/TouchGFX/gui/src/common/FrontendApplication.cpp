#include <gui/common/FrontendApplication.hpp>
#include <gui/test_menu_screen/TEST_MenuView.hpp>
#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <platform/driver/lcd/LCD32bpp.hpp>
#include <gui/main_screen_screen/Main_screenView.hpp>
#include <gui/main_screen_screen/Main_screenPresenter.hpp>
#include <gui/menu_9_screen/Menu_9View.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <gui/test_menu_screen/TEST_MenuView.hpp>
#include <gui/test_menu_screen/TEST_MenuPresenter.hpp>

#include <gui/clock_settings_screen/Clock_settingsView.hpp>
#include <gui/clock_settings_screen/Clock_settingsPresenter.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{

}


void FrontendApplication::Test_menu_ScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::Test_menu_ScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::Test_menu_ScreenNoTransitionImpl()
{
    touchgfx::makeTransition<TEST_MenuView, TEST_MenuPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}




void FrontendApplication::Set_Date_ScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::Set_Date_ScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::Set_Date_ScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Clock_settingsView, Clock_settingsPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
