#include <gui/clock_settings_screen/Clock_settingsView.hpp>

Clock_settingsView::Clock_settingsView():BackClickedCallback(this, &Clock_settingsView::BackClicked)
{

}

void Clock_settingsView::BackClicked(Back_menu_container& element)
{
	//TGFX_Actual_menu = TGFX_Sub_menu;

	if(TGFX_Actual_menu.parent != NULL)
	{
		application().gotoMenu_9ScreenNoTransition();
	}
	else
	{
		application().gotoMain_screenScreenNoTransition();
	}


}

void Clock_settingsView::setupScreen()
{
    Clock_settingsViewBase::setupScreen();

    Clock_back_menu_container.setBack(TGFX_Actual_menu,BackClickedCallback);
    Clock_menu_tree_title_container.Set_Title(T_SET_CLOCK);
}

void Clock_settingsView::tearDownScreen()
{
    Clock_settingsViewBase::tearDownScreen();
}
