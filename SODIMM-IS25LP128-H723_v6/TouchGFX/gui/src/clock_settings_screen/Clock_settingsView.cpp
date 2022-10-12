#include <gui/clock_settings_screen/Clock_settingsView.hpp>

Clock_settingsView::Clock_settingsView():BackClickedCallback(this, &Clock_settingsView::BackClicked)
{

    Clock_back_menu_container.setBack(TGFX_Actual_menu,BackClickedCallback);
    Clock_menu_tree_title_container.Set_Title(T_SET_CLOCK);


    HH_container.Min_value = 0;
    HH_container.Max_value = 23;
    HH_container.step_fine_value = 1;
    HH_container.step_coarse_value = 5;
    HH_container.value = HH_container.Min_value;

    MM_container.Min_value = 0;
    MM_container.Max_value = 59;
    MM_container.step_fine_value = 1;
    MM_container.step_coarse_value = 5;
    MM_container.value = MM_container.Min_value;


    YY_container.Min_value = 2022;
    YY_container.Max_value = 2099;
    YY_container.step_fine_value = 1;
    YY_container.step_coarse_value = 5;
    YY_container.value = YY_container.Min_value;
    //YY_container.invalidate();

    MO_container.Min_value = 1;
    MO_container.Max_value = 12;
    MO_container.step_fine_value = 1;
    MO_container.step_coarse_value = 3;
    MO_container.value = 1;
   // MO_container.invalidate();

    DD_container.Min_value = 1;
    DD_container.Max_value = 31;
    DD_container.step_fine_value = 1;
    DD_container.step_coarse_value = 5;
    DD_container.value = 1;
    //DD_container.invalidate();

    Clock_settingsViewBase::setupScreen();

    //invalidate();

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





}

void Clock_settingsView::tearDownScreen()
{
    Clock_settingsViewBase::tearDownScreen();
}
