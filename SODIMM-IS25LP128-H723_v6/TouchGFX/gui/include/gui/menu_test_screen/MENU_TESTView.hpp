#ifndef MENU_TESTVIEW_HPP
#define MENU_TESTVIEW_HPP

#include <gui_generated/menu_test_screen/MENU_TESTViewBase.hpp>
#include <gui/menu_test_screen/MENU_TESTPresenter.hpp>
#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <gui_generated/menu_9_screen/Menu_9ViewBase.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <gui/containers/Menu_buttons_container.hpp>
#include <touchgfx/Utils.hpp>

class MENU_TESTView : public MENU_TESTViewBase
{
public:
    MENU_TESTView();
    virtual ~MENU_TESTView() {}
    virtual void setupScreen();
    TGFX_Menu_t TGFX_menu_elemnt;
    virtual void tearDownScreen();
protected:
};

#endif // MENU_TESTVIEW_HPP
