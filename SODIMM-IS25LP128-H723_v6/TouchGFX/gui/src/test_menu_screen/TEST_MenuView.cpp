#include <gui/test_menu_screen/TEST_MenuView.hpp>

TEST_MenuView::TEST_MenuView():BackClickedCallback(this, &TEST_MenuView::BackClicked)
{

}


void TEST_MenuView::BackClicked(Back_menu_container& element)
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

void TEST_MenuView::setupScreen()
{
    TEST_MenuViewBase::setupScreen();
    Test_menu_back_cont.setBack(TGFX_Actual_menu,BackClickedCallback);
    Test_menu_tree_title.Set_Title(TGFX_Sub_menu.Ttext);
   // touchgfx_printf("name: %s\n", TGFX_Actual_menu.name);

}

void TEST_MenuView::tearDownScreen()
{
    TEST_MenuViewBase::tearDownScreen();
}



/*
 * Virtual Action Handlers
 */
void TEST_MenuView::btn_spr_clicked()
{
	bool state = Btn_Spr.getState();

if(state == 1)
{
		Btn_Pdz.forceState(1);
		Btn_Pdz.setTouchable(0);
		Btn_Pco.forceState(1);
		Btn_Pco.setTouchable(0);
		invalidate();

	//touchgfx_printf("name: %s\n", "mmmmm");
}
else
{
	Btn_Pdz.setTouchable(1);
	Btn_Pco.setTouchable(1);
}
    // Override and implement this function in TEST_Menu
}

void TEST_MenuView::btn_pdz_clicked()
{
    // Override and implement this function in TEST_Menu
}

void TEST_MenuView::btn_pco_clicked()
{
    // Override and implement this function in TEST_Menu
}

void TEST_MenuView::btn_pcwu_clicked()
{
    // Override and implement this function in TEST_Menu
}

void TEST_MenuView::btn_3d_clicked()
{
    // Override and implement this function in TEST_Menu
}

void TEST_MenuView::btn_gr1_clicked()
{
    // Override and implement this function in TEST_Menu
}

void TEST_MenuView::btn_gr2_clicked()
{
    // Override and implement this function in TEST_Menu
}

void TEST_MenuView::btn_zz_clicked()
{
    // Override and implement this function in TEST_Menu
}
