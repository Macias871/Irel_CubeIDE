#include <gui/menu_9_screen/Menu_9View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>


TGFX_Menu_t menu_9 = { "9. Menu", T_MENU_TITLE_9_1,NULL, NULL, &sub_menu_9_1, NULL, NULL};

TGFX_Menu_t sub_menu_9_1 = { "9.1. Nastawy podstawowe", T_DEFAULT_SETTINGS , &sub_menu_9_2, NULL, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_2 = { "9.2. Serwis"            , T_SERVICE          ,NULL          , &sub_menu_9_1, NULL, NULL, NULL};



//TGFX_Menu_t *TGFX_Actual_menu;
TGFX_Menu_t *Sub_menu;
TGFX_Menu_t *Temp_menu;


Menu_9View::Menu_9View()
{

}

void Menu_9View::setupScreen()
{
    //Menu_9ViewBase::setupScreen();

	//TGFX_Actual_menu = &sub_menu_9_1;


    menu_tree_title_container1.initialize();
    back_menu_container_11.initialize();

    fill_positions_menu(menu_9);

   // scrollList.invalidate();




    //scrollList.initialize();

    /*for (int i = 0; i < scrollListListItems.getNumberOfDrawables(); i++)
    {
        scrollListListItems[i].initialize();
    }
*/



   // scrollListListItems[0].setupListElement(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID), T_DEFAULT_SETTINGS);
   // scrollListListItems[1].setupListElement(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID), T_SERVICE);
    //scrollListListItems[2].setupListElement(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID), T_OUT_TEMPERATURE);

    /*
    for(uint8_t position = 0; position < 9; position++)
    {
    	scrollListListItems[0].setupListElement(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID), T_DEFAULT_SETTINGS);
    }
    */
}


void Menu_9View::fill_positions_menu(TGFX_Menu_t Menu)
{

	uint8_t numbers_of_menu_lines = 0;


	if(Menu.child != NULL)
	{
		Sub_menu = Menu.child;
	}

    for(uint8_t position = 0; position < 9; position++)
    {
    	if(Menu.next == NULL)
    	{
    		break;
    	}

    	if(Sub_menu->next == NULL)
    	{
    		break;
    	}

    //	scrollListListItems[position].setupListElement(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID), Sub_menu->Ttext);

    	Sub_menu = Sub_menu->next;


   	numbers_of_menu_lines++;

    }


	//if(Menu.next != NULL)
	//{
	//scrollListListItems[position].setupListElement(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID), Sub_menu.Ttext);
	//}

}


void Menu_9View::tearDownScreen()
{
    Menu_9ViewBase::tearDownScreen();
}



void Menu_9View::scrollListUpdateItem(Menu_buttons_container& item, int16_t itemIndex, TGFX_Menu_t Menu)
{



	//item.SetListElemnts(itemIndex,TGFX_Actual_menu);

}


void Menu_9View::listElementClicked(Menu_buttons_container& element)
{
    // The button of the list element has been pressed
    // so it is removed from the list
   // list.remove(element);
   // scrollCnt.invalidate();
}
