#include <gui/menu_9_screen/Menu_9View.hpp>









Menu_9View::Menu_9View(): listElementClickedCallback(this, &Menu_9View::listElementClicked),BackElementClickedCallback(this, &Menu_9View::BackElementClicked)
{
}

void Menu_9View::listElementClicked(Menu_buttons_container& element)
{
	if(element.TGFX_menu_elemnt.menu_function == NULL)
	{
		Temp_menu = element.TGFX_menu_elemnt;
		fill_positions_menu(Temp_menu);
		scrollcnt.setVisible(1);
//		Sub_menu_cont.setVisible(0);
		invalidate();

	}
	else
	{
		scrollcnt.setVisible(0);
//		Sub_menu_cont.setVisible(1);
		//Sub_menu_cont.setVisible(1);
		Open_callback_menu(element.TGFX_menu_elemnt);

		back_menu_cont.setBack(element.TGFX_menu_elemnt,BackElementClickedCallback);
		invalidate();

	}


}


void Menu_9View::BackElementClicked(Back_menu_container& element)
{
	//application().gotoMenu_9ScreenNoTransition();

	//touchgfx_printf("name: %s\n", "main");

	if(element.TGFX_back_elemnt.parent != NULL)
	{

		scrollcnt.setVisible(1);
//		Sub_menu_cont.setVisible(0);


		fill_positions_menu(*element.TGFX_back_elemnt.parent);
	}
	else
	{
		application().gotoMain_screenScreenNoTransition();

	}

/*
	touchgfx_printf("name: %s\n", element.TGFX_back_elemnt.name);
	touchgfx_printf("parent: %s\n", element.TGFX_back_elemnt.parent->name);
*/

}


void Menu_9View::Open_callback_menu(TGFX_Menu_t Menu)
{

	//TGFX_Actual_menu = Menu;

	TGFX_Sub_menu = Menu;

	application().Test_menu_ScreenNoTransition();

}






void Menu_9View::setupScreen()
{
	//touchgfx_printf("name: %s\n", "setup menu");


	//Test_cont.setVisible(0);
//	Sub_menu_cont.setVisible(0);

    menu_tree_title_cont.initialize();
    back_menu_cont.initialize();
    fill_positions_menu(TGFX_Actual_menu);

}



void Menu_9View::fill_positions_menu(TGFX_Menu_t Menu)
{
	if(Menu.child != NULL)
	{
		TGFX_Actual_menu = Menu;
		list.removeAll();

		Sub_menu = Menu.child;

	    for(uint8_t position = 0; position < 30; position++)
	    {
	    	scrollListListItems[position].setupListElement( Sub_menu->Ttext, *Sub_menu);
	    	scrollListListItems[position].setAction(listElementClickedCallback);
	    	list.add(scrollListListItems[position]);
	    //	touchgfx_printf("name: %s\n", scrollListListItems[position].TGFX_menu_elemnt.name);
	    //	Base_of_menu_struct_items[position] = Sub_menu;
	    	if(Sub_menu->next == NULL)
	    	{
	    		scrollcnt.invalidate();
	    //	    touchgfx_printf("EXIT", numbers_of_menu_lines);
	    		break;
	    	}
	    	else
	    	{
	    		Sub_menu = Sub_menu->next;
	    	}

	    }
	    back_menu_cont.setBack(Menu,BackElementClickedCallback);
	    menu_tree_title_cont.Set_Title(Menu.Ttext);

	}
}



void Menu_9View::tearDownScreen()
{
    Menu_9ViewBase::tearDownScreen();
}
