#include <gui/test_menu_screen/TEST_MenuView.hpp>

TEST_MenuView::TEST_MenuView():BackClickedCallback(this, &TEST_MenuView::BackClicked)
{

}


void TEST_MenuView::BackClicked(Back_menu_container& element)
{
	application().gotoMenu_9ScreenNoTransition();
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
