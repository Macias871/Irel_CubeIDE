/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <new>
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

using namespace touchgfx;

FrontendApplicationBase::FrontendApplicationBase(Model& m, FrontendHeap& heap)
    : touchgfx::MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
    touchgfx::HAL::getInstance()->setDisplayOrientation(touchgfx::ORIENTATION_PORTRAIT);
    touchgfx::Texts::setLanguage(GB);
    reinterpret_cast<touchgfx::LCD32bpp&>(touchgfx::HAL::lcd()).enableTextureMapperAll();
}

/*
 * Screen Transition Declarations
 */

// Main_screen

void FrontendApplicationBase::gotoMain_screenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplication::gotoMain_screenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMain_screenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Main_screenView, Main_screenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Menu_9

void FrontendApplicationBase::gotoMenu_9ScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplication::gotoMenu_9ScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMenu_9ScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Menu_9View, Menu_9Presenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
