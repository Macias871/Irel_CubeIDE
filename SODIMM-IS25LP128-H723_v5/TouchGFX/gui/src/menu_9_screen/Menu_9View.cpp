#include <gui/menu_9_screen/Menu_9View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>
#include <gui/containers/Menu_buttons_container.hpp>
#include <gui/containers/Back_menu_container_1.hpp>




//TGFX_menu_struct   {const char * name;TEXTS  Ttext;TGFX_Menu_t * next;TGFX_Menu_t * prev;TGFX_Menu_t * child;TGFX_Menu_t * parent;void (*menu_function)(void);};
TGFX_Menu_t menu_9 = { "9. Menu", T_MENU_TITLE_9_1,NULL, NULL, &sub_menu_9_1, NULL, NULL};

TGFX_Menu_t sub_menu_9_1 = { "9.1. Nastawy podstawowe", T_DEFAULT_SETTINGS , &sub_menu_9_2, NULL, &sub_menu_9_1_1, &sub_menu_9_1, NULL};

	TGFX_Menu_t sub_menu_9_1_1 = { "9.1.1 Język"            , T_LANGUAGE     , &sub_menu_9_1_2, NULL, NULL, &sub_menu_9_1, NULL};
	TGFX_Menu_t sub_menu_9_1_2 = { "9.1.2 Zał ogrz"         , T_SET_HEAT     , &sub_menu_9_1_3, &sub_menu_9_1_2, NULL, &sub_menu_9_1, NULL};
	TGFX_Menu_t sub_menu_9_1_3 = { "9.1.3 Ust. Fab."        , T_SET_DEFAULTS , &sub_menu_9_1_4, &sub_menu_9_1_3, NULL, &sub_menu_9_1, NULL};
	TGFX_Menu_t sub_menu_9_1_4 = { "9.1.4 Ust. Roz."        , T_SET_EXTERNALS, NULL, &sub_menu_9_1_3, NULL, &sub_menu_9_1, NULL};



TGFX_Menu_t sub_menu_9_2 = { "9.2. Serwis"            , T_SERVICE          , &sub_menu_9_3, &sub_menu_9_1, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_3 = { "9.3. Diagnostyka"       , T_DIAGNSTIC        , &sub_menu_9_4, &sub_menu_9_2, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_4 = { "9.4. Temp. zew."        , T_OUT_TEMPERATURE  , &sub_menu_9_5, &sub_menu_9_3, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_5 = { "9.5. Czas pracy"        , T_WORK_TIME        , &sub_menu_9_6, &sub_menu_9_4, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_6 = { "9.6. Wybór programu"    , T_SET_PROGRAMM     , NULL         , &sub_menu_9_5, NULL, NULL, NULL};



TGFX_Menu_t *TGFX_Actual_menu;
TGFX_Menu_t *Sub_menu;
TGFX_Menu_t Temp_menu;
TGFX_Menu_t *Base_of_menu_struct_items[30];



Menu_9View::Menu_9View(): listElementClickedCallback(this, &Menu_9View::listElementClicked),BackElementClickedCallback(this, &Menu_9View::BackElementClicked)
{
}

void Menu_9View::listElementClicked(Menu_buttons_container& element)
{
	//touchgfx_printf("Received callback from: %s\n", element.TGFX_menu_elemnt.name);

	//TGFX_Actual_menu = element.TGFX_menu_elemnt.child;

	//Temp_menu = *element.TGFX_menu_elemnt.child;

	fill_positions_menu(sub_menu_9_1);

}


void Menu_9View::BackElementClicked(Back_menu_container_1& element)
{
	//touchgfx_printf("Received callback from: %s\n", "1");
	//fill_positions_menu(*element.TGFX_back_elemnt.parent);
	touchgfx_printf("name: %s\n", element.TGFX_back_elemnt.name);
	touchgfx_printf("parent: %s\n", element.TGFX_back_elemnt.parent->name);

	//TGFX_Actual_menu = element.TGFX_menu_elemnt.child;

	//Temp_menu = *element.TGFX_back_elemnt.parent->name;



	//fill_positions_menu(sub_menu_9_1);

}

void Menu_9View::setupScreen()
{
    menu_tree_title_container1.initialize();
    back_menu_container_11.initialize();
    fill_positions_menu(menu_9);

}


void Menu_9View::fill_positions_menu(TGFX_Menu_t Menu)
{

	uint8_t numbers_of_menu_lines = 0;



	if(Menu.child != NULL)
	{
		Sub_menu = Menu.child;
	}

    for(uint8_t position = 0; position < 30; position++)
    {
    	scrollListListItems[position].setupListElement( Sub_menu->Ttext, *Sub_menu);
    	scrollListListItems[position].setAction(listElementClickedCallback);
    	//touchgfx_printf("Received callback from: %s\n", Sub_menu->name);
    	Base_of_menu_struct_items[position] = Sub_menu;
    	numbers_of_menu_lines++;
    	if(Sub_menu->next == NULL)
    	{
    		break;
    	}
    	else
    	{
    		Sub_menu = Sub_menu->next;
    	}

    }

    back_menu_container_11.setBack(Menu,BackElementClickedCallback);
    scrollList.setNumberOfItems(numbers_of_menu_lines);
    scrollList.invalidate();

}


void Menu_9View::tearDownScreen()
{
    Menu_9ViewBase::tearDownScreen();
}
